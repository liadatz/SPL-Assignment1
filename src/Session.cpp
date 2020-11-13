#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g{{}} {
    ifstream i("../config1.json");
    json j;
    i >> j;
    g = Graph (j["graph"]);
}

void Session::simulate() {
    for (auto& element: agents) {
        element->act();
    }
}

void Session::addAgent(const Agent &agent) {}

void Session::setGraph(const Graph &graph) {
//    g=graph;
}
Graph& Session::getGraphReference() {
    return g;
}

int Session::getCurrCycle() const {
    return currCycle;
}

void Session::enqueueInfected(int) {}

int Session::dequeueInfected() {}

TreeType Session::getTreeType() const {}




