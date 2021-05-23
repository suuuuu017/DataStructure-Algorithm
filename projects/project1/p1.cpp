#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

void print_prompt() {
    std::cout << "Please enter the integer and the test number: ";
}

bool armstrongNum(int num){

}

bool cycloneJet(int num) {

}

bool blackPremium(int num){

}

bool auspiciousNum(int num){

}

int main() {
    //TODO: write your code here
    bool rangeCheck = false;
    bool opCheck = false;
    int integer;
    int op;
    while (!(rangeCheck && opCheck)){
        print_prompt();
        std::cin >> integer >> op;
        if((0 <= integer) && (integer <= 10000000)){
            rangeCheck = true;
        }
        if((1 <= op) && (op <= 4)){
            opCheck = true;
        }
    }
    return 0;
}
