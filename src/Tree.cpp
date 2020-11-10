#include "../include/Tree.h"
#include "../include/Session.h"
#include <queue>

//------------Rule-Of-5--------------------
// Constructor
Tree::Tree(int rootLabel):node(rootLabel),children(){}

// Destructor
Tree::~Tree(){
    delete this;
    for (int i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

// Copy Constructor
Tree::Tree(const Tree &other) {

}

// Move Constructor
Tree::Tree(Tree &&other){}

// Copy Assignment
Tree::Tree& operator=(const Tree &other){}

// Move Assignment
Tree::Tree& operator=(Tree &&other){}


//------------Methods--------------------
void Tree::addChild(const Tree& child){
    Tree* const childClone = clone(child);
    std::vector<Tree*>::iterator iterator;
    int i = 0;
    while (childClone->node > children[i]->node) i++;
    children.insert(iterator,i,childClone);
}

void Tree::addChild(Tree* child) {}

Tree* Tree::clone(const Tree& tree) {}

Tree* Tree::createTree(const Session& session, int rootLabel) {
    Tree* tree;
    if (session.getTreeType()==Cycle) tree = new CycleTree(rootLabel,session.getCurrCycle());
    else if (session.getTreeType()==Root) tree = new RootTree(rootLabel);
    else tree = new MaxRankTree(rootLabel);
    return tree;
}

Tree& Tree::runBFS(Session& session,int rootLabel) {
    Tree* tree = createTree(session,rootLabel);
    std::vector<std::vector<int>>& edges = session.getGraphReference().getEdges();
    int numOfVertices = edges.size();
    int currVertex;
    std::vector<bool>visited(numOfVertices,false);
    std::queue<int> queue;
    visited[rootLabel] = true;
    queue.push(rootLabel);
    while (!queue.empty()) {
        currVertex = queue.front();
        for (int i = 0; i < numOfVertices; ++i) {
            if (!visited[i] && edges[currVertex][i] == 1) {
                visited[i] = true;
                tree->addChild(createTree(session,i));
                queue.push(i);
            }
        }
    }
    return *tree;
}

Tree* Tree::getChild(int i) {
    if (i <= children.size()) return children[i];
    else return nullptr;
}

//------------Cycle-Tree--------------------
CycleTree::CycleTree(int rootLabel, int currCycle):Tree(rootLabel),currCycle(currCycle){}

int CycleTree::traceTree() {
    Tree* BFSTree = runBFS(session,node);
    int c = currCycle;
    int output = node;
    while ((c>0) & !children.empty()) {
        output = BFSTree->getChild(0)->node;
    }
    return output;
}

//------------MaxRank-Tree--------------------
MaxRankTree::MaxRankTree(int rootLabel):Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    std::vector<std::vector<int>> nodes;

}

//------------Root-Tree--------------------
RootTree::RootTree(int rootLabel):Tree(rootLabel) {}

int RootTree::traceTree() {
    return node;
}