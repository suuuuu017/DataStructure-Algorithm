#include "node.h"
#include <iostream>

void Node::addChild(Node *child) {
//    std::cout << "add node " << child->value << std::endl;
    if(child_num >= n){
        throw tooManyChildren();
    }
    else{
//        std::cout << "start with " << child_num << std::endl;
        this->children[child_num] = child;
        this->children[child_num]->parent = this;
        if(this->height == 0){
            this->height = this->height + 1;
            Node * tmpNode = this->parent;
            while(tmpNode){
                tmpNode->height = tmpNode->height + 1;
                tmpNode = tmpNode->parent;
            }
        }
        child_num = child_num + 1;
    }

//    std::cout << child_num << std::endl;
}

bool Node::equal(Node *sub) {
//    if(this == nullptr && sub ==nullptr){
//        return true;
//    }
//    std::cout << "equal" << sub->value << std::endl;
    if(this->child_num == sub->child_num){
        if(this->value == sub->value){
            for(int i = 0; i < child_num; i++){
                if(!this->children[i]->equal(sub->children[i])){
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

Node::Node(int _value, int _n): value(_value), child_num(0), n(_n), parent(nullptr),
                                                                                   children(new Node*[n]), height(0){
//    std::cout << "root start with" << child_num << std::endl;
}

Node::~Node() {
    for(int i = 0; i < child_num; i++){
//        children[i] -> ~Node();
        delete children[i];
    }
    delete [] children;
}

void Node::addChild(int _value) {
//    std::cout << "add val " << _value << std::endl;
    if(child_num >= n){
        throw tooManyChildren();
    }
    Node * newNode = new Node(_value, n);
    this->addChild(newNode);
}

void Node::traverse(vector<int> &traverseValue) {
    traverseValue.push_back(this->value);
    for(int i = 0; i < child_num; i++){
//        traverseValue.push_back(children[i]->value);
        children[i]->traverse(traverseValue);
    }
}

bool Node::contain(Node *sub) {
//    std::cout << "contain " << std::endl;
    if(this->value == sub->value){
        if(this->equal(sub)){
            return true;
        }
    }
    for(int i = 0; i < child_num; i++){
        if(children[i]->contain(sub)){
            return true;
        }
    }
    return false;
}

int Node::getHeight() {
//    std::cout << "height " << std::endl;
    return height;
}

Node &Node::operator[](int i) {
    if(i >= child_num){
        throw invalidIndex();
    }
    else{
        return *children[i];
    }
}






