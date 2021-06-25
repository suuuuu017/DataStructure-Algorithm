//
// Created by Zhuoer Zhu on 10/06/2020.
// Updated by Yanjun Chen on 16/06/2021.
//

#include <cmath>
#include "standardForm.h"
#include <iostream>

QuadraticFunction::QuadraticFunction(float a_in, float b_in, float c_in): a(a_in), b(b_in), c(c_in){}
// TODO: implement this constructor

float QuadraticFunction::getA() const {
    return a;
}

float QuadraticFunction::getB() const {
    return b;
}

float QuadraticFunction::getC() const {
    return c;
}

float QuadraticFunction::evaluate(float x) {
    // TODO: implement this function
    float result = 0;
    result = a * pow(x, 2)+ x * b + c;
    return result;
}

Root QuadraticFunction::getRoot() {
    // TODO: implement this function
    Root root;
    float delta = pow(b, 2) - 4 * a * c;
    if(delta > 0){
        if(a > 0){
            root.roots[0].real = (-1 * b - sqrt(delta)) / (2 * a);
            root.roots[1].real = (-1 * b + sqrt(delta)) / (2 * a);
        }
        else{
            root.roots[0].real = (-1 * b + sqrt(delta)) / (2 * a);
            root.roots[1].real = (-1 * b - sqrt(delta)) / (2 * a);
        }

        root.roots[0].imaginary = 0;
        root.roots[1].imaginary = 0;
        root.realRootNum = 2;
    }
    else if(delta == 0){
        root.roots[0].real = (-1 * b)/ (2 * a);
        root.roots[1].real = (-1 * b) / (2 * a);
        root.roots[0].imaginary = 0;
        root.roots[1].imaginary = 0;
        root.realRootNum = 1;
    }
    else if(delta < 0){
        root.roots[0].real = (-1 * b)/ (2 * a);
        root.roots[1].real = (-1 * b) / (2 * a);
        if(a > 0){
            root.roots[0].imaginary = -(sqrt(-1 * delta))/ (2 * a);
            root.roots[1].imaginary = (sqrt(-1 * delta))/ (2 * a);
        }
        else if(a < 0){
            root.roots[0].imaginary = (sqrt(-1 * delta))/ (2 * a);
            root.roots[1].imaginary = -(sqrt(-1 * delta))/ (2 * a);
        }
        root.realRootNum = 0;
    }
    return root;
}

bool QuadraticFunction::intersect(QuadraticFunction q){
    // TODO: implement this function
    if((a - q.getA()) == 0){
        if((b - q.getB()) != 0){
            return true;
        }
        else if((b - q.getB()) == 0){
            if((c - q.getC() == 0)){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        QuadraticFunction n(a - q.getA(), b - q.getB(), c - q.getC());
        Root nRoot = n.getRoot();
        if(nRoot.realRootNum > 0){
            return true;
        }
        else{
            return false;
        }
    }
    return false;

}