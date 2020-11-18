#include "../include/Agent.h"
#include "../include/Session.h"

// Constructor
Agent::Agent() = default;
Agent::~Agent() {}

//------------ContactTracer----------------
ContactTracer::ContactTracer() = default;

Agent* ContactTracer::clone() const {return new ContactTracer(*this);}

void ContactTracer::act(Session &session) {
    int dequeueNode = session.dequeueInfected();
    if (dequeueNode != -1) {
        Tree* tree = Tree::createTree(session, dequeueNode);
        tree->runBFS(session);
        int traceNode = tree->traceTree();
        session.getGraphReference().removeEdges(traceNode);
        delete tree;
        tree = nullptr;
    }
}

//------------Virus-------------------
Virus::Virus(int nodeInd):nodeInd(nodeInd) {}

Agent* Virus::clone() const {return new Virus(*this);}

void Virus::act(Session &session) {
    Graph& g = session.getGraphReference();
    std::vector<int>& nodeNeighbors = g.getNeighbors(nodeInd);
    if(!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    for (unsigned int i = 0; i < nodeNeighbors.size(); i++){
        if (nodeNeighbors[i] == 1 && g.nodesStatus[i] == Healthy) {
            Virus newVirus = Virus(i);
            g.nodesStatus[i] = Carrier;
            session.addAgent(newVirus);
            break;
        }
    }
}