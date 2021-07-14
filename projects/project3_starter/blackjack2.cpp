#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

#include "player.h"
#include "deck.h"
#include "rand.h"

Deck shuffle(Deck & deck, Player * player){
    std::cout << "Shuffling the deck" << std::endl;
    for(int i = 0; i < 7; i++){
        int cut = get_cut();
        std::cout << "cut at " << cut << std::endl;
        deck.shuffle(cut);
    }
    player->shuffled();
    return deck;
}

bool checkDeck(Deck deck){
    if(deck.cardsLeft() == 0){
        return true;
    }
    return false;
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
};



Hand kjPower(Hand hand, int cardNum, Deck & deck, Card & lastcard, Player * player){
    hand.discardAll();
    for(int i = 0; i < cardNum; i++){
//        std::cout << "card Num is " << cardNum << std::endl;
        if(checkDeck(deck)){
            shuffle(deck, player);
            i = i - 1;
            continue;
        }
        Card c = deck.deal();
//        std::cout << "card is " << SuitNames[c.suit] << SpotNames[c.spot] << std::endl;
        hand.addCard(c);
        if(hand.handValue().count > 21){
            hand = kjPower(hand, i, deck, lastcard, player);
        }
        lastcard = c;
    }
    return hand;
}
bool hithere = false;
Card kjHit(Hand & hand, int cardNum, Player * player, Card dealerUp, Deck & deck, Card & lastcard){
    int num = cardNum;
    Card c;
    while(true){
        if(hand.handValue().count < 21 && player->draw(dealerUp, hand)){
            if(checkDeck(deck)){
                shuffle(deck, player);
            }
            c = deck.deal();
//            Hand tmphand = hand;
            hand.addCard(c);
//            std::cout << "torf" << player->draw(dealerUp, hand) << std::endl;
//            std::cout << "Player: " << player->getName() << " dealt "
//                      << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
//            std::cout << "card is before time " << SuitNames[c.suit] << SpotNames[c.spot] << std::endl;
//            dealerHit(hand, player, c);
            num = num + 1;
            lastcard = c;
            continue;
        }
//        std::cout << "Player: " << player->getName() << " dealt "
//            << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
//        num = num + 1;
        break;
    }

    if(hand.handValue().count <= 21 && !player->draw(dealerUp, hand) ){
//        std::cout << "torf!" << player->draw(dealerUp, hand) << std::endl;
//        std::cout << "Dealer: " << player->getName() << ": \"Star Platinum, Za Warudo\"" << std::endl;
//            std::cout << "dealer cardnum " << num << std::endl;
//        std::cout << "Player: " << player->getName() << " dealt "
//                  << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
        return lastcard;
    }
    if(hand.handValue().count > 21) {
//        if (!hithere) {
//            hithere = true;
//            std::cout << "Player: " << player->getName() << ": \"Star Platinum, Za Warudo\"" << std::endl;
//        }
        std::cout << "Dealer: " << player->getName() << ": \"Star Platinum, Za Warudo\"" << std::endl;
//            std::cout << "dealer cardnum " << num << std::endl;
        hand = kjPower(hand, num, deck, lastcard, player);
        if (hand.handValue().count < 17) {
            kjHit(hand, num, player, dealerUp, deck, lastcard);
        }
    }
    std::cout << "Player: " << player->getName() << " dealt "
          << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
    return lastcard;
}

bool beenhere = false;
Card dealerkjHit(Hand & hand, int cardNum, Player * player, Deck & deck, Card & lastcard){
    int num = cardNum;
    Card c = lastcard;
    if(hand.handValue().count < 17) {
        while (true) {
            if (checkDeck(deck)) {
                shuffle(deck, player);
            }
            c = deck.deal();
            hand.addCard(c);
            if (hand.handValue().count < 17) {
//            std::cout << "Dealer: " << player->getName() << " dealt "
//                      << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
//            std::cout << "card is before time " << SuitNames[c.suit] << SpotNames[c.spot] << std::endl;
//            dealerHit(hand, player, c);
                num = num + 1;
                lastcard = c;
                continue;
            }
            num = num + 1;
            break;
        }
    }

    if(hand.handValue().count >= 17 && hand.handValue().count <= 21 ){
//        std::cout << "Dealer: " << player->getName() << ": \"Star Platinum, Za Warudo\"" << std::endl;
//            std::cout << "dealer cardnum " << num << std::endl;
        std::cout << "Dealer: " << player->getName() << " dealt "
                  << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
        return lastcard;
    }
    if(hand.handValue().count > 21){
//        if(!beenhere){
//            beenhere = true;
//            std::cout << "Dealer: " << player->getName() << ": \"Star Platinum, Za Warudo\"" << std::endl;
//        }
        std::cout << "Dealer: " << player->getName() << ": \"Star Platinum, Za Warudo\"" << std::endl;
//            std::cout << "dealer cardnum " << num << std::endl;
        hand = kjPower(hand, num, deck, lastcard, player);
        if(hand.handValue().count < 17){
            dealerkjHit(hand, num, player, deck, lastcard);
        }
//        dealerkjHit(hand, num, player, deck, lastcard);
//        dealerkjHit(hand, num, player, deck, lastcard);
//        dealerkjHit(hand, num, player, deck, lastcard);
    }

    return lastcard;
}


