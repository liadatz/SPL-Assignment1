#include "../include/Agent.h"
#include "../include/Session.h"
#include <iostream>
#include <fstream>
#include "../include/json.hpp"
#include <queue>

using json = nlohmann::json;
using namespace std;

//------------Rule-Of-5--------------------
// Constructor
Session::Session(const std::string &path):g{{}},agents(),infectedQueue(),currCycle(0){
    ifstream i("../config1.json");
    json j;
    i >> j;
    // Initiate graph
    g = Graph (j["graph"]);

    // Initiate agent
    int ind = 0;
    for (auto& agent: j["agents"]) {
        if (agent[ind][0] == "C") {
            ContactTracer* CT = new ContactTracer();
            addAgent(*CT);
            delete (CT); // maybe not needed
        }
        else {
            Virus* virus = new Virus (agent[ind][1]);
            addAgent(*virus);
            delete (virus); // maybe not needed
        }
        ind++;
    }

    // Initiate TreeType
    if (j["tree"] == "C") treeType  = Cycle;
    else if (j["tree"] == "M") treeType  = MaxRank;
    else treeType = Root;
}

// Destructor
Session::~Session() {
    clear();
}

// Copy Constructor
Session::Session(const Session &other) : g(other.g),agents(),infectedQueue(other.infectedQueue),currCycle(other.currCycle) {
    for (auto& agent : other.agents) {
        addAgent(*agent);
    }
}

// Move Constructor

// Copy Assignment

// Move Assignment


//------------Methods--------------------
void Session::simulate() {
}

void Session::addAgent(const Agent &agent) {
    agents.push_back(agent.clone());
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}
Graph& Session::getGraphReference() {
    return g;
}

int Session::getCurrCycle() const {
    return currCycle;
}

void Session::enqueueInfected(int nodeInd) {
    infectedQueue.push(nodeInd);
}

int Session::dequeueInfected() {
    if (infectedQueue.empty()) return -1;
    int output = infectedQueue.front();
    infectedQueue.pop();
    return output;
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::clear() {
    for (auto& agent : agents) delete (agent);
    agents.clear();
}






