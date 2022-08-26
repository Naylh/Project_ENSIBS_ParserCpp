#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

#include "Parser.h"

// macros for the color in the console.
#define RED "\e[0;31m"
#define NC "\e[0m"

using namespace std;

Parser::Parser(const string& filename) {
    this->_filename = (this->checkCSVExtension(filename) ? this->_filename = filename :  "");
}


vector<Node*> Parser::getNodes() {
    return this->_nodes;
}


vector<vector<Node*>> Parser::getTraffic() {
    return this->_traffic;
}


vector<vector<Node>> Parser::getConnection() {
    return this->_connection;
}


std::string Parser::getFilename() {
    return this->_filename;
}


bool Parser::checkCSVExtension(const string& filename) {
    if (filename.substr(filename.find_last_of('.') + 1) != "csv") {
        cout << RED "[ERROR]\tFile extension must be .csv" NC << endl;
        return false;
    }

    return true;
}


vector<string> Parser::splitString(const string &str, char delimiter) {
    stringstream basicStringStream(str);
    vector<string> result;
    string item;

    // parses the elements of the string in parameter split according to the delimiter
    while (getline(basicStringStream, item, delimiter))
        result.push_back(item);


    return result;
}


bool Parser::calculateParsingAttributes() {
    ifstream input_file(this->_filename);

    // Test open file
    if (!input_file.is_open()) {
        cout << RED "[ERROR]\tCould not open the file" NC << endl;
        return false;
    }

    // regex for parsing ...
    regex nodeReg("Node,+"), trafficReg("traffic,+"), connectionReg("connection,+");
    regex nodeRegLine("Node([0-9]+(,[0-9]+)+),*"), TCRegLine("Node[0-9]+,Node[0-9]+(,Node[0-9]+)*,*"); // TC for Traffic and Connection

    vector<string> lines;
    string line; // Add line of the input file to the vector files.

    int currentPart = -1; // -1 -> start / 0 -> Nodes part / 1 -> Traffic part / 2 -> Connection part

    while (getline(input_file, line)) {
        // Test empty line
        if (line.length() == 0) {
            cout << RED "[ERROR]\tEmpty lines in the file !" NC << endl;
            return false;
        }

        vector<string> splitLine = splitString(line, ','); // cuts each current line according to the "," delimiter
        splitLine.erase(remove(splitLine.begin(), splitLine.end(), ""), splitLine.end()); // We delete from the vector the empty elements caused by the final commas


        /***************************************************************************
        /                                                                          /
        /     CHANGE THE CURRENT PART (NODES, TRAFFIC, CONNECTION)                 /
        /                                                                          /
        ***************************************************************************/


        // Check if "nodes" is in the first line
        if (regex_match(line, nodeReg)) {
            currentPart ++;
            continue;
        }
            // Check if "traffic" is present in the whole file
        else if (regex_match(line, trafficReg)) {
            // test nodes label existence
            if (currentPart != 0) {
                cout << RED "[ERROR]\tThere is no nodes label in this file !" NC << endl;
                return false;
            }

            currentPart ++;
            continue;
        }
            // Check if "connection" is present in the whole file
        else if (regex_match(line, connectionReg)) {
            // test traffic label existence
            if (currentPart != 1) {
                cout << RED "[ERROR]\tThere is no traffic label in this file !" NC << endl;
                return false;
            }

            currentPart ++;
            continue;
        }


        /*********************************************************************************
        /                                                                                /
        /    APPLIES THE INFORMATION OF THE CURRENT PART (NODES, TRAFFIC, CONNECTION)    /
        /                                                                                /
        *********************************************************************************/


        // if line is node ...
        if (currentPart == 0 && regex_match(line, nodeRegLine)) {
            this->_nodes.emplace_back(new Node(splitLine[0], Position(stoi(splitLine[1]), stoi(splitLine[2])), INFINITY));
            continue;
        }
        // if line is traffic ...
        else if (currentPart == 1 && regex_match(line, TCRegLine)) {
            vector<Node*> traffic;

            for (const string& elt : splitLine) {
                // The node corresponding to the element of the array is searched in the node array and its address is retrieved
                Node* node_traf = *find_if(this->_nodes.begin(), this->_nodes.end(), [elt](Node* node) {
                    return node->getName() == elt;
                });

                traffic.push_back(node_traf);
            }

            this->_traffic.push_back(traffic);
            continue;
        }
        // if line is connection ...
        else if (currentPart == 2 && regex_match(line, TCRegLine)) {
            // ----------- Creation of neighbours in a table useful for the display part ----------- //
            vector<Node> connection;

            for (string elt: splitLine) {
                // The node corresponding to the element of the array is searched for in the node array and copied to the deep
                Node ret = **find_if(this->_nodes.begin(), this->_nodes.end(),
                                     [&elt](Node *node) { return node->getName() == elt; });
                connection.emplace_back(ret);
            }

            this->_connection.push_back(connection);

            /*********** Creating useful neighbours for the Dijkstra algorithm ***********/

            // The node corresponding to the element of the array is searched in the node array and its address is retrieved
            Node &node1 = **find_if(this->_nodes.begin(), this->_nodes.end(), [&splitLine](Node *node) {
                return node->getName() == splitLine[0];
            });

            // The node corresponding to the element of the array is searched in the node array and its address is retrieved
            Node &node2 = **find_if(this->_nodes.begin(), this->_nodes.end(), [&splitLine](Node *node) {
                return node->getName() == splitLine[1];
            });

            // add the neighbour's address for both connecting nodes
            node1.addNeighbor(&node2);
            node2.addNeighbor(&node1);
            continue;
        }
        else {
            cout << RED "[ERROR]\tThere is double label in the csv file !" NC << endl;
            return false;
        }
            }

    // test if final format of csv file is good
    if (currentPart != 2) {
        cout << RED "[ERROR]\tThere is no correct format for the csv file !" NC << endl;
        return false;
    }

    input_file.close();

    return true;
}