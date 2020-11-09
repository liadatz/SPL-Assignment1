//
// Created by spl211 on 09/11/2020.
//
#include "../include/Graph.h"
Graph::Graph(const std::vector<std::vector<int>> &matrix) : edges(&matrix){}


void infectNode(int nodeInd){
        this._arr[nodeInd]=true;
    }
    bool isInfected(int nodeInd){
        return _arr[nodeInd];
    }
