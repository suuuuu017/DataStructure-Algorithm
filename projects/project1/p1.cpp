#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

void print_prompt() {
    std::cout << "Please enter the integer and the test number: ";
}

bool armstrongNum(int num){
    int i = 1;
    while(i < num){
        long tmp = 1;
        for(int j = 1; j <= num; j ++){
            tmp = tmp * i % num;
        }
        if(tmp != i){
            return false;
        }
        i = i + 1;
    }
    return true;
//TODO: check if i need to add 0.5 after the pow
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
    float x = 0.0;
    x = (sqrt(24.0 * num + 1.0) + 1.0) / 6.0;
    if(int(x) == x){
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
    while (true){
        print_prompt();
        std::cin >> integer >> op;
        //TODO: what if the input is a string and an op, why nonstop print
        if((0 <= integer) && (integer <= 10000000)){
            rangeCheck = true;
        }
        if((1 <= op) && (op <= 4)){
            opCheck = true;
        }
        if(rangeCheck && opCheck){
            break;
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
