#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include "Dlist.h"

template<class T>
bool Dlist<T>::isEmpty() const {
    return !this->first;
}

template<class T>
void Dlist<T>::insertFront(T * op) {
    node * np = new node;
    np->op = op;
    np->next = first;
    np->prev = nullptr;
    if(this->isEmpty()){
        first = last = np;
    }
    else{
        first->prev = np;
        first = np;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    node * np = new node;
    np->op = op;
    np->next = nullptr;
    np->prev = last;
    if(this->isEmpty()){
        first = last = np;
    }
    else{
        last->next = np;
        last = np;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if(this->isEmpty()){
        throw EmptyList();
    }
    node * victim = first;
    T * result = victim->op;
    first = victim->next;
    if(!first){
        last = nullptr;
//        return result;
    }
    else{
        first->prev = nullptr;
    }
//    delete victim->op;
    //TODO: do i have to delete the victim->op?
    delete victim;
    return result;
}

template<class T>
T *Dlist<T>::removeBack() {
    if(this->isEmpty()){
        throw EmptyList();
    }
    else{
        node * victim = last;
        T * result = victim->op;
        last = victim->prev;
        if(!last){
            first = nullptr;
        }
        else{
            last->next = nullptr;
        }
//        delete victim->op;
        delete victim;
        return result;
    }
}

template<class T>
void Dlist<T>::removeAll() {
    while(!isEmpty()){
        delete removeFront();
    }
}

template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template<class T>
Dlist<T>::Dlist(): first(0), last(0) {
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    node * tmp = l.first;
    while(tmp){
        T * tmpOp = new T(*(tmp->op));
        insertBack(tmpOp);
        tmp = tmp->next;
    }
}

template<class T>
Dlist<T>::Dlist(const Dlist &l): first(0), last(0) {
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if(!isEmpty()){
        removeAll();
    }
    copyAll(l);
    return *this;
}

#endif




