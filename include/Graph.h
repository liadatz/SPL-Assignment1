#ifndef GRAPH_H_
#define GRAPH_H_

#include "Tree.h"
#include <vector>

using namespace std;

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    std::vector<std::vector<int>>& getEdgesReference();
    std::vector<int>& getNeighbors(nodeInd);
    void removeEdges (int nodeInd);


    std::vector<int> nodesStatus; // Number indicator: 0-no virus(healthy) present 1-carrying virus 2-ill
private:
    std::vector<std::vector<int>> edges;

};

#endif

