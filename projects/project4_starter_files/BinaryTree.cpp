#include "BinaryTree.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const int &val, Node *left, Node *right):val(val), left(left), right(right){
}

int Node::getVal() const {
    return val;
}

void Node::setVal(const int &newVal){
    this->val = newVal;
}

Node* Node::getLeft() const {
    return left;
}

void Node::setLeft(const int &newVal) {
    if(!left){
        left = new Node(newVal);
    }
    else{
        left->setVal(newVal);
    }
}

Node* Node::getRight() const {
    return right;
}

void Node::setRight(const int &newVal) {
    if(!right){
        right = new Node(newVal);
    }
    else{
        right->setVal(newVal);
    }
}
/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(const int &rootValue):root(new Node(rootValue)){
}

BinaryTree::BinaryTree(Node *node):root(node){
}

//REQUIRES: a input source tree root node
//EFFECTS: returns a root node for the tree
Node* copyNodeHelper(const Node* source){
    if(!source){
        return nullptr;
    }
    Node * newNode = new Node(source->getVal(), copyNodeHelper(source->getLeft()),
                                copyNodeHelper(source->getRight()));
    return newNode;
}


BinaryTree::BinaryTree(const BinaryTree &tree) {
    this->root = copyNodeHelper(tree.root);
}

BinaryTree::BinaryTree(std::vector<nodeValue> &source) {
    this->root = createFromVariant(source, 0);
}

//REQUIRES: a input source tree root node
//MODIFIES: the input tree
//EFFECTS: delete the tree
void deleteHelper(Node * node){
    if(node){
        deleteHelper(node->getLeft());
        deleteHelper(node->getRight());
        delete node;
    }
}

BinaryTree::~BinaryTree() {
    deleteHelper(this->root);
}

bool BinaryTree::empty() const {
    return !root;
}

//REQUIRES: a input source tree root node and the target key
//EFFECTS: return nullptr if not found or the node with the target key if found
Node* findHelper(const int &key, Node * node){
    if(!node){return nullptr;}
    if(node->getVal() == key){return node;}
    else{
        Node* left = findHelper(key, node->getLeft());
        if(left){return left;}
        Node* right = findHelper(key, node->getRight());
        if(right){return right;}
    }
    return nullptr;
}

Node *BinaryTree::find(const int &key) const {
    if(!this->root){
        return nullptr;
    }
    return findHelper(key, this->root);
}

//REQUIRES: a input source tree root node and the target key
//EFFECTS: return "" if not found or path to the node with the val
bool findPathHelper(const int &value, Node * node, std::string & output){
    if(!node){return false;}
    if(node->getVal() == value){return true;}
    output.push_back('0');
    if(findPathHelper(value, node->getLeft(), output)){return true;}
    output.pop_back();
    output.push_back('1');
    if(findPathHelper(value, node->getRight(), output)){return true;}
    output.pop_back();
    return false;
}

std::string BinaryTree::findPath(const int &value) const {
    std::string output;
    findPathHelper(value, this->root, output);
    return output;
}

//REQUIRES: a input source tree root node and a path
//EFFECTS: return nullptr if not found or the node reachable from the path
Node * visitThroughHelper(string &path, Node *node){
    if(path.empty() && node){return node;}
    else if(node && (!path.empty())){
        char next = path.back();
        path.pop_back();
        if(next == '0'){return visitThroughHelper(path, node->getLeft());}
        else if(next == '1'){return visitThroughHelper(path, node->getRight());}
    }
    return nullptr;
}

Node *BinaryTree::visitThroughPath(const string &path) const {
    if(path.empty()){
        return this->root;
    }
    string tmpPath = path;
    reverse(tmpPath.begin(), tmpPath.end());
    return visitThroughHelper(tmpPath, this->root);
}

//REQUIRES: a input source tree root node
//EFFECTS: return sum of the nodes in a tree
int sumHelper(Node * node){
    if(!node){
        return 0;
    }
    return node->getVal() + sumHelper(node->getLeft()) + sumHelper(node->getRight());
}

int BinaryTree::sum() const {
    return sumHelper(this->root);
}

