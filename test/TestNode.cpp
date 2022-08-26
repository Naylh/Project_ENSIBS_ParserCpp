#include <iostream>
#include <cmath>

#include "TestNode.h"

// macros for the color in the console.
#define NC "\e[0m"
#define GRN "\e[0;32m"
#define RED "\e[0;31m"

using namespace std;

TestNode::TestNode() :
    _node1("Node1", Position(12, 34), 52.3),
    _node2() {}

void TestNode::runTests() {
    cout << GRN "\nNode test : [";
    this->testCreation();
    this->testEqualOperator();
    this->testAddNeighbor();
    this->testRemoveNeighbor();
    cout << ">]" NC << endl;
}

void TestNode::testCreation() {
    cout << (this->_node1.getName() == "Node1" ? "=" : RED "E" NC); // True
    cout << (this->_node1.getPosition() == Position(12, 34) ? "=" : RED "E" NC); // True
    cout << (this->_node1.getValue() == 52.3 ? "=" : RED "E" NC); // True
    cout << (this->_node1.getNeighbors().empty() ? "=" : RED "E" NC); // True
    cout << (this->_node1.getOld() == nullptr ? "=" : RED "E" NC); // True

    cout << (this->_node2.getValue() == INFINITY ? "=" : RED "E" NC); // True
    this->_node2.setValue(10);
    cout << (this->_node2.getValue() == 10 ? "=" : RED "E" NC); // True

    this->_node2.setOld(&_node1);
    cout << (this->_node2.getOld() == &_node1 ? "=" : RED "E" NC); // True
}

void TestNode::testEqualOperator() {
    Node tmpNode = Node(_node1); // deep copy

    cout << (this->_node1 == tmpNode ? "=" : RED "E" NC); // True
    cout << (this->_node1 == _node2  ? RED "E" NC : "="); // False
}

void TestNode::testAddNeighbor() {
    this->_node1.addNeighbor(&_node2);
    this->_node2.addNeighbor(&_node1);

    cout << (this->_node1.getNeighbors()[0] == &this->_node2 ? "=" : RED "E" NC); // True
    cout << (this->_node2.getNeighbors()[0] == &this->_node1 ? "=" : RED "E" NC); // True
}

void TestNode::testRemoveNeighbor() {
    this->_node1.removeNeighbor(&_node2);
    this->_node2.removeNeighbor(&_node1);

    cout << (this->_node1.getNeighbors().empty() ? "=" : RED "E" NC); // True
    cout << (this->_node2.getNeighbors().empty() ? "=" : RED "E" NC); // True
}
