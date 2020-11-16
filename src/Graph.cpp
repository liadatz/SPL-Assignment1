#include "../include/Graph.h"
#include <queue>

Graph::Graph(std::vector<std::vector<int>> matrix):edges(matrix),nodesStatus(),nOfUnhealthy(-1){ // TODO: Check error
    for (int i=0;i<edges.size();i++)
        nodesStatus.push_back(0); // init node's vector
}

void Graph::infectNode(int nodeInd) {
    nodesStatus.at(nodeInd) = 1;
    }

bool Graph::isInfected(int nodeInd) {
    return nodesStatus.at(nodeInd) == 1 | nodesStatus.at(nodeInd) == 2;
}

std::vector<std::vector<int>>& Graph::getEdgesReference() {
    return edges;
}

void Graph::removeEdges(int nodeInd) {
    for (int i = 0; i < edges.size(); i++) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}

std::vector<int>& Graph::getNeighbors(int nodeInd) {
    return edges[nodeInd];
}

bool Graph::checkStopCondition() {
    int counter = 0;
    for (int &node : nodesStatus) {
        if (node != 0)
            counter++;
    }
    if (counter == nOfUnhealthy) {
        return true;
    } else {
        nOfUnhealthy = counter;
        return false;
    }
}
