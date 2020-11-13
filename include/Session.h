#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Session.h"
#include "Graph.h"
#include "Tree.h"
#include "Agent.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    
    void enqueueInfected(int);
    int dequeueInfected();

    // Getters
    Graph& getGraphReference();
    TreeType getTreeType() const;
    int getCurrCycle() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int currCycle;
};

#endif
