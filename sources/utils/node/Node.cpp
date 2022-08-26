#include "Node.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

Node::Node() : _position(0, 0) {
    this->_name  = "";
    this->_value = INFINITY;
}

Node::Node(string name, Position position, double value) : _position(position) {
    this->_name  = std::move(name);
    this->_value = value;
}

string Node::getName() {
    return this->_name;
}

Position Node::getPosition() {
    return this->_position;
}

bool Node::operator==(Node otherNode) const {
    return this->_name == otherNode.getName();
}

double Node::getValue() const {
    return this->_value;
}

void Node::setValue(double newValue) {
    this->_value = newValue;
}

Node* Node::getOld() {
    return this->_old;
}

void Node::setOld(Node* newOld) {
    this->_old = newOld;
}

std::vector<Node*> Node::getNeighbors() {
    return this->_neighbors;
}

void Node::addNeighbor(Node* newNeighbor) {
    this->_neighbors.push_back(newNeighbor);
}

void Node::removeNeighbor(Node* neighbor) {
    this->_neighbors.erase(std::remove(this->_neighbors.begin(), this->_neighbors.end(), neighbor), this->_neighbors.end());
}