#include "deck.h"

Deck::Deck() {
    for(int suit = 0; suit < 4; suit++){
        for(int spot = 0; spot < 13; spot++){
            deck[suit * 13 + spot].suit = static_cast<Suit>(suit);
            deck[suit * 13 + spot].spot = static_cast<Spot>(spot);
        }
    }
    next = 0;
}

void Deck::reset() {
    Deck();
}

void Deck::shuffle(int n) {
    Card shuffledDeck[DeckSize];
    int leftStart = 0;
    int rightStart = n;
    int leftEnd = n - 1;
    int rightEnd = 51;

    int i = 0;
    while(i < DeckSize){
        if(leftStart <= leftEnd && rightStart <= rightEnd){
            shuffledDeck[i] = deck[leftStart];
            shuffledDeck[i + 1] = deck[rightStart];
            leftStart = leftStart + 1;
            rightStart = rightStart + 1;
            i = i + 2;
        }
        else if(leftStart > leftEnd && rightStart <= rightEnd){
            shuffledDeck[i] = deck[rightStart];
            rightStart = rightStart + 1;
            i = i + 1;
        }
        else if(rightStart > rightEnd && leftStart <= leftEnd){
            shuffledDeck[i] = deck[leftStart];
            leftStart = leftStart + 1;
            i = i + 1;
        }
    }

    for(int j = 0; j < DeckSize; j++){
        deck[j] = shuffledDeck[j];
    }
}

Card Deck::deal() {
    if(next < DeckSize){
        next = next + 1;
        return deck[next - 1];
    }
    else{
        throw DeckEmpty();
    }
}

int Deck::cardsLeft() {
    return DeckSize - next;
}


