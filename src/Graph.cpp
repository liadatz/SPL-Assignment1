#include "../include/Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix):nodesStatus(),edges(matrix),nOfUnhealthy(-1){ // TODO: Check error
    for (unsigned int i=0;i<edges.size();i++)
        nodesStatus.push_back(Healthy); // init node's vector
}

void Graph::infectNode(int nodeInd) {
    nodesStatus[nodeInd] = Infected;
}

bool Graph::isInfected(int nodeInd) {
    return nodesStatus[nodeInd] == Infected;
}

std::vector<std::vector<int>>& Graph::getEdgesReference() {
    return edges;
}

void Graph::removeEdges(int nodeInd) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}

std::vector<int>& Graph::getNeighbors(int nodeInd) {
    return edges[nodeInd];
}

bool Graph::checkStopCondition() {
    int counter = 0;
    for (int &node : nodesStatus) if (node != Healthy) counter++;
    if (counter == nOfUnhealthy) return true;
    else {
        nOfUnhealthy = counter;
        return false;
    }
}
