/*
 * This is an exercise of VE280 Lab 1, SU2020.
 * Written by Martin Ma.
 * Latest Update: 5/10/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#include <iostream>
#include <string.h>
using namespace std;


// EFFECTS: return true if the password is a valid one
bool isValidPassword(char password[]){
    // TODO: Implement this function.
    if(strlen(password) > 50){
        return false;
    }
    bool alphabetic = false;
    bool numerical = false;
    bool other = false;
    int i = 0;
    while(i < strlen(password)){
        if(isalpha(password[i])){
            alphabetic = true;
        }
        else if(isdigit(password[i])){
            numerical = true;
        }
        else{
            other = true;
        }
        i++;
    }
    return alphabetic && numerical && other;
}


int main(){
    char password[50] = {};
    cin >> password;
    cout << isValidPassword(password) << endl;
}
