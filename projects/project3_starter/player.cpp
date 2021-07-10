#include "player.h"

class Simple : protected Player{
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand& player);
    void expose(Card c);
    void shuffled();
    string getName();
    int getID();
    Team getTeam();
    void setPlayer(Team tm, int id);
};

int Simple::bet(unsigned int bankroll, unsigned int minimum) {
    return int(minimum);
}

bool Simple::draw(Card dealer, const Hand &player) {
    if(!player.handValue().soft){
        if(player.handValue().count <= 11){
            return true;
        }
        else if(player.handValue().count == 12){
            if(dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX){
                return false;
            }
            else{
                return true;
            }
        }
        else if(player.handValue().count >= 13 && player.handValue().count <= 16){
            if(dealer.spot >= TWO && dealer.spot <= SIX){
                return false;
            }
            else{
                return true;
            }
        }
        else if(player.handValue().count >= 17){
            return false;
        }
    }
    else{
        if(player.handValue().count <= 17){
            return true;
        }
        else if(player.handValue().count == 18){
            if(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT){
                return false;
            }
            else{
                return true;
            }
        }
        else if(player.handValue().count >= 19){
            return false;
        }
    }
    return false;
}

void Simple::expose(Card c) {
}

void Simple::shuffled() {
}

string Simple::getName() {
    return this->name;
}

int Simple::getID() {
    return this->ID;
}

Team Simple::getTeam() {
    return this->team;
}

void Simple::setPlayer(Team tm, int id) {
    this->team = tm;
    this->ID = id;
    if(tm == SOSBrigade){
        this->name = SOS_Name[id];
    }
    else if(tm == StardustCrusaders){
        this->name = SC_Name[id];
    }
}

//TODO implement the get_Player for simple player

class Counting : protected Simple{
private:
    int count = 0;
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand& player);
    void expose(Card c);
    void shuffled();
    string getName();
    int getID();
    Team getTeam();
    void setPlayer(Team tm, int id);
};

int Counting::bet(unsigned int bankroll, unsigned int minimum) {
    if(count >= 2 && bankroll >= minimum * 2){
        return 2 * int(minimum);
    }
    else{
        return int(minimum);
    }
}

bool Counting::draw(Card dealer, const Hand &player) {
    return Simple::draw(dealer, player);
}

void Counting::expose(Card c) {
    if(c.spot >= TEN){
        count = count - 1;
    }
    else if(c.spot >= TWO && c.spot <= SIX){
        count = count + 1;
    }
}

void Counting::shuffled() {
    count = 0;
}

string Counting::getName() {
    return Simple::getName();
}

int Counting::getID() {
    return Simple::getID();
}

Team Counting::getTeam() {
    return Simple::getTeam();
}

void Counting::setPlayer(Team tm, int id) {
    Simple::setPlayer(tm, id);
}

//TODO implement the get_Player for counting player

