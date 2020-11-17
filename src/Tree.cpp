#include "../include/Tree.h"
#include "../include/Session.h"
#include <queue>


using namespace std;

// TODO:arrange methods in private and public

//------------Rule-Of-5--------------------
// Constructor
Tree::Tree(int rootLabel) : node(rootLabel), children() {}

// Destructor
Tree::~Tree() {
    clear();
}

// Copy Constructor
Tree::Tree(const Tree &other) : node(other.node), children(){
    for (auto& child : other.children) {
        this->children.push_back(child->clone());
    }
}

// Move Constructor
Tree::Tree(Tree &&other) : node(other.node), children() {
    int i = 0;
    for (auto &child : other.children) {
        this->children[i] = child;
        i++;
    }
    other.children.clear();
}

// Copy Assignment
Tree& Tree::operator=(const Tree &other){
    if (this!=&other) {
        this->node = other.node;
        for (auto& child : other.children) {
            this->children.push_back(child->clone());
        }
    }
    return *this;
}

// Move Assignment
Tree& Tree::operator=(Tree &&other){
    if (this!=&other) {
        clear();
        this->node = other.node;
        int i = 0;
        for (auto &child : other.children) {
            this->children[i] = child;
            i++;
        }
        other.children.clear();
    }
    return *this;
}


//------------Methods--------------------
void Tree::addChild(const Tree &child) {
    Tree* childClone = child.clone();
    std::vector<Tree*>::iterator it = children.begin();
    unsigned int i = 0;
    while (i < children.size() && childClone->node > children[i]->node) i++; // TODO: check for case when children is empty possible error
    children.insert(it+i, childClone);
}

void Tree::addChild(Tree *child) {
    std::vector<Tree*>::iterator it = children.begin();
    unsigned int i = 0;
    while (i < children.size() && child->node > children[i]->node) i++; // TODO: check for case when children is empty possible error
    children.insert(it+i, child);

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree *tree;
    if (session.getTreeType() == Cycle) tree = new CycleTree(rootLabel, session.getCurrCycle());
    else if (session.getTreeType() == Root) tree = new RootTree(rootLabel);
    else tree = new MaxRankTree(rootLabel);
    return tree;
}

void Tree::runBFS(Session& session) {
    std::vector<std::vector<int>>& edges = session.getGraphReference().getEdgesReference();
    int numOfVertices = edges.size();
    int currVertex;
    Tree* currTree;
    std::vector<bool>visited(numOfVertices,false);
    std::queue<Tree*> queue;
    visited[node] = true;
    queue.push(this);
    while (!queue.empty()) {
        currTree = queue.front();
        currVertex = currTree->node;
        queue.pop();
        for (int i = 0; i < numOfVertices; i++) {
            if (!visited[i] && edges[currVertex][i] == 1) {
                visited[i] = true;
                Tree* nextTree = createTree(session,i);
                currTree->addChild(nextTree);
                queue.push(nextTree);
            }
        }
    }
}

Tree *Tree::getChild(unsigned int i) {
    if (i <= children.size()) return children[i];
    else return nullptr;
}

void Tree::clear() {
    for (auto &child: children) delete (child);
    children.clear();
}

int Tree::getNodeNumber() const {
    return node;
}

int Tree::getNumOfChildren() {
    return children.size();
}

//------------Cycle-Tree--------------------
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() {
    int c = currCycle;
    int output = getNodeNumber();
    Tree *currTree = this;
    while ((c > 0) & (currTree->getNumOfChildren() != 0)) {
        currTree = currTree->getChild(0);
        output = currTree->getNodeNumber();
        c--;
    }
    return output;
}

Tree* CycleTree::clone() const {
    Tree* newCycleTree = new CycleTree(*this);
    return newCycleTree;
}
//------------MaxRank-Tree--------------------
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() {
    int maxRankNode = node;
    int maxRank = children.size();
    Tree *currTree;
    std::queue<Tree*> queue;
    queue.push(this);
    while (!queue.empty()) {
        currTree = queue.front();
        queue.pop();
        for (int i = 0; i < currTree->getNumOfChildren(); i++) {
            Tree *child = currTree->getChild(i);
            queue.push(child);
            if (child->getNumOfChildren() > maxRank) {
                maxRankNode = child->getNodeNumber();
                maxRank = child->getNumOfChildren();
            }
        }
    }
    return maxRankNode;
}

Tree* MaxRankTree::clone() const {
    Tree* newMaxRankTree = new MaxRankTree(*this);
    return newMaxRankTree;
}

//------------Root-Tree--------------------
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return node;
}

Tree* RootTree::clone() const {
    Tree* newRootTree = new RootTree(*this);
    return newRootTree;
}