#include "hand.h"

Hand::Hand() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::discardAll() {
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card c) {
    if(c.spot == ACE && curValue.soft){
        curValue.count = curValue.count + 1;
    }
    //TODO: check if the logic is correct
    else if(c.spot == ACE && (!curValue.soft)){
        curValue.count = curValue.count + 11;
        curValue.soft = true;
    }
    else if(c.spot == JACK || c.spot == QUEEN || c.spot == KING){
        curValue.count = curValue.count + 10;
    }
    else{
        curValue.count = curValue.count + c.spot + 2;
    }

    if(curValue.count > 21 && curValue.soft){
        curValue.count = curValue.count - 10;
        curValue.soft = false;
    }
}

HandValue Hand::handValue() const {
    return curValue;
}



