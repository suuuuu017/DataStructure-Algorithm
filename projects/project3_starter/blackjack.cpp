#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "player.h"
#include "deck.h"
#include "rand.h"

void shuffle(Deck & deck, Player * player){
    std::cout << "Shuffling the deck" << std::endl;
    for(int i = 0; i < 7; i++){
        int cut = get_cut();
        std::cout << "cut at " << cut << std::endl;
        deck.shuffle(cut);
    }
    player->shuffled();
}

Card deal(Hand & handP, Hand & handD, int i, Player* player, Player* dealer, Card & c){
    if(i == 0 || i == 2){
        handP.addCard(c);
        player->expose(c);
        std::cout << "Player: " << player->getName() << " dealt "
                  << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
    }
    else if(i == 1){
        handD.addCard(c);
        player->expose(c);
        std::cout << "Dealer: " << dealer->getName() << " dealt "
                  << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
    }
    else if(i == 3){
        handD.addCard(c);
    }
    return c;
}

void playerHit(Hand & handP, Player* player, Card & c){
    handP.addCard(c);
    player->expose(c);
    std::cout << "Player: " << player->getName() << " dealt "
              << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
}

void dealerHit(Hand & handD, Player* dealer, Card & c){
    handD.addCard(c);
    std::cout << "Dealer: " << dealer->getName() << " dealt "
              << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
}

Card lastcard{};
Hand kjPower(Hand & hand, int cardNum, Deck deck){
    hand.discardAll();
    for(int i = 0; i < cardNum; i++){
        Card c = deck.deal();
        hand.addCard(c);
        if(hand.handValue().count > 21){
            hand = kjPower(hand, i, deck);
        }
        lastcard = c;
    }
    return hand;
}

Card kjHit(Hand & hand, int cardNum, Player * player, Card dealerUp, Deck & deck){
    int num = cardNum;
    while(hand.handValue().count < 21 && player->draw(dealerUp, hand)){
        Card c = deck.deal();
        hand.addCard(c);
        player->expose(c);
        num = num + 1;
        lastcard = c;
    }
    if(hand.handValue().count > 21){
        std::cout << "Star Platinum, Za Warudo" << std::endl;
        kjPower(hand, num, deck);
    }
    return lastcard;
}

bool checkDeck(Deck deck){
    if(deck.cardsLeft() == 0){
        return true;
    }
    return false;
}

void play(Player * player, Player * dealer, int minBet, int & bankroll,
            const string& team, int p, Deck deck, int hands,
            bool & playerWin, bool & dealerWin, bool & jjWin){

    double threshold = bankroll * 0.5;
    if(team == "sos" && p == 0){
        bankroll = 2 * bankroll;
    }

    shuffle(deck, player);
    int thishand = 1;

    while(bankroll >= minBet && thishand <= hands){
        playerWin = false;
        dealerWin = false;
        std::cout << "Hand " << thishand << " bankroll " << bankroll << std::endl;
        if(deck.cardsLeft() < 20){
            shuffle(deck, player);
        }

        int wager = player->bet(bankroll, minBet);
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
            bankroll = bankroll + wager * 1.5;
            playerWin = true;
            //TODO: check if the natural the wager would not be added twice
            continue;
        }

        int cardNum = 2;
        while(handP.handValue().count < 21 && player->draw(dealerUp, handP)){
            std::cout << handP.handValue().count << std::endl;
            c = deck.deal();
            if(checkDeck(deck)){
                shuffle(deck, player);
                continue;
            }
            playerHit(handP, player, c);
            cardNum = cardNum + 1;
        }
        std::cout << handP.handValue().count << std::endl;
        std::cout << "Player: " << player->getName() << "'s total is "
                  << handP.handValue().count << std::endl;

        if(handP.handValue().count > 21){
            std::cout << "Player: " << player->getName() << " busts" << std::endl;
//            bankroll = bankroll - wager;
            dealerWin = true;
            //TODO: how to continue to next player
        }
        else{
            std::cout << "Dealer: " << dealer->getName() << "'s hole card is "
                      << SpotNames[dealerDown.spot] << " of "
                      << SuitNames[dealerDown.suit] << std::endl;
        }

        while(handD.handValue().count < 17){
            c = deck.deal();
            if(checkDeck(deck)){
                shuffle(deck, player);
                continue;
            }
            dealerHit(handD, dealer, c);
        }
        std::cout << "Dealer: " << dealer->getName() << "'s total is "
                  << handD.handValue().count << std::endl;
        if(handD.handValue().count > 21){
            std::cout << "Dealer: " << player->getName() << " busts" << std::endl;
//            bankroll = bankroll + wager;
            playerWin = true;
            //TODO: how to continue to next dealer
        }

        if((handD.handValue().count > handP.handValue().count && handD.handValue().count <= 21) || dealerWin){
            std::cout << "Dealer: " << dealer->getName() << " wins this hand" << std::endl;
            bankroll = bankroll - wager;
            dealerWin = true;
        }
        else if((handD.handValue().count < handP.handValue().count && handP.handValue().count <= 21) || playerWin){
            std::cout << "Player: " << player->getName() << " wins this hand" << std::endl;
            bankroll = bankroll + wager;
            playerWin = true;
        }
        else{
            std::cout << "Push" << endl;
        }
        if(team == "sos" && p == 0){
            //TODO: check this escape
            if(bankroll < threshold){
                std::cout << "Ni Ge Run Da Yo" << std::endl;
                jjWin = false;
                return;
            }
        }
        thishand = thishand + 1;
    }

    if(team == "sos" && p == 0 && bankroll >= minBet){
        jjWin = true;
    }

    if(bankroll < minBet){
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
    for(int i = 0; i < 5; i++){
        int ID = i + 1;
//        std::cout << ID << type << std::endl;
//        sos[i] = get_Simple();
        string dealerSide = "sc";
        sos[i] = get_Player(dealerSide, type, ID);
    }

    Player* sc[5];
    for(int i = 0; i < 5; i ++){
        int ID = i + 1;
        string dealerSide = "sos";
        sc[i] = get_Player(dealerSide, type, ID);
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
    bool jjWin = false;

    while(p < 5 && d < 5){
        int newBankroll = bankroll;
//        std ::cout << "bankRoll " << bankroll << std::endl;
        player = players[p];
        dealer = dealers[d];
        //TODO: what to do it push
        play(player, dealer, minBet, newBankroll, team, p, deck, hands, playerWin, dealerWin, jjWin);
        if(newBankroll < minBet || (player->getName() == SC_Name[0] && !jjWin)){
            if(dealer->getName() == SC_Name[0]){
                std::cout << "Nice!" << std::endl;
            }
            p = p + 1;
        }
        else if(newBankroll >= minBet){
            if(player->getName() == SC_Name[0] && jjWin){
                std::cout << "Nice!" << std::endl;
            }
            if(player->getName() == SC_Name[4]){
                std::cout << "rerorerorero rerorerorero" << std::endl;
            }
            d = d + 1;
        }
//        std::cout << p << " " << d << std::endl;
//        std::cout << " the p and d are" << std::endl;

    }




}