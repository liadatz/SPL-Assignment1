#ifndef TREE_H_
#define TREE_H_
#include "Graph.h"

#include <vector>

class Session;

class Tree{
public:
//------------Rule Of 5--------------------
    Tree(int rootLabel);
    virtual ~Tree();
    Tree(const Tree& other);
    Tree(Tree &&other);
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other);

//------------Methods--------------------
    void addChild(const Tree& child);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual Tree* clone() const=0;
    void runBFS(Session& session);
    Tree* getChild(unsigned int i);
    void clear();
    int getNodeNumber () const;
    int getNumOfChildren ();

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
    virtual Tree* clone() const;
protected:
    int currCycle;
};

//------------MaxRank-Tree--------------------
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

//------------Root-Tree--------------------
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif
