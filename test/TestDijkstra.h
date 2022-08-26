#ifndef PROJET_RESEAU_CPP_TESTDIJKSTRA_H
#define PROJET_RESEAU_CPP_TESTDIJKSTRA_H

#include "../sources/parsing/Parser.h"

/**
 * class that test the Dijstra algorithm class.
 *
 * @author COUTAND Bastien
 * @version 1.0
 * @date 23.04.2022
 */
class TestDijkstra {
    private:
        /**
         * The good parser for the path.
         */
        Parser _goodParser;

        /**
         * Result in form of [=E=E==>].
         * E : Error
         * = : OK
         */
        std::string _result;

        /**
         * The bad parser for the path.
         */
        Parser _badParser;

        void testGoodDijkstraAlgorithm();

        void testBadDijkstraAlgorithm();

    public:
        TestDijkstra();

        /**
         * Function to run all tests.
         */
        void runTests();
};


#endif //PROJET_RESEAU_CPP_TESTDIJKSTRA_H