void play(Player * player, Player * dealer, int minBet, int & bankroll,
            const string& team, int p, Deck & deck, int hands,
            bool & playerWin, bool & dealerWin, bool & jjWin, int threshold){

//    double threshold = bankroll * 0.5;
//    if(team == "sos" && p == 0){
//        bankroll = 2 * bankroll;
//    }

//    Deck oldDeck = shuffle(deck, player);

    int thishand = 1;


    shuffle(deck, player);
    if(bankroll < minBet){
        std::cout << "Player: " << player->getName() << " has " << bankroll << " after " <<
                  "0" << " hands" << endl;
        return;
    }



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

        if(checkDeck(deck)){
            shuffle(deck, player);
            std::cout << "Hand " << thishand << " card used up, this hand will start again" <<
                 std::endl;
            continue;
        }
        Card c = deck.deal();

        deal(handP, handD, 0, player, dealer, c);
        if(checkDeck(deck)){
            shuffle(deck, player);
            std::cout << "Hand " << thishand << " card used up, this hand will start again" <<
                      std::endl;
            continue;
        }
        c = deck.deal();

        Card dealerUp = deal(handP, handD, 1, player, dealer, c);
        if(checkDeck(deck)){
            shuffle(deck, player);
            std::cout << "Hand " << thishand << " card used up, this hand will start again" <<
                      std::endl;
            continue;
        }
        c = deck.deal();

        deal(handP, handD, 2, player, dealer, c);
        if(checkDeck(deck)){
            shuffle(deck, player);
            std::cout << "Hand " << thishand << " card used up, this hand will start again" <<
                      std::endl;
            continue;
        }
        c = deck.deal();

        Card dealerDown = deal(handP, handD, 3, player, dealer, c);

        if(handP.handValue().count == 21){
            std::cout << "Player: " << player->getName() << " dealt natural 21" << std::endl;
            //TODO: how to deal with this int double convertion
            bankroll = bankroll + wager * 1.5;
            playerWin = true;
            //TODO: check if the natural the wager would not be added twice
            continue;
        }

        Card lastcard = c;

        int cardNum = 2;
        if(player->getName() != SC_Name[1]){
            while(handP.handValue().count < 21 && player->draw(dealerUp, handP)){
//                std::cout << handP.handValue().count << std::endl;
                if(checkDeck(deck)){
                    shuffle(deck, player);
                    std::cout << "Hand " << thishand << " card used up, this hand will start again" <<
                              std::endl;
                    continue;
                }
                c = deck.deal();

                playerHit(handP, player, c);
                cardNum = cardNum + 1;
            }
        }
        else{
            kjHit(handP, 2, player, dealerUp, deck, lastcard);
//            std::cout << "Player: " << player->getName() << " dealt "
//                      << SpotNames[c.spot] << " of " << SuitNames[c.suit] << std::endl;
        }
//        std::cout << handP.handValue().count << std::endl;
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
        if(!dealerWin){
            if(dealer->getName() != SC_Name[1]){
                while(handD.handValue().count < 17){
//                    std::cout << "stuck here" << std::endl;
                    if(checkDeck(deck)){
                        shuffle(deck, player);
                        std::cout << "Hand " << thishand << " card used up, this hand will start again" <<
                                  std::endl;
                        continue;
                    }
                    c = deck.deal();

                    dealerHit(handD, dealer, c);
                }
            }
            else{
                dealerkjHit(handD, 2, dealer, deck, lastcard);
//                Card tmpcard = dealerkjHit(handD, 2, dealer, deck, lastcard);
//                std::cout << "Dealer: " << dealer->getName() << " dealt "
//                          << SpotNames[tmpcard.spot] << " of " << SuitNames[tmpcard.suit] << std::endl;
//                int dealerCard = 2;
//                while(handD.handValue().count < 17){
//                    if(checkDeck(deck)){
//                        shuffle(deck, player);
//                        continue;
//                    }
//                    c = deck.deal();
//                    dealerHit(handD, dealer, c);
//                    dealerCard = dealerCard + 1;
//                    if(handD.handValue().count > 17 && handD.handValue().count <= 21 ){
//                        break;
//                    }
//                    else if(handD.handValue().count > 21){
//                        handD = kjPower(handD, dealerCard, deck, lastcard, dealer);
//                    }
//                }

            }
            std::cout << "Dealer: " << dealer->getName() << "'s total is "
                      << handD.handValue().count << std::endl;
            if(handD.handValue().count > 21){
                std::cout << "Dealer: " << dealer->getName() << " busts" << std::endl;
//            bankroll = bankroll + wager;
                playerWin = true;
                //TODO: how to continue to next dealer
            }
        }


        if((handD.handValue().count > handP.handValue().count && handD.handValue().count <= 21) || dealerWin){
            if(handD.handValue().count > handP.handValue().count && handD.handValue().count <= 21){
                std::cout << "Dealer: " << dealer->getName() << " wins this hand" << std::endl;
            }
            bankroll = bankroll - wager;
            dealerWin = true;
        }
        else if((handD.handValue().count < handP.handValue().count && handP.handValue().count <= 21) || playerWin){
            if(handD.handValue().count < handP.handValue().count && handP.handValue().count <= 21){
                std::cout << "Player: " << player->getName() << " wins this hand" << std::endl;
            }
            bankroll = bankroll + wager;
            playerWin = true;
        }
        else if(handD.handValue().count == handP.handValue().count && handD.handValue().count <= 21
                && handP.handValue().count <= 21){
            std::cout << "Push" << endl;
        }

//        std::cout << "Player: " << player->getName() << " has " << bankroll << " after " <<
//             thishand << " hands" << endl;
        if(team == "sos" && p == 0){
            //TODO: check this escape
            if(bankroll < threshold){
//                deck = oldDeck;

                std::cout << "Player: " << player->getName() << " has " << bankroll << " after " <<
                          thishand << " hands" << endl;
                std::cout << "Player: " << player->getName() << ": \"Ni Ge Run Da Yo\"" << std::endl;
                jjWin = false;
                return;
            }
        }
        beenhere = false;
        hithere = false;
        thishand = thishand + 1;
    }
    std::cout << "Player: " << player->getName() << " has " << bankroll << " after " <<
        (thishand - 1) << " hands" << endl;

