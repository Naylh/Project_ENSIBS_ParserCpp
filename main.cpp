#include <iostream>
#include <string>
#include <cstdlib>
#include <regex>
#include <fstream>
#include <vector>

#include "sources/parsing/Parser.h"
#include "sources/utils/analyze/Analyzer.h"
#include "test/TestNode.h"
#include "test/TestParser.h"
#include "test/TestDijkstra.h"

using namespace std;

/**
 * @brief Get the Min object of a vector of pointers
 *
 * @param tabNode vector of pointers
 * @param pos x or y
 * @return int the minimum value of x or y from the array
 */
int getMin(vector<Node*> tabNode, char pos)
{
    if (tabNode.size() > 0) //check if there is value
    {
        if (pos == 'x') //check if pos is x
        {
            int min = tabNode.at(0)->getPosition().getX(); //initialize the value
            for (int i = 0; i < tabNode.size(); i++) //for each value in the array
            {
                if (tabNode.at(i)->getPosition().getX() < min) //if the value is less than min then
                {
                    min = tabNode.at(i)->getPosition().getX(); //change min value
                }
            }
            return min;
        }
        else if (pos == 'y') //check if pos is y
        {
            int min = tabNode.at(0)->getPosition().getY(); //initialize the value
            for (int i = 0; i < tabNode.size(); i++) //for each value in the array
            {
                if (tabNode.at(i)->getPosition().getY() < min) //if the value is less than min then
                {
                    min = tabNode.at(i)->getPosition().getY(); //change min value
                }
            }
            return min;
        }
    }
    return 0;
}

/**
 * @brief Get the Max object of a vector of pointers
 *
 * @param tabNode vector of pointers
 * @param pos x or y
 * @return int the maximum value of x or y from the array
 */
int getMax(vector<Node*> tabNode, char pos)
{
    if (tabNode.size() > 0) //check if there is value
    {
        if (pos == 'x') //check if pos is x
        {
            int max = tabNode.at(0)->getPosition().getX(); //initialize the value
            for (int i = 0; i < tabNode.size(); i++) //for each value in the array
            {
                if (tabNode.at(i)->getPosition().getX() > max) //check if the value is greater than max then
                {
                    max = tabNode.at(i)->getPosition().getX(); //change the value
                }
            }
            return max;
        }
        else if (pos == 'y') //check if pos is y
        {
            int max = tabNode.at(0)->getPosition().getY(); //initialize the value
            for (int i = 0; i < tabNode.size(); i++) //for each value in the array
            {
                if (tabNode.at(i)->getPosition().getY() > max) //check if the value is greater than max then
                {
                    max = tabNode.at(i)->getPosition().getY(); //change the value
                }
            }
            return max;
        }
    }
    return 0;
}

/**
 * @brief write the .dem file
 *
 * @param parser
 * @return int
 */
