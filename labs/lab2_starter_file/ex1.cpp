#include <iostream>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime() {
    // TODO: implement Eratosthenes Sieve Algorithm
    for (int i = 0; i < RANGE + 1; i++){
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;
    for (int smallest = 2; smallest * smallest < RANGE + 1; smallest++){
        if (isPrime[smallest]){
            for (int tmp = smallest * smallest; tmp < RANGE + 1; tmp += smallest){
                isPrime[tmp] = false;
            }
        }
    }
}

int main() {
    // TODO: generate lookup table
    generateIsPrime();
    // TODO: read input and check if each num is prime
    int size;
    int input[RANGE] = {0};
    cin >> size;
    for (int i = 0; i < size; ++i){
        cin >> input[i];
    }
    for (int i = 0; i < size; i++){
        if (isPrime[input[i]]){
            cout << input[i] << " ";
        }
    }
    return 0;
}