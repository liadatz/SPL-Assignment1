#ifndef GRAPH_H_
#define GRAPH_H_

#include "Tree.h"
#include <vector>

using namespace std;

enum nodeState{
    Healthy,
    Carrier,
    Infected
};

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    std::vector<std::vector<int>>& getEdgesReference();
    std::vector<int>& getNeighbors(int nodeInd);
    void removeEdges (int nodeInd);
    bool checkStopCondition();


    std::vector<int> nodesStatus; // Number indicator: 0-healthy 1-carrying virus 2-sick
private:
    std::vector<std::vector<int>> edges;
    int nOfUnhealthy;

};

#endif