//REQUIRES: a input source tree root node
//EFFECTS: return height of a tree
int heightHelper(Node * node){
    if(!node){return 0;}
    int lDepth = heightHelper(node->getLeft());
    int rDepth = heightHelper(node->getRight());
    if (lDepth < rDepth){
        return(heightHelper(node->getRight()) + 1);
    }
    else{
        return(heightHelper(node->getLeft()) + 1);
    }
}

int BinaryTree::height() const {
    return heightHelper(this->root);
}

//REQUIRES: a input source tree root node
//EFFECTS: return the preorder traversal results
void preOrderHelper(Node * node){
    if(!node){
        return;
    }
    cout << node->getVal() << " ";
    preOrderHelper(node->getLeft());
    preOrderHelper(node->getRight());
}

void BinaryTree::preOrder() const {
    preOrderHelper(this->root);
    cout << endl;
}

//REQUIRES: a input source tree root node
//EFFECTS: return the inorder traversal results
void inOrderHelper(Node * node){
    if(!node){
        return;
    }
    inOrderHelper(node->getLeft());
    cout << node->getVal() << " ";
    inOrderHelper(node->getRight());
}

void BinaryTree::inOrder() const {
    inOrderHelper(this->root);
    cout << endl;
}

//REQUIRES: a input source tree root node
//EFFECTS: return the postorder traversal results
void postOrderHelper(Node * node){
    if(!node){
        return;
    }
    postOrderHelper(node->getLeft());
    postOrderHelper(node->getRight());
    cout << node->getVal() << " ";
}

void BinaryTree::postOrder() const {
    postOrderHelper(this->root);
    cout << endl;
}

//REQUIRES: a input source tree root node and the sum bar
//EFFECTS: return true if the sum along any path is larger than the bar and false otherwise
bool pathSumGreaterHelper(int sum, Node * node){
    if(!node){
        return true;
    }
    if(!node->getLeft() && !node->getRight()){
        return node->getVal() > sum;
    }
    return pathSumGreaterHelper(sum - node->getVal(), node->getLeft()) &&
            pathSumGreaterHelper(sum - node->getVal(), node->getRight());
}

bool BinaryTree::allPathSumGreater(const int &sum) const {
    int tmpSum = sum;
    return pathSumGreaterHelper(tmpSum, this->root);
}

//REQUIRES: a input source tree root node and the tree to test again
//EFFECTS: return true if the tree is covered by the tested-again tree and false otherwise
bool coverHelper(Node * thisNode, Node * thatNode){
    if(!thisNode && !thatNode){return true;}
    else if(!thisNode && thatNode){return true;}
    else if(thatNode == nullptr && thisNode){return false;}
    else if(thisNode->getVal() != thatNode->getVal()){return false;}
    return coverHelper(thisNode->getLeft(), thatNode->getLeft()) &&
            coverHelper(thisNode->getRight(), thatNode->getRight());
}

bool BinaryTree::operator<(const BinaryTree &tree) const {
    return coverHelper(this->root, tree.root);
}

//REQUIRES: a input source tree root node and the tree to test again
//EFFECTS: return true if the tree is contained by the tested-again tree and false otherwise
bool containHelper(Node * thisnode, Node * thatnode){
    if(!thatnode){
        return false;
    }
    if(coverHelper(thisnode, thatnode)){
        return true;
    }
    return containHelper(thisnode, thatnode->getLeft()) || containHelper(thisnode, thatnode->getRight());
}

bool BinaryTree::operator<<(const BinaryTree &tree) const {
    return containHelper(this->root, tree.root);
}

BinaryTree &BinaryTree::operator=(const BinaryTree &tree) {
    deleteHelper(this->root);
    this->root = copyNodeHelper(tree.root);
    return *this;
}

Node *BinaryTree::createFromVariant(const vector<nodeValue> &source, const int &rootIndex) {
    if (rootIndex >= source.size())
        return nullptr;
    auto rootValue = get_if<int>(&source[rootIndex]);
    if (!rootValue)
        return nullptr;
    int rightIndex = 2 * (rootIndex + 1);
    int leftIndex = rightIndex - 1;
    return new Node(*rootValue, createFromVariant(source, leftIndex), createFromVariant(source, rightIndex));
}
