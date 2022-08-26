#ifndef PROJET_RESEAU_CPP_PARSER_H
#define PROJET_RESEAU_CPP_PARSER_H

#include <string>
#include <vector>
#include "../utils/node/Node.h"

/**
 * Class allowing to parse a CSV file with a specific format cf. document in resources
 *
 * @author MARCHAND Robin
 * @version 1.6
 * @date 15.05.2022
 */
class Parser {
    private:
        /**
         * The set of nodes in the graph.
         */
        std::vector<Node*> _nodes;

        /**
         * All the traffic in the graph.
         */
        std::vector<std::vector<Node*>> _traffic;

        /**
         * The set of connections in the graph
         */
        std::vector<std::vector<Node>> _connection;


        /**
         * The csv file to be parsed.
         */
        std::string _filename;

        /**
         * Check if extension is .csv.
         * @param filename : true if the file has integrity, false otherwise
         * @return true if the file is a csv file, false otherwise.
         */
        bool checkCSVExtension(const std::string& filename);

        /**
        * This takes a string and splits it with a delimiter and returns a vector of strings
        * @param str       : the string to split.
        * @param delimiter : the delimiter who split the string.
        * @return std::vector<std::string>
        */
        std::vector<std::string> splitString(const std::string& str, char delimiter);

    public:
        explicit Parser(const std::string& filename);

        /**
         * Function that returns the _nodes attribute
         * @return vector<node*>
         */
        std::vector<Node*> getNodes();

        /**
         * Function that returns the _traffic attribute
         * @return vector<vector<node*>>
         */
        std::vector<std::vector<Node*>> getTraffic();

        /**
         * Function that returns the _connection attribute
         * @return vector<vector<node*>>
         */
        std::vector<std::vector<Node>> getConnection();

        /**
         * Function that returns the _filename attribute
         * @return string
         */
        std::string getFilename();

        /**
         *  Function that calculates, according to each line of the CSV file, the values to put in the attributes
         *  nodes, and traffic. The connections are managed in "neighbour". A node has therefore a node pointer vector.
         *
         *  The change of part is done with the parameter currentPart at the beginning of the function, this allows
         *  to check the integrity of the file.
         *
         *  It checks if the file is in the right format and without errors: empty file, file that does not contain the
         *  keywords traffic, nodes, connection, or contain double label, and many others error.
         *
         *  @return true if the file has integrity and if the parsing is good, false otherwise.
         */
        bool calculateParsingAttributes();
};

#endif //PROJET_RESEAU_CPP_PARSER_H