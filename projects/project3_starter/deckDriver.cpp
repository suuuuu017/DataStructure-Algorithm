#include "deck.h"
#include <iostream>

int main(){
    Deck d = Deck();
    d.shuffle(26);
    for(int i = 0; i < 52; i ++){
        std::cout << d.deck[i].suit << " " << d.deck[i].spot << std::endl;
    }
    std::cout << " shuffle 26 and rest" << std::endl;
    d.reset();
    for(int i = 0; i < 52; i ++){
        std::cout << d.deck[i].suit << " " << d.deck[i].spot << std::endl;
    }
};