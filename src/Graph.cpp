//
// Created by spl211 on 09/11/2020.
//
#include "../include/Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),nodesStatus(){
    for (int i=0;i<edges.size();i++)
        nodesStatus.push_back(false); // init node's vector
}

void Graph::infectNode(int nodeInd) {
    nodesStatus.at(nodeInd) = true;
    }

bool Graph::isInfected(int nodeInd) {
    return nodesStatus.at(nodeInd);
}

std::vector<std::vector<int>> Graph::getEdges() {
    return edges;
};