//    deck = oldDeck;

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

    int newBankroll = bankroll;
    double threshold = bankroll * 0.5;
    while(p < 5 && d < 5){
//        std ::cout << "bankRoll1 " << newBankroll << std::endl;
        player = players[p];
        dealer = dealers[d];
        //TODO: what to do it push
        if(team == "sos" && p == 0 && d == 0){
            newBankroll = 2 * newBankroll;
        }
        play(player, dealer, minBet, newBankroll, team, p, deck, hands, playerWin, dealerWin, jjWin, threshold);
        if(newBankroll < minBet || (player->getName() == SC_Name[0] && !jjWin)){

            cout << "Player: " << player->getName() <<
                 " has been kicked out. The winner of this round is "
                 << dealer->getName() <<"." << endl;
            if(dealer->getName() == SC_Name[0]){
                std::cout << "Dealer: " << dealer->getName() << ": \"Nice!\"" << std::endl;
            }
            newBankroll = bankroll;
            p = p + 1;
            beenhere = false;
            hithere = false;
        }
        else if(newBankroll >= minBet){
//            std ::cout << "bankRoll! " << newBankroll << std::endl;
            cout << "Dealer: " << dealer->getName() <<
                 " has been kicked out. The winner of this round is "
                 << player->getName() <<"." << endl;
            if(player->getName() == SC_Name[0] && jjWin){
                std::cout << "Player: " << player->getName() << ": \"Nice!\"" << std::endl;
            }
            if(player->getName() == SC_Name[4]){
                std::cout << "Player: " << player->getName() << ": \"rerorerorero rerorerorero\"" << std::endl;
            }
            d = d + 1;
            beenhere = false;
            hithere = false;
        }
//        std::cout << p << " " << d << std::endl;
//        std::cout << " the p and d are" << std::endl;

    }

    if((p == 5 && team == "sc") || (d == 5 && team == "sos")){
        std::cout << "Game over. The winner is Stardust Crusaders. SOS Brigade will return the computer to "
                     "Joseph Joestar and Suzumiya Haruhi will become a member of Stardust Crusaders"
                  << std::endl;
    }
    else{
        std::cout << "Game over. The winner is SOS Brigade. SOS Brigade got four computers and "
                     "Stardust Crusaders become an affiliate group of SOS Brigade"
                    << std::endl;
    }


}