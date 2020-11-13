#include "../include/Agent.h"


// Constructor
Agent::Agent() {}

//------------ContactTracer----------------
ContactTracer::ContactTracer() {}

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
    g.infectNode(nodeInd);
    for (int i = 0; i < nodeNeighbors.size(); i++){
        if (nodeNeighbors[i] == 1 && g.nodesStatus[i] == 0) {
            g.nodesStatus[i] = 1;
            Virus newVirus = Virus(i);
            session.addAgent(newVirus);
            session.enqueueInfected(i);
            break;
        }
    }
}