/*
 * VE280 Lab 3, SU2021.
 * Written by Guoxin Yin
 */

#include <iostream>

using namespace std;

const int MAXSIZE = 10;
const int winning = 280;

bool canWin_helper(bool visit[], int count, int card[], int position){
    if(card[position] == winning){
        visit[position] = true;
        return true;
    }
    else if (visit[position] || position >= count || position < 0){
        return false;
    }
    else{
        visit[position] = true;
        return canWin_helper(visit, count, card, position + card[position]) ||
                canWin_helper(visit, count, card, position - card[position]);
    }

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