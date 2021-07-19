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
        if(compressTree.visitThroughPath(longestString) && (input.peek() == EOF)){
            Node * lastNode = compressTree.visitThroughPath(longestString);
            NodeInfo node(lastNode->getVal(), '@');
            std::cout << node;
            continue;
        }
        else if(!compressTree.visitThroughPath(longestString)){
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
//    std::cout << std::endl;
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
    }
    return 0;
}