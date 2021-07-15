#include <iostream>
#include "constant.h"
#include "node.h"

int main(){
    Node root = Node(0, 2);
    root.addChild(1);
    root.addChild(3);
    root[0].addChild(2);
    root[1].addChild(4);
    root[1][0].addChild(5);
    root[1][0][0].addChild(6);
    root[1][0].addChild(7);
    root[1][0][1].addChild(8);
    root[1][0][1].addChild(9);
    root[1][0][1][1].addChild(10);

    vector<int> traverseValue;
    root.traverse(traverseValue);
    for(auto i = traverseValue.begin(); i != traverseValue.end(); i++){
//        std::cout << *i << std::endl;
        std::cout << storyProcess[*i] << std::endl;
//        traverseValue.pop_back();
    }

}
