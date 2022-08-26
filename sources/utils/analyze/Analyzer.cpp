#include <cmath>
#include <algorithm>
#include <iostream>

#include "../node/Node.h"
#include "Analyzer.h"

// macros for the color in the console.
#define NC "\e[0m"
#define RED "\e[0;31m"

using namespace std;

double Analyzer::distance(Node* node1, Node* node2) {
    return sqrt(pow(node2->getPosition().getX() - node1->getPosition().getX(), 2) + pow(node2->getPosition().getY() - node1->getPosition().getY(), 2));
}


void Analyzer::majDistanceForNeighbor(Node* currentNode, Node* node1, vector<Node*> nodesAlreadyVisited) {
    // Change the value of the neighbour if it is greater than the sum of the distance between the
    // Current node and the neighbour + the value of the current node
    if (node1->getValue() > currentNode->getValue() + distance(currentNode, node1)) {
        node1->setValue(currentNode->getValue() + distance(currentNode, node1));
        node1->setOld(currentNode);
    }

    // Value of elt goes into good node of nodesAlreadyVisited
    Node* nexELTDETEST = *std::find_if(nodesAlreadyVisited.begin(), nodesAlreadyVisited.end(), [&node1](Node* node) {
        return node->getName() == node1->getName();
    });

    nexELTDETEST->setValue(node1->getValue());
}


Node* Analyzer::findNode(const vector<Node*>& nodes, Node* searchedNode) {
    for (Node* elt : nodes)
        if (searchedNode == elt) return searchedNode;

    return nullptr;
}


void Analyzer::init(const vector<Node*>& nodes, Node* startingNode) {
    for (Node* elt : nodes)
        elt->setValue(INFINITY);

    // The distance between the starting vertex and its neighbours is 0.
    startingNode->setValue(0);
}


bool Analyzer::comp(Node* node1, Node* node2) { return node1->getValue() < node2->getValue(); }


void Analyzer::dijkstra(const vector<Node*>& nodes, Node* startingNode) {
    init(nodes, startingNode); // init the nodes in the graphs
    vector<Node*> nodesAlreadyVisited = vector<Node*>(nodes); // Unvisited nodes of the graph, if visited then do not appear in the test vector

    // We visit all the nodes of the graph
    while (!nodesAlreadyVisited.empty()) {
        // We look for the smallest value of the remaining (unvisited) nodes
        Node* currentNodeFromNodesAlreadyVisited  = *std::min_element(nodesAlreadyVisited.begin(),nodesAlreadyVisited.end(), comp);
        Node* currentNodeFromNodes                = findNode(nodes, currentNodeFromNodesAlreadyVisited);

        // we visit all the neighbours of the looked node ...
        for (Node* elt : currentNodeFromNodes->getNeighbors()) {
            // ... except those that are not in nodesAlreadyVisited because already visited
            if (findNode(nodesAlreadyVisited, elt) != nullptr)
                majDistanceForNeighbor(currentNodeFromNodes, elt, nodesAlreadyVisited);
        }

        // removal of the node already visited from the vector of nodes remaining to be visited.
        nodesAlreadyVisited.erase(std::remove(nodesAlreadyVisited.begin(), nodesAlreadyVisited.end(), currentNodeFromNodesAlreadyVisited), nodesAlreadyVisited.end());
    }
}


pair<bool, vector<Node>> Analyzer::dijkstraPath(Node* startingNode, Node* endNode) {
    pair<bool, vector<Node>> pairPath(true, vector<Node>());

    while (endNode != startingNode) {
        // problem with the path = no path between startingNode and endNode
        if (endNode == nullptr) {
            pairPath.first = false;
            break;
        }

        pairPath.second.insert(pairPath.second.begin(), *endNode);
        endNode = endNode->getOld(); // we take the predecessor
    }

    // if path exist we add the start node
    if (pairPath.first) pairPath.second.insert(pairPath.second.begin(), *startingNode);
    return pairPath;
}


vector<vector<Node>> Analyzer::dijkstraPathForTraffic(const vector<vector<Node*>>& traffic, const vector<Node*>& nodes) {
    vector<vector<Node>> res;

    for(vector<Node*> elt : traffic) {
        Node* firstElt = elt[0]; // The first elt on traffic
        dijkstra(nodes, firstElt); // Applies the calculations related to the Dijkstra algorithm

        for (int i = 1; i < elt.size(); i++) {
            pair<bool, vector<Node>> pairPath = dijkstraPath(firstElt, elt[i]);

            // if a path exists then it is added otherwise an error is printed
            if (pairPath.first) {
                res.push_back(pairPath.second);
            } else {
                cout << RED "[ERROR]\tThere is no path between (" << firstElt->getName() << ", " << elt[i]->getName() << ")" NC << endl;
            }
        }
    }

    return res;
}