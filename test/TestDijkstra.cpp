#include <iostream>

#include "TestDijkstra.h"
#include "../sources/utils/analyze/Analyzer.h"

// macros for the color in the console.
#define NC "\e[0m"
#define GRN "\e[0;32m"
#define RED "\e[0;31m"

using namespace std;

TestDijkstra::TestDijkstra() : _goodParser("./ressources/G2_PMRSimple.csv"), _badParser("./ressources/G8_badPath.csv") {}

void TestDijkstra::runTests() {
    this->_result += GRN "\nDijkstra test : [";
    this->testGoodDijkstraAlgorithm();
    this->testBadDijkstraAlgorithm();
    this->_result += ">]" NC;

    cout << this->_result << endl;
}

void TestDijkstra::testGoodDijkstraAlgorithm() {
    this->_goodParser.calculateParsingAttributes();
    this->_result += (Analyzer::dijkstraPathForTraffic(this->_goodParser.getTraffic(), this->_goodParser.getNodes()).empty() ? RED "E" NC : "=" );
}

void TestDijkstra::testBadDijkstraAlgorithm() {
    this->_badParser.calculateParsingAttributes();

    Node* firstElt = this->_badParser.getTraffic()[0][0];
    Node* endElt   = this->_badParser.getTraffic()[0][1];

    Analyzer::dijkstra(this->_badParser.getNodes(), endElt); // applies dijkstra algorithm
    this->_result += (!Analyzer::dijkstraPath(firstElt, endElt).first ? "=" : RED "E" NC);
}