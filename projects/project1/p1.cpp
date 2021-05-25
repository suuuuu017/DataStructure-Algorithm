#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

void print_prompt() {
    std::cout << "Please enter the integer and the test number: ";
}

int* binaryList(int num) {
    int * binaryNum = new int[32];
    int count = 0;
    for(int i = 0; i < 32; i ++){
        binaryNum[i] = 0;
    }
    while (num > 0) {
        binaryNum[count] = num % 2;
        num = num / 2;
        count++;
    }
    return binaryNum;
}

int partialMod(int* binaryNum, int b, int n){
    int last = 0;
    int next = 0;
    int mod = 0;
    for(int i = 0; i < 32; i++){
        if(binaryNum[i]){
            last = i;
            int tmp = int(pow(2, last) + 0.5);
            mod = int(pow(b, tmp) + 0.5) % n;
            break;
        }
    }
    int i = last + 1;
    for(int j = i; j < 32; j ++){
        if(binaryNum[j] == 1){
            next = j;
            int newmod = mod;
            for(int c = 0; c < next - last; c = c + 1){
                newmod = ( newmod * mod ) % n;
            }
            mod = ( mod * newmod ) % n;
        }
        last = next;
    }
    return mod;
}

bool armstrongNum(int num){
    int i = 1;
    while(i < num){
        int* l = binaryList(num);
        int ans = partialMod(l, i, num);
        if(ans == i){
            i = i + 1;
        }
        else{
            return false;
        }
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
