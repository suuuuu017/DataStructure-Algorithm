//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    Node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template<class T>
bool List<T>::isEmpty() const {
    return (!first);
}

template<class T>
void List<T>::insertBack(T val) {
    Node_t<T> *np = new Node_t<T>;
    np->next = NULL;
    np->val = val;
    if(isEmpty()){
        first = last = np;
    }
    else{
        last->next = np;
        last = np;
    }
}

template<class T>
T List<T>::removeFront() {
    if(isEmpty()){
        EmptyList e;
        throw e;
    }
    Node_t<T> *victim = first;
    first = victim->next;
    T result = victim->val;
    delete victim;
    return result;
}

template<class T>
List<T>::List(): first(nullptr), last(nullptr) {
}

template<class T>
void List<T>::removeAll() {
    while(!isEmpty()){
        removeFront();
    }
}

template<class T>
List<T>::~List() {
    removeAll();
}

template<class T>
void copyHelper(Node_t<T> *node, List<T> *l){
    if(!node){
        return;
    }
    l->insertBack(node->val);
    copyHelper(node->next, l);
}

template<class T>
void List<T>::copyFrom(const List &l) {
    removeAll();
    copyHelper(l.first, this);
}

template<class T>
List<T>::List(const List &l) {
    first = nullptr;
    last = nullptr;
    copyFrom(l);
}

template<class T>
List<T> &List<T>::operator=(const List &l) {
    copyFrom(l);
    return *this;
}

template<class T>
const Node_t<T> *List<T>::returnFront() const {
    return first;
}

bool isLarger(const List<int> &a, const List<int> &b) {
    List<int> duplicateA(a);
    List<int> duplicateB(b);
    if(duplicateA.isEmpty() && duplicateB.isEmpty()){
        return false;
    }
    int sumA = 0;
    int sumB = 0;
    int aC = 1;
    int bC = 1;
    while(!duplicateA.isEmpty()){
        sumA = sumA + aC * duplicateA.removeFront();
        aC = aC * 10;
    }
    while(!duplicateB.isEmpty()){
        sumB = sumB + bC * duplicateB.removeFront();
        bC = bC * 10;
    }
    return (sumA > sumB);
}

List<int> add(const List<int> &a, const List<int> &b) {
    List<int> duplicateA(a);
    List<int> duplicateB(b);
    List<int> result;
    int sum = 0;
    int carry = 0;

    while(!duplicateA.isEmpty() || !duplicateB.isEmpty()){
        if(duplicateA.isEmpty()){
            result.insertBack(carry + duplicateB.removeFront());
            carry = 0;
        }
        else if(duplicateB.isEmpty()){
            result.insertBack(carry + duplicateA.removeFront());
            carry = 0;
        }
        else if(!duplicateA.isEmpty() && !duplicateB.isEmpty()){
            sum = duplicateA.removeFront() + duplicateB.removeFront() + carry;
            if(sum >= 10){
                carry = 1;
                sum = sum - 10;
            }
            else{
                carry = 0;
            }
            result.insertBack(sum);
            sum = 0;
        }
    }
    if(carry == 1){
        result.insertBack(carry);
    }
    return result;
}

#endif //INTLIST_IMPL_H
