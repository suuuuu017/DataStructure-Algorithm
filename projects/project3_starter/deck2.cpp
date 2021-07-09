#include <iostream>
#include "deck.h"
using namespace std;

Deck::Deck()
{
    this -> reset();
}

void Deck::reset(){
    for (int suit = SPADES; suit <= DIAMONDS; suit++){
        for (int spot = TWO; spot <= ACE; spot++){
            int index;
            index = suit * (ACE+1) + spot;
            deck[index].suit = (enum Suit)suit;
            deck[index].spot = (enum Spot)spot;
        }
    }
    next = 0;
}

void Deck::shuffle(int n){
    Card deckold[DeckSize];
    next = 0;
    for(int i = 0; i<DeckSize; i++){
        deckold[i] = deck[i];
    }
    int indexL = 0;
    int indexR = n;
    for(int i = 0; i<DeckSize; i++){
        //alternately deal with both segments
        if(indexL < n && indexR < DeckSize){
            if(i%2 == 0){
                deck[i] = deckold[indexR];
                indexR++;
            }
            else{
                deck[i] = deckold[indexL];
                indexL++;
            }
        }
        else if(indexL == n && indexR < DeckSize){
            deck[i] = deckold[indexR];
            indexR++;
        }
        else if(indexR == DeckSize && indexL < n){
            deck[i] = deckold[indexL];
            indexL++;
        }

    }
}

Card Deck::deal(){
    if (next < DeckSize){
        next++;
        return deck[next-1];
    }
    throw DeckEmpty();
}

int Deck::cardsLeft(){
    return DeckSize - next;
}



