#include "../include/Agent.h"
#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
#include <queue>

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path):g{{}} {
    ifstream i("../config1.json");
    json j;
    i >> j;
    // Initiate graph
    g = Graph (j["graph"]);

    // Initiate agent
    int indicator = 0;
    for (auto& agent: j["agents"]) {
        if (agent[indicator][0] == "C") ContactTracer* CT = new ContactTracer();

    }
}

void Session::simulate() {
    for (auto& element: agents) {
        element->act();
    }
}

void Session::addAgent(const Agent &agent) {}

void Session::setGraph(const Graph &graph) {
    g = graph;
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




