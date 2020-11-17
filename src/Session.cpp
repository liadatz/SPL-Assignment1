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
Session::Session(const std::string &path):g{{}},treeType(),agents(),currCycle(0),infectedQueue(){
    ifstream i(path);
    json j;
    i >> j;
    // Initiate graph
    g = Graph (j["graph"]);

    // Initiate agent
    int ind = 0;
    for (auto& agent: j["agents"]) {
        if (agent[0] == "C") {
            ContactTracer* CT = new ContactTracer();
            addAgent(*CT);
            delete (CT);
        }
        else {
            Virus* virus = new Virus (agent[1]);
            addAgent(*virus);
            this->g.nodesStatus[ind] = 1; //~Stav
            enqueueInfected(agent[1]);
            delete (virus);
        }
        ind++;
    }

    // Initiate TreeType
    if (j["tree"] == "C") treeType  = Cycle;
    else if (j["tree"] == "M") treeType  = MaxRank;
    else treeType = Root;
}
//~Stav:
// Destructor
Session::~Session() {
    clear();
}

// Copy Constructor
Session::Session(const Session &other) : g(other.g),treeType(other.treeType),agents(),
                                        currCycle(other.currCycle),infectedQueue(other.infectedQueue)  { //Stav: Added treeType
    for (auto& agent : other.agents) {
        addAgent(*agent);
    }
}

// Move Constructor
Session::Session(Session&& other) : g(other.g),treeType(other.treeType),agents(),
                                    currCycle(other.currCycle),infectedQueue(other.infectedQueue) {
    int i = 0;
    for (auto& agent : other.agents) {
        this->agents[i] = agent;
        i++;
    }
    //clearing other:
    std::vector<std::vector<int>> emptyG;
    other.g = Graph(emptyG);//Clearing the graph
    other.clear();
    other.currCycle = 0;
    std::queue<int> emptyQ;
    std::swap(other.infectedQueue, emptyQ);//Clearing the queue
}


// Copy Assignment
Session& Session::operator=(const Session &other){
    if(this != &other){
        this->g = other.g;
        this->treeType = other.treeType;
        this->currCycle = other.currCycle;
        clear();
        for (auto& agent : other.agents)
            addAgent(*agent);
        this->infectedQueue = other.infectedQueue;
    }
    return *this;
}

// Move Assignment
Session& Session::operator=(Session &&other){
    if(this != &other){
        this->g = other.g;
        this->treeType = other.treeType;
        this->currCycle = other.currCycle;
        clear();
        int i = 0;
        for (auto& agent : other.agents) {
            this->agents[i] = agent;
            i++;
        }
        this->infectedQueue = other.infectedQueue;
        other.clear();
    }
    return *this;
}
//------------Methods--------------------
void Session::simulate() {
    while(!g.checkStopCondition()){
        currCycle++;
        int size = agents.size();
        for (int i = 0; i < size; i++) {
            agents[i]->act(*this);
        }
    }
    json output;
    ofstream i("./output.json");
    output["graph"] = g.getEdgesReference();
    std::vector<int> infected;
    for(uint j=0; j < g.nodesStatus.size() ; j++){
        if(g.nodesStatus[j] != 0)
            infected.push_back(j);
    }
    output["infected"] = infected;
    i << output;
    cout << "finished"; // TODO: DELETE
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






