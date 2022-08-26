#ifndef PROJET_RESEAU_CPP_TESTNODE_H
#define PROJET_RESEAU_CPP_TESTNODE_H

#include "../sources/utils/node/Node.h"

/**
 * class that test the Node class.
 *
 * @author COUTAND Bastien
 * @version 1.1
 * @date 23.04.2022
 */
class TestNode {
    private:
        Node _node1;
        Node _node2;

        /**
         * Function that tests the creation of an object of type node with
         * its getters and setters.
         */
        void testCreation();

        /**
         * Function that tests the equality operation between two nodes.
         */
        void testEqualOperator();

        /**
         * Function that tests the addition of a neighbour for a node.
         */
        void testAddNeighbor();

        /**
         * Function that tests the deletion of a neighbour for a node.
         */
        void testRemoveNeighbor();

    public:
        TestNode();

        /**
         * Function to run all tests.
         */
        void runTests();
};


#endif //PROJET_RESEAU_CPP_TESTNODE_H
