#ifndef PROJET_RESEAU_CPP_ANALYZER_H
#define PROJET_RESEAU_CPP_ANALYZER_H

/**
 * class which defines analysis methods for a graph
 *
 * @author COUTAND Bastien
 * @version 1.1
 * @date 24.05.2022
 */
class Analyzer {
    private:
        /**
         * Function that calculates the distance between two points of coordinates (x,y).
         * @link : https://fr.wikipedia.org/wiki/Distance_entre_deux_points_sur_le_plan_cart%C3%A9sien.
         *
         * @param node1 : the first node.
         * @param node2 : the second node.
         * @return double
         */
        static double distance(Node* node1, Node* node2);
        
        /**
          * Function that updates the distances (value) and predecessor (old) of the current node's
          * neighbours (currentNode).
          *
          * @param currentNode         : the current node.
          * @param node1               : a neighbour of the current node.
          * @param nodesAlreadyVisited : the knots they still have to visit.
          */
         static void majDistanceForNeighbor(Node* currentNode, Node* node1, std::vector<Node*> nodesAlreadyVisited);
        
         /**
          * Function that searches if a searchedNode exists in an array of nodes.
          *
          * @param nodes        : the node table.
          * @param searchedNode : the node to be searched.
          * @return if find then returns the address of the element in question in the array otherwise returns null.
          */
         static Node* findNode(const std::vector<Node*>& nodes, Node* searchedNode);
        
         /**
          * Function that initializes the values of the nodes to plus infinity (maximum valuer) and
          * initializes the value of the starting node to 0.
          *
          * @param nodes        : the nodes of the graph.
          * @param startingNode : the starting node of the traffic.
          */
         static void init(const std::vector<Node*>& nodes, Node* startingNode);
        
         /**
         * Function which is used by the min_element function, which compares the two values of two nodes.
         *
         * @param node1 : the first node.
         * @param node2 : the second node.
         * @return true if the value of node1 is less strict than that of node2, otherwise false
         */
         static bool comp(Node* node1, Node* node2);

    public:
        /**
         * Function that determines the shortest path between two nodes of a graph.
         * @link: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm.
         *
         * @param nodes        : the nodes of the graph.
         * @param startingNode : the starting node of the traffic.
         */
        static void dijkstra(const std::vector<Node*>& nodes, Node* startingNode);


        /**
         * Function that determines the shortest path between startingNode and endNode as parameters,
         * after applying the dijkstra algorithm.
         *
         * IMPORTANT : If the path is not found then the first value of the path becomes false, if the path is found remains true
         *
         * @param startingNode : the starting node.
         * @param endNode      : the final node.
         * @return the path traversed (set of nodes) to get from startingNode to endNode.
         */
        static std::pair<bool, std::vector<Node>> dijkstraPath(Node* startingNode, Node* endNode);

        /**
         * Function that determines the shortest path for a set of traffic with a table of nodes.
         *
         * @param traffic : the traffic to be analysed.
         * @param nodes   : the node table.
         * @return an array of array containing for each row a set of nodes defining the shortest path
         */
        static std::vector<std::vector<Node>> dijkstraPathForTraffic(const std::vector<std::vector<Node*>>& traffic, const std::vector<Node*>& nodes);
};


#endif //PROJET_RESEAU_CPP_ANALYZER_H