int writeDem(Parser parser)
{
    string filetowrite("./graph/tobeexecute.dem"); //the name of the .dem file
    fstream output_fstream; //the variable stream to write the .dem file

    output_fstream.open(filetowrite, std::ios_base::out); //open the .dem file
    if (!output_fstream.is_open()) //check if the .dem file is open
    {
        cout << "Failed to open " << filetowrite << endl; //print an error message
    }
    else
    {
        //Display of the network
        vector<Node*> tabNode{parser.getNodes()}; //array of nodes

        for (int i = 0; i < tabNode.size(); i++) //for each node
        {
            output_fstream << "set label \"" << tabNode.at(i)->getName() << "\"  at " << tabNode.at(i)->getPosition().getX() << "," << tabNode.at(i)->getPosition().getY() << endl; //set a label at the position of the node
        }

        //I think it's prettier to do like that than an autoscale
        output_fstream << "set xrange [" << getMin(tabNode, 'x') - 10 << ":" << getMax(tabNode, 'x') + 10 << "]" << endl; //set xrange
        output_fstream << "set yrange [" << getMin(tabNode, 'y') - 10 << ":" << getMax(tabNode, 'y') + 10 << "]" << endl; //set yrange

        for (int i = 0; i < tabNode.size(); i++) //for each node
        {
            output_fstream << "set object circle at " << tabNode.at(i)->getPosition().getX() << "," << tabNode.at(i)->getPosition().getY() << " size 1 fc rgb  \"blue\"" << endl; //put a circle at the position of the node
        }
        output_fstream << "plot \"data.dat\" with lines;" << endl; //plot the first file .dat
        output_fstream << "pause mouse \"click to continue\"" << endl; //do a break and wait until a click

        //Display of packages with Dijkstra
        vector<vector<Node>> packets = Analyzer::dijkstraPathForTraffic(parser.getTraffic(), parser.getNodes()); //array of packets
        for (int i = 0; i < packets.size();i++) { //for each packets
            output_fstream << "set title \"Packet "<< i+1 << "\"" << endl; //set title to the graph (on the top)
            output_fstream << "set label \"Packet" << i+1 << "\"  at " << packets.at(i).at(0).getPosition().getX() -2 << "," << packets.at(i).at(0).getPosition().getY() -2 << endl; //set a label at the beginning of the way's packet
            for (int j = 0; j < packets.at(i).size();j++) { //for each way of each packet
                output_fstream << "set object rect from " << packets.at(i).at(j).getPosition().getX() -1 << "," << packets.at(i).at(j).getPosition().getY() -1<< " to "<< packets.at(i).at(j).getPosition().getX() +1 << "," << packets.at(i).at(j).getPosition().getY() +1 <<" fc rgb  \"red\"" << endl; //put a rectangle over the node
            }
            output_fstream << "plot \"data"<< i <<".dat\" with lines;" << endl; //plot other file .dat
            output_fstream << "pause mouse \"click to continue\"" << endl; //do a break and wait until a click
        }
        cout << "Done Writing The File .dem !" << endl; //print a correct message
        output_fstream.close(); //close the file
    }
    return 0;
}

/**
 * @brief write the first .dat file with the position of nodes and their connections inside the network
 *
 * @param parser
 * @param fileName the name of the file .dat
 * @return int
 */
int firstWriteDat(Parser parser, string fileName)
{
    string filetowrite("./graph/"+fileName+".dat"); //the name of the .dat file
    fstream output_fstream; //the variable stream to write the .dat file

    output_fstream.open(filetowrite, std::ios_base::out); //open the .dat file
    if (!output_fstream.is_open()) //check if the .dat file is open
    {
        cout << "Failed to open " << filetowrite << endl; //print an error message
    }
    else
    {
        output_fstream << "# x  y" << endl; //just put a comment in the .dat file
        vector<Node*> tabNode = parser.getNodes(); //array of node
        vector<vector<Node>> tabConnection{parser.getConnection()}; //array of connection between nodes

        for (int i = 0; i < tabNode.size(); i++) // for each node
        {
            output_fstream << tabNode.at(i)->getPosition().getX() << "  " << tabNode.at(i)->getPosition().getY() << endl; //write their position
        }

        for (int i = 0; i < tabConnection.size(); i++) //for each connection
        {
            output_fstream << endl;
            output_fstream << tabConnection.at(i).at(0).getPosition().getX() << "  " << tabConnection.at(i).at(0).getPosition().getY() << endl; //write the position of the first node to be link
            output_fstream << tabConnection.at(i).at(1).getPosition().getX() << "  " << tabConnection.at(i).at(1).getPosition().getY() << endl; //write the position of the second node to be link
        }

        cout << "Done Writing The First File .dat !" << endl; //print a correct message
        output_fstream.close(); //close the file
    }
    return 0;
}

/**
 * @brief write the first .dat file with the position of nodes and their connections inside the network
 *
 * @param parser
 * @param fileName the name of the file .dat
 * @param i the position of the packet to be display
 * @return int
 */
int writeDat(Parser parser, string fileName, int i)
{
    string filetowrite("./graph/"+fileName+".dat"); // write a .dat file with the name given
    fstream output_fstream; //the variable stream to write the .dat file

    output_fstream.open(filetowrite, std::ios_base::out); //open the .dat file
    if (!output_fstream.is_open()) //check if the file is open
    {
        cout << "Failed to open " << filetowrite << endl; //print an error message
    }
    else
    {
        vector<vector<Node>> packets = Analyzer::dijkstraPathForTraffic(parser.getTraffic(), parser.getNodes()); //get the packets from Dijkstra

        for (int j = 0; j < packets.at(i).size()-1;j++) { //for the way of the i-th packet
            output_fstream << packets.at(i).at(j).getPosition().getX() << "  " << packets.at(i).at(j).getPosition().getY() << endl; //write the position of the first node to be link
            output_fstream << packets.at(i).at(j+1).getPosition().getX() << "  " << packets.at(i).at(j+1).getPosition().getY() << endl; //write the position of the second node to be link
            output_fstream << endl;
        }

        cout << "Done Writing The File .dat !" << endl; //print a correct message
        output_fstream.close(); //close the file
    }
    return 0;
}


