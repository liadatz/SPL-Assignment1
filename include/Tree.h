#ifndef TREE_H_
#define TREE_H_
#include "../include/Session.h"

#include <vector>

class Session;

class Tree{
public:
//------------Rule Of 5--------------------
    Tree(int rootLabel);
    ~Tree();
    Tree(const Tree& other);
    Tree(Tree &&other);
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other);


//------------Methods--------------------
    void addChild(const Tree& child);
    void addChild(Tree* child);
    Tree * clone(const Tree& tree);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    Tree& runBFS(Session& session,int rootLabel);
    Tree* getChild(int i);

//------------Data-Members------------------
protected:
    int node;
    std::vector<Tree*> children;
};

//------------Cycle-Tree--------------------
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
protected:
    int currCycle;
};

//------------MaxRank-Tree--------------------
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};

//------------Root-Tree--------------------
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif
