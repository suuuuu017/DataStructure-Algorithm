#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "player.h"
#include "deck.h"
#include "rand.h"

void shuffle(Deck deck, Player * player){
    std::cout << "Shuffling the deck" << std::endl;
    for(int i = 0; i < 7; i++){
        int cut = get_cut();
        std::cout << "cut at " << cut << std::endl;
        deck.shuffle(cut);
    }
    player->shuffled();
}

Card deal(Hand & handP, Hand & handD, int i, Player* player, Player* dealer, Card & c){
    if(i == 0 || i == 2 || i > 3){
        handP.addCard(c);
        player->expose(c);
        std::cout << "Player: " << player->getName() << " dealt "
                  << SuitNames[c.suit] << " of " << SpotNames[c.spot] << std::endl;
    }
    else if(i == 1 || i > 3){
        handD.addCard(c);
        player->expose(c);
        std::cout << "Dealer: " << dealer->getName() << " dealt "
                  << SuitNames[c.suit] << " of " << SpotNames[c.spot] << std::endl;
    }
    else if(i == 3){
        handD.addCard(c);
    }
    return c;
}

bool checkDeck(Deck deck){
    if(deck.cardsLeft() == 0){
        return true;
    }
    return false;
}

void play(Player * player, Player * dealer, int minBet, int bankroll,
            const string& team, int p, Deck deck, int hands,
            bool & playerWin, bool & dealerWin){
    int thisBankroll = bankroll;
    if(team == "sos" && p == 0){
        thisBankroll = 2 * bankroll;
    }

    shuffle(deck, player);
    int thishand = 1;

    while(thisBankroll >= minBet && thishand <= hands){
        std::cout << "Hand " << thishand << " bankroll " << bankroll << std::endl;
        if(deck.cardsLeft() < 20){
            shuffle(deck, player);
        }

        int wager = player->bet(thisBankroll, minBet);
        cout << "Player: " << player->getName() << " bets " << wager << endl;

        Hand handD;
        Hand handP;

        Card c = deck.deal();
        if(checkDeck(deck)){
            shuffle(deck, player);
            continue;
        }
        deal(handP, handD, 0, player, dealer, c);
        c = deck.deal();
        if(checkDeck(deck)){
            shuffle(deck, player);
            continue;
        }
        Card dealerUp = deal(handP, handD, 1, player, dealer, c);
        c = deck.deal();
        if(checkDeck(deck)){
            shuffle(deck, player);
            continue;
        }
        deal(handP, handD, 2, player, dealer, c);
        c = deck.deal();
        if(checkDeck(deck)){
            shuffle(deck, player);
            continue;
        }
        Card dealerDown = deal(handP, handD, 3, player, dealer, c);

        if(handP.handValue().count == 21){
            std::cout << "Player: " << player->getName() << " dealt natural 21" << std::endl;
            //TODO: how to deal with this int double convertion
            thisBankroll = thisBankroll + wager * 1.5;
            playerWin = true;
        }

        int cardNum = 4;
        while(handP.handValue().count < 21 && player->draw(dealerUp, handP)){
            c = deck.deal();
            if(checkDeck(deck)){
                shuffle(deck, player);
                continue;
            }
            deal(handP, handD, cardNum, player, dealer, c);
            cardNum = cardNum + 1;
        }

        std::cout << "Player: " << player->getName() << "'s total is "
                  << handP.handValue().count << std::endl;

        if(handP.handValue().count > 21){
            std::cout << "Player: " << player->getName() << " busts" << std::endl;
            thisBankroll = thisBankroll - wager;
            dealerWin = true;
            //TODO: how to continue to next player
        }
        else{
            std::cout << "Dealer: " << dealer->getName() << "'s hole card is"
                      << SuitNames[dealerDown.suit] << " of "
                      << SpotNames[dealerDown.spot] << std::endl;
        }

        while(handD.handValue().count < 17){
            c = deck.deal();
            if(checkDeck(deck)){
                shuffle(deck, player);
                continue;
            }
            deal(handP, handD, cardNum, player, dealer, c);
        }
        std::cout << "Dealer: " << dealer->getName() << "'s total is "
                  << handD.handValue().count << std::endl;
        if(handD.handValue().count > 21){
            std::cout << "Dealer: " << player->getName() << " busts" << std::endl;
            thisBankroll = thisBankroll + wager;
            playerWin = true;
            //TODO: how to continue to next dealer
        }

        if(handD.handValue().count > handP.handValue().count){
            std::cout << "Dealer: " << dealer->getName() << " wins this hand" << std::endl;
            bankroll = bankroll - wager;
            dealerWin = true;
        }
        else if(handD.handValue().count < handP.handValue().count){
            std::cout << "Player: " << player->getName() << " wins this hand" << std::endl;
            bankroll = bankroll + wager;
            playerWin = true;
        }
        else{
            std::cout << "Push" << endl;
        }

        thishand = thishand + 1;
    }

    if(thisBankroll < minBet){
        dealerWin = true;
        return;
    }
    else if(thisBankroll >= minBet){
        playerWin = true;
        return;
    }
}


int main(int argc, char * argv[]){
    int bankroll = atoi(argv[1]);
    int hands = atoi(argv[2]);
    std::string type = argv[3];
    std::string team = argv[4];

    Player* player = nullptr;
    Player* dealer = nullptr;
    Player* players[5];
    Player* dealers[5];

    Player* sos[5];
    for(int i = 0; i < 5; i ++){
        int ID = i + 1;
        sos[i] = get_Player((string &) "sc", type, ID);
    }

    Player* sc[5];
    for(int i = 0; i < 5; i ++){
        int ID = i + 1;
        sc[i] = get_Player((string &) "sos", type, ID);
    }

    Deck deck;

    if(team == "sc"){
        for(int i = 0; i < 5; i ++){
            players[i] = sos[i];
            dealers[i] = sc[i];
        }
    }
    else if(team == "sos"){
        for(int i = 0; i < 5; i ++){
            players[i] = sc[i];
            dealers[i] = sos[i];
        }
    }

    int minBet = 5;

    int p = 0;
    int d = 0;

    bool playerWin = false;
    bool dealerWin = false;

    while(p < 5 && d < 5){
        if(dealerWin){
            p = p + 1;
            dealerWin = false;
        }
        if(playerWin){
            d = d + 1;
            playerWin = false;
        }
        player = players[p];
        dealer = dealers[d];
        //TODO: what to do it push
        play(player, dealer, minBet, bankroll, team, p, deck, hands, playerWin, dealerWin);
    }




}