//
// Created by Zhuoer Zhu on 10/06/2020.
// Updated by Yanjun Chen on 16/06/2021.
//

#include "factoredForm.h"
#include <iostream>

QuadraticFunction::QuadraticFunction(float a_in, float b_in, float c_in){
    float a1 = a_in;
    float b1 = b_in;
    float c1 = c_in;
    float delta = pow(b1, 2) - 4 * a1 * c1;
    Root root;
    root.roots[0].real = 0;
    root.roots[0].imaginary = 0;
    root.roots[1].real = 0;
    root.roots[1].imaginary = 0;
    r1.real = 0;
    r1.imaginary = 0;
    r2.real = 0;
    r2.imaginary = 0;
    if(delta > 0){
        if(a > 0){
            root.roots[0].real = (-1 * b1 - sqrt(delta)) / (2 * a1);
            root.roots[1].real = (-1 * b1 + sqrt(delta)) / (2 * a1);
        }
        else{
            root.roots[0].real = (-1 * b1 + sqrt(delta)) / (2 * a1);
            root.roots[1].real = (-1 * b1 - sqrt(delta)) / (2 * a1);
        }

        root.roots[0].imaginary = 0;
        root.roots[1].imaginary = 0;
        root.realRootNum = 2;
    }
    else if(delta == 0){
        root.roots[0].real = (-1 * b1)/ (2 * a1);
        root.roots[1].real = (-1 * b1) / (2 * a1);
        root.roots[0].imaginary = 0;
        root.roots[1].imaginary = 0;
        root.realRootNum = 1;
    }
    else if(delta < 0){
        root.roots[0].real = (-1 * b1)/ (2 * a1);
        root.roots[1].real = (-1 * b1) / (2 * a1);
        if(a > 0){
            root.roots[0].imaginary = -(sqrt(-1 * delta))/ (2 * a1);
            root.roots[1].imaginary = (sqrt(-1 * delta))/ (2 * a1);
        }
        else if(a < 0){
            root.roots[0].imaginary = (sqrt(-1 * delta))/ (2 * a1);
            root.roots[1].imaginary = -(sqrt(-1 * delta))/ (2 * a1);
        }
        root.realRootNum = 0;
    }
    a = a_in;
    r1.real = root.roots[0].real;
    r1.imaginary = root.roots[0].imaginary;
    r2.real = root.roots[1].real;
    r2.imaginary = root.roots[1].imaginary;
}
// TODO: implement this constructor

float QuadraticFunction::getA() const {
    return a;
}

float QuadraticFunction::getB() const {
    // TODO: implement this function
    float b = (r1.real + r2.real) * a * (-1);
    return b;
}

float QuadraticFunction::getC() const {
    // TODO: implement this function
    float c = (r1.real * r2.real - r1.imaginary * r2.imaginary) * a;
    return c;
}

float QuadraticFunction::evaluate(float x) {
    // TODO: implement this function
    float a = getA();
    float b = getB();
    float c = getC();
    float result = 0;
    result = a * pow(x, 2) + b * x + c;
    return result;
}

Root QuadraticFunction::getRoot() {
    // TODO: implement this function
    Root root;
    root.roots[0].real = r1.real;
    root.roots[0].imaginary = r1.imaginary;
    root.roots[1].real = r2.real;
    root.roots[1].imaginary = r2.imaginary;
    if((pow(getB(), 2) - 4 * getA() * getC()) > 0){
        root.realRootNum = 2;
    }
    else if((pow(getB(), 2) - 4 * getA() * getC()) == 0){
        root.realRootNum = 1;
    }
    else{
        root.realRootNum = 0;
    }
    return root;
}

bool QuadraticFunction::intersect(QuadraticFunction q) {
    // TODO: implement this function
    if((a - q.getA()) == 0){
        if((getB() - q.getB()) != 0){
            return true;
        }
        else if((getB() - q.getB()) == 0){
            if((getC() - q.getC() == 0)){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else{
        QuadraticFunction n(a - q.getA(), getB() - q.getB(), getC() - q.getC());
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