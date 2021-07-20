#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include "BinaryTree.h"
#include "NodeInfo.h"

void compress(std::istringstream& input){
    BinaryTree compressTree(0);

    std::string longestString;
    int nodeIndex = 0;
    char c;
    while(input.get(c)){
        longestString.push_back(c);
        if(compressTree.visitThroughPath(longestString)){
//            Node * lastNode = compressTree.visitThroughPath(longestString);
//            NodeInfo node(lastNode->getVal(), '@');
////            std::cout << "here " << std::endl;
//            std::cout << node;
            continue;
        }
        else if(!compressTree.visitThroughPath(longestString)){
//            std::cout << "here " << longestString << std::endl;
            char lastDigit = longestString.back();
            longestString.pop_back();
            Node * lastNode = compressTree.visitThroughPath(longestString);
            if(lastDigit == '1'){
                nodeIndex = nodeIndex + 1;
                lastNode->setRight(nodeIndex);
            }
            else if(lastDigit == '0'){
                nodeIndex = nodeIndex + 1;
                lastNode->setLeft(nodeIndex);
            }
            NodeInfo node(lastNode->getVal(), lastDigit);
            std::cout << node;
            longestString = "";
        }
    }
    Node * lastNode = compressTree.visitThroughPath(longestString);
    NodeInfo node(lastNode->getVal(), '@');
//    std::cout << "here " << std::endl;
    std::cout << node;
//    std::cout << std::endl;

}

void decompress(std::istringstream& input){
    BinaryTree decompressTree(0);
    int index = 0;
    while(input.peek() != EOF){
        NodeInfo node;
        input >> node;
        int key = node.node_index;
        Node * parent = decompressTree.find(key);
        char info = node.c;
        if(info == '0'){
            index = index + 1;
            parent->setLeft(index);
            std::cout << decompressTree.findPath(index);
        }
        else if(info == '1'){
            index = index + 1;
            parent->setRight(index);
            std::cout << decompressTree.findPath(index);
        }
        else if(info == '@'){
            std::cout << decompressTree.findPath(node.node_index);
        }
    }
}

int main(int argc, char *argv[]){
    // TODO: implement your dbc program here!
    std::string option = argv[1];
    std::string filePath = argv[2];

    if(option == "-x"){
        std::fstream fs;
        fs.open(filePath);
        std::string str;
        getline(fs, str);
//        std::cout << str << std::endl;
        std::istringstream ss(str);
        compress(ss);
        fs.close();
    }
    else if(option == "-d"){
        std::fstream fs;
        fs.open(filePath);
        std::string str;
        getline(fs, str);
        std::istringstream ss(str);
        decompress(ss);
        fs.close();
    }
    return 0;
}