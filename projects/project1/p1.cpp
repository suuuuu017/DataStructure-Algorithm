#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

void print_prompt() {
    std::cout << "Please enter the integer and the test number: ";
}

bool armstrongNum(int num){
    int i = 0;
    while(i < num){
        if((i ^ num % num) == i){
            i = i + 1;
        }
        else{
            return false;
        }
    }
    return true;
}

bool cycloneJet(int num) {
    int j = num;
    int rev = 0;
    while(j > 0){
        rev = rev * 10 + j % 10;
        j = j / 10;
    }
    if(rev == num){
        return true;
    }
    else{
        return false;
    }
}

bool blackPremium(int num){
    int x = 0;
    x = (sqrt(24 * num + 1) + 1) / 6.0;
    if(isdigit(x)){
        return true;
    }
    else{
        return false;
    }
}

bool auspiciousNum(int num){
    int sum = 0;
    for (int i=2; i <= sqrt(num); i++){
        if (num % i == 0){
            if (num / i == i){
                sum = sum + i;
            }
            else{
                sum = sum + i + num / i;
            }
        }
    }
    sum = sum + 1;
    if(sum > num){
        return true;
    }
    else{
        return false;
    }
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
    if(op == 1){
        std::cout << armstrongNum(integer);
    }
    if(op == 2){
        std::cout << cycloneJet(integer);
    }
    if(op == 3){
        std::cout << blackPremium(integer);
    }
    if(op == 4){
        std::cout << auspiciousNum(integer);
    }
    return 0;
}
