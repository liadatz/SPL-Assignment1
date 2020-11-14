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
Session::Session(const std::string &path):g{{}}, infectedQueue() {
    ifstream i("../config1.json");
    json j;
    i >> j;
    currCycle = 0;
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

void Session::enqueueInfected(int) {

}

int Session::dequeueInfected() {

}

TreeType Session::getTreeType() const {
    return treeType;
}




