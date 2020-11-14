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
    delete this; // TODO:maybe delete 'this'?
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
        this->children[i] = other.children[i];
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
            this->children[i] = other.children[i];
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
    int i = 0;
    while (childClone->node > children[i]->node) i++; // TODO: check for case when children is empty possible error
    children.insert(it, i, childClone);
}

void Tree::addChild(Tree *child) {
    Tree* childTree = new Tree (child); // TODO: check
    std::vector<Tree*>::iterator it = children.begin();
    int i = 0;
    while (childTree->node > children[i]->node) i++; // TODO: check for case when children is empty possible error
    children.insert(it, i, childTree);

}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree *tree;
    if (session.getTreeType() == Cycle) tree = new CycleTree(rootLabel, session.getCurrCycle());
    else if (session.getTreeType() == Root) tree = new RootTree(rootLabel);
    else tree = new MaxRankTree(rootLabel);
    return tree;
}

void Tree::runBFS(Session& session) {
//    Tree* tree = createTree(session,rootLabel);
    std::vector<std::vector<int>>& edges = session.getGraphReference().getEdgesReference();
    int numOfVertices = edges.size();
    int currVertex;
    std::vector<bool>visited(numOfVertices,false);
    std::queue<int> queue;
    visited[node] = true;
    queue.push(node);
    while (!queue.empty()) {
        currVertex = queue.front();
        for (int i = 0; i < numOfVertices; ++i) {
            if (!visited[i] && edges[currVertex][i] == 1) {
                visited[i] = true;
                addChild(createTree(session,i));
                queue.push(i);
            }
        }
    }
//    return tree;
}

Tree *Tree::getChild(int i) {
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
    Tree *currTree;
    while ((c > 0) & !children.empty()) {
        currTree = getChild(0);
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
    std::queue<Tree *> queue;
    queue.push(this);
    while (!queue.empty()) {
        currTree = queue.front();
        for (int i = 0; i < currTree->getNumOfChildren(); i++) {
            Tree *child = getChild(i);
            queue.push(child);
            if (child->getNumOfChildren() > maxRank) maxRankNode = child->getNodeNumber();
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