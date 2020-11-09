//
// Created by spl211 on 09/11/2020.
//
#include "../include/Graph.h"
class Graph : public Graph{
    std::vector<std::vector<int>> edges;
    Graph(std::vector<std::vector<int>> matrix) : matrix(edges);
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
};




