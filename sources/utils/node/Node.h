#ifndef PROJET_RESEAU_CPP_NODE_H
#define PROJET_RESEAU_CPP_NODE_H

#include <string>
#include "Position.h"
#include <vector>

/**
 * The class that defines a node
 *
 * @author COUTAND Bastien
 * @version 1.3
 * @date 20.05.2022
 */
class Node {
    private:
        /**
         * The name of the node.
         */
        std::string _name;

        /**
         * The value of the useful node for dijkstra.
         */
        double _value;

        /**
         * The position of the node in the graph.
         */
        Position _position;

        /**
         * The addresses of the node's neighbours.
         */
        std::vector<Node*> _neighbors;

        /**
         * The address of the node before this one, useful for creating paths in the dijkstra algorithm.
         */
        Node* _old = nullptr;

    public:
        Node(std::string name, Position position, double value);
        Node(); // default builder

        /**
         * Function that returns the _name attribute.
         * @return string
         */
        std::string getName();

        /**
         * Function that returns the _position attribute.
         * @return Position
         */
        Position getPosition();

        /**
         * Function that returns the _old attribute.
         * @return node*
         */
        Node* getOld();

        /**
         * Function that modifies the _old attribute with the newOld parameter.
         * @param newOld : the node before.
         */
        void setOld(Node* newOld);

        /**
         * Function that returns the _value attribute.
         * @return double
         */
        double getValue() const;

        /**
         * Function that modifies the _value attribute with the newValue parameter.
         * @param newValue : the new newValue.
         */
        void setValue(double newValue);

        /**
         * Function that returns the _neighbors attribute.
         * @return vector<node*>
         */
        std::vector<Node*> getNeighbors();

        /**
         * Function that adds the new neighbour as a parameter to the list of
         * neighbours of the current node.
         * @param newNeighbor : the new neighbour.
         */
        void addNeighbor(Node* newNeighbor);

        /**
        * Function that remove the new neighbour as a parameter to the list of
        * neighbours of the current node.
        * @param neighbor : the neighbour to delete.
        */
        void removeNeighbor(Node* neighbor);

        /**
         * Overload of the == operator which allows to compare the equality between
         * two objects of class node.
         * @param otherNode : the otherNode to be compared with the current otherNode.
         * @return true if equals, otherwise false.
         */
        bool operator==(Node otherNode) const;
};


#endif //PROJET_RESEAU_CPP_NODE_H
