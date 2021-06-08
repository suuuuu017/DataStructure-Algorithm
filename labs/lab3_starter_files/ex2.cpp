/*
 * VE280 Lab 3, SU2021.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;
const int winning = 280;

bool canWin_helper(bool visit[], int count, int card[], int position){
    visit[position] = true;
    if(card[position] == winning){
        return true;
    }
//    else if((position + card[position] < count) && (! visit[position + card[position]])){
//        canWin_helper(visit, count, card, position + card[position]);
//    }
//    else if((position - card[position] >= 0) && (! visit[position - card[position]])){
//        canWin_helper(visit, count, card, position - card[position]);
//    }
    return false;
}

bool canWin(int count, int arr[], int position) {
    // EFFECTS: return whether the player can win given the start position
    // and the card sequence
    
    // TODO: implement this function
    bool visit[MAXSIZE] = {false};
    return canWin_helper(visit, count, arr, position);
}


int main() {
    int count;
    cin >> count;
    int arr[MAXSIZE];
    for (int i = 0; i < count; ++i) {
        cin >> arr[i];
    }
    int position;
    cin >> position;
    cout << canWin(count, arr, position);
}