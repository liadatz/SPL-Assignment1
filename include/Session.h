#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    //------------Rule-Of-5--------------------
    Session(const std::string& path);
    ~Session();

    //------------Methods--------------------
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    
    void enqueueInfected(int);
    int dequeueInfected();


    Graph& getGraphReference();
    TreeType getTreeType() const;
    int getCurrCycle() const;
    
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    int currCycle;
    std::queue<int> infectedQueue;
};

#endif
