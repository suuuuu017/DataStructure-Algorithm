#include "BinaryTree.h"
#include <iostream>
#include <vector>

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
    //use visit order function
}

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

Node* findHelper(const int &key, Node * node){
    if(!node){
        return nullptr;
    }
    if(node->getVal() == key){
        return node;
    }
    else{
        Node* left = findHelper(key, node->getLeft());
        if(left){
            return left;
        }
        Node* right = findHelper(key, node->getRight());
        if(right){
            return right;
        }
    }
    return nullptr;
}

Node *BinaryTree::find(const int &key) const {
    if(!this->root){
        return nullptr;
    }
    return findHelper(key, this->root);
}

bool findPathHelper(const int &value, Node * node, std::string & output){
    if(!node){
        return false;
    }
    if(node->getVal() == value){
        return true;
    }
    output.push_back('0');
    if(findPathHelper(value, node->getLeft(), output)){
        return true;
    }
    output.pop_back();
    output.push_back('1');
    if(findPathHelper(value, node->getRight(), output)){
        return true;
    }
    output.pop_back();
    return false;
}

std::string BinaryTree::findPath(const int &value) const {
    std::string output;
    findPathHelper(value, this->root, output);
}

Node * visitThroughHelper(const string &path, Node *node){

}

Node *BinaryTree::visitThroughPath(const string &path) const {
    if(path.empty()){
        return this->root;
    }

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