#include "deck.h"
#include <iostream>

void suf(Deck &d, int n){
    d.shuffle(n);
}

int main(){
    Deck d = Deck();
    suf(d, 10);
    for(int i = 0; i < 52; i ++){
        std::cout << d.deck[i].suit << " " << d.deck[i].spot << std::endl;
    }
    std::cout << " shuffle 1 and reset" << std::endl;
    d.reset();
    for(int i = 0; i < 52; i ++){
        std::cout << d.deck[i].suit << " " << d.deck[i].spot << std::endl;
    }
};