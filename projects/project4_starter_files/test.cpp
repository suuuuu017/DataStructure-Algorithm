//
// Created by 吴佳遥 on 2021/7/7.
//
#include <iostream>
#include "BinaryTree.h"
#include <vector>

using namespace std;

void treeCheck(const BinaryTree &tree) {
    cout << tree.height() << endl;
    cout << tree.sum() << endl;
    cout << tree.empty() << endl;
    tree.preOrder();
    tree.inOrder();
    tree.postOrder();
}

void nodePrint(Node *x) {
    if (x == nullptr)
        cout << "nullptr" << endl;
    else
        cout << x->getVal() << endl;
}

int main() {
//    vector<nodeValue> source = {4, 2, 5, 7, 3, "$", "@", "hey", "xm", 8, 9};
    vector<nodeValue> source = {1, 2, 3, 4, 5, "!", 6, 7, 8, 9, "?", 10, 11};
    BinaryTree tree(source);
//    BinaryTree waste(tree);
//    treeCheck(tree);
//
//    Node *x = tree.findPath(12);
    cout << tree.findPath(12) << endl;
//    x->setLeft(100);
//    cout <<"path to 100 " <<  tree.findPath(100) << endl;
//
//    treeCheck(tree);
//    treeCheck(waste);
//
//    x = tree.visitThroughPath("0110");
//    nodePrint(x);
//
//    x = tree.visitThroughPath("001");
//    nodePrint(x);
//
//    x = tree.find(7);
//    x->setRight(101);
//
//    x = tree.visitThroughPath("0001");
//    nodePrint(x);
//    treeCheck(waste);
//
//    x = tree.find(101);
//    x->setLeft(102);
//
////    cout <<"path to 102 " <<  tree.findPath(102) << endl;
//    vector<nodeValue> coveredVec = {4, 2, 5};
////    vector<nodeValue> coveredVec = {3, 6, 7};
//    vector<nodeValue> uncoveredVec1 = {4, 3};
//    vector<nodeValue> uncoveredVec2 = {5};
////    vector<nodeValue> uncoveredVec = {3, "!", 7};
//    vector<nodeValue> coveredTargetVec = {4, 2, 5, "", 3};
//    BinaryTree covered(coveredVec);
//    BinaryTree uncovered1(uncoveredVec1);
//    BinaryTree uncovered2(uncoveredVec2);
//    BinaryTree coveredTarget(coveredTargetVec);
//    cout << "cover " << (covered < coveredTarget) << endl;
//    cout << "uncover1 " << (uncovered1 < coveredTarget) << endl;
//    cout << "uncover2 " << (uncovered2 < coveredTarget) << endl;
//
//    vector<nodeValue> containedVec = {3, 6, 7};
//    vector<nodeValue> notContainedVec1 = {4, 2, 5, "", 3, 7, 8};
//    vector<nodeValue> notContainedVec2 = {3, "!", 7};
//    vector<nodeValue> containedTargetVec = {4, 2, 5, "", 3, "", 8, "", "", 6, 7};
//    BinaryTree contained(containedVec);
//    BinaryTree notContained1(notContainedVec1);
//    BinaryTree notContained2(notContainedVec2);
//    BinaryTree containedTarget(containedTargetVec);
//    cout << "contained " << (contained << containedTarget) << endl;
//    cout << "notcontained1 " << (notContained1 << containedTarget) << endl;
//    cout << "contained2 " << (notContained2 << containedTarget) << endl;
//
//    vector<nodeValue> sumGreaterVec = {4, 1, 5, 3, 6};
//    BinaryTree sumGreater(sumGreaterVec);
//    cout << sumGreater.allPathSumGreater(9) << endl;
//    cout << sumGreater.allPathSumGreater(7) << endl;
}