int main(int argc, char *argv[]) {

    cout << "\n\n\n _____  _____   ____       _ ______ _____ _______ _____           \n"
            "|  __ \\|  __ \\ / __ \\     | |  ____/ ____|__   __/ ____|_     _   \n"
            "| |__) | |__) | |  | |    | | |__ | |       | | | |   _| |_ _| |_ \n"
            "|  ___/|  _  /| |  | |_   | |  __|| |       | | | |  |_   _|_   _|\n"
            "| |    | | \\ \\| |__| | |__| | |___| |____   | | | |____|_|   |_|  \n"
            "|_|    |_|  \\_\\\\____/ \\____/|______\\_____|  |_|  \\_____|        " << endl << endl << endl;

    // Include -h for help
    if ((argc == 2 && strcmp(argv[1], "-h") == 0) || (argc == 1)) {
        cout << "Usage: ./projet <filename>" << endl;
        cout << "Example: ./projet G2_PMRSimple.csv" << endl;
        return EXIT_FAILURE;
    }

    cout << "------------------------ TEST PART --------------------" << endl;
    TestNode testNode;
    testNode.runTests();

    TestParser testParser;
    testParser.runTests();

    TestDijkstra testDijkstra;
    testDijkstra.runTests();

    cout << "\n\n--------------- Display node neighbors from filename ---------------" << endl;
    Parser parser = Parser(argv[1]);
    parser.calculateParsingAttributes();

    vector<Node*> nodes = parser.getNodes();

    nodes.at(0)->addNeighbor(new Node("node34", Position(2,3), 0));
    nodes.at(0)->addNeighbor(new Node("node44", Position(1,3), 0));
    cout << nodes.at(0)->getNeighbors().at(0)->getName() << endl;
    cout << nodes.at(0)->getNeighbors().at(1)->getName() << endl;

    nodes.at(0)->removeNeighbor(new Node("node34", Position(2,3), 0));
    cout << nodes.at(0)->getNeighbors().at(0)->getName() << endl;

    Parser parser3 = Parser(argv[1]);
    parser3.calculateParsingAttributes();


    // Display of nodes and their neighbours
    for (Node* elt : parser3.getNodes()) {
        cout << elt->getName() << " : ";

        for (Node* neighbor : elt->getNeighbors())
            cout << neighbor->getName() << " ";

        cout << endl;
    }

    // ----- Test Dijkstra
    cout << "\n\n--------------- Display path from traffic with Dijkstra algorithm ---------------" << endl;
    Parser parser2 = Parser(argv[1]);
    parser2.calculateParsingAttributes();

    Analyzer::dijkstra(parser2.getNodes(), parser2.getTraffic().at(0).at(0));
    vector<vector<Node>> r = Analyzer::dijkstraPathForTraffic(parser2.getTraffic(), parser2.getNodes());

    for (const vector<Node>& elt : r) {
        cout << "path : ";
        for (Node elt_bis : elt)
            cout << elt_bis.getName() << " - ";
        cout << endl;
    }

    // ----- Test Gnu plot part
    cout << "\n\n--------------- Construct the gnu plot part ---------------" << endl;
    Parser parser4 = Parser(argv[1]); //parse command line arguments
    parser4.calculateParsingAttributes(); //check the integrity of the file
    vector<vector<Node>> packets = Analyzer::dijkstraPathForTraffic(parser4.getTraffic(), parser4.getNodes()); //get the packets from Dijkstra
    string name; //a variable name

    firstWriteDat(parser4,"data"); //write the first .dat file
    for (int i = 0; i < packets.size(); i++){ //for each way of each packet
        name = "data" + to_string(i); //change the name of the file
        writeDat(parser4,name,i); //write .dat file
    }
    writeDem(parser4); //write the .dem file

    return EXIT_SUCCESS;
}