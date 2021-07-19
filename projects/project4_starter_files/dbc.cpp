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
//        c = input.get();
        longestString.push_back(c);
//        Node * node = compressTree.visitThroughPath(longestString);
        if(compressTree.visitThroughPath(longestString) && (input.peek() == EOF)){
//            Node * node = compressTree.visitThroughPath(longestString);
//            std::cout << "find node";
//            std::cout << longestString << std::endl;
//            std::cout << "here " << std::endl;
            Node * lastNode = compressTree.visitThroughPath(longestString);
            NodeInfo node(lastNode->getVal(), '@');
            std::cout << node;
            continue;
        }
        else if(!compressTree.visitThroughPath(longestString)){
//            std::cout << "longest string is " << longestString << std::endl;
//            std::cout << longestString << std::endl;
            char lastDigit = longestString.back();
//            std::cout << "last digit is" << lastDigit << std::endl;
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
    std::cout << std::endl;
//    compressTree.inOrder();
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
        std::istringstream ss(str);
        compress(ss);
        fs.close();
//        std::cout << std::endl;
    }
    return 0;
}