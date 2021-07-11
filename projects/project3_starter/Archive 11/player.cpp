#include "player.h"
#include <iostream>

class Simple : public Player{
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
        this->name = SOS_Name[id - 1];
    }
    else if(tm == StardustCrusaders){
        this->name = SC_Name[id - 1];
    }
}

//TODO implement the get_Player for simple player

class Counting : public Simple{
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


//SOS class

class SH: public Simple{
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand& player) {
        return Simple::draw(dealer, player);
    }

    void expose(Card c) {
        Simple::expose(c);
    }

    void shuffled() {
        Simple::shuffled();
    }

    string getName() {
        return Simple::getName();
    }

    int getID() {
        return Simple::getID();
    }

    Team getTeam() {
        return Simple::getTeam();
    }

    void setPlayer(Team tm, int id);
};

int SH::bet(unsigned int bankroll, unsigned int minimum) {
    return (2 * int(minimum));
}

void SH::setPlayer(Team tm, int id) {
    this->team = SOSBrigade;
    this->ID = 1;
    this->name = SOS_Name[0];
}

class NY : public Counting{
private:
    int count = 0;
public:
    int bet(unsigned int bankroll, unsigned int minimum) {
        return Counting::bet(bankroll, minimum);
    }

    bool draw(Card dealer, const Hand& player) {
        return Counting::draw(dealer, player);
    }

    void expose(Card c) {
        Counting::expose(c);
    }

    void shuffled() {
        Counting::shuffled();
    }

    string getName() {
        return Counting::getName();
    }

    int getID() {
        return Counting::getID();
    }

    Team getTeam() {
        return Counting::getTeam();
    }

    void setPlayer(Team tm, int id);
};

void NY::setPlayer(Team tm, int id) {
    this->team = SOSBrigade;
    this->ID = 2;
    this->name = SOS_Name[1];
}

class AM : public Counting{
private:
    int count = 0;
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand& player) {
        return Counting::draw(dealer, player);
    }

    void expose(Card c) {
        Counting::expose(c);
    }

    void shuffled() {
        Counting::shuffled();
    }

    string getName() {
        return Counting::getName();
    }

    int getID() {
        return Counting::getID();
    }

    Team getTeam() {
        return Counting::getTeam();
    }

    void setPlayer(Team tm, int id);
};

int AM::bet(unsigned int bankroll, unsigned int minimum) {
    if(count <= -2 && bankroll >= minimum * 2){
        return 2 * int(minimum);
    }
    else{
        return int(minimum);
    }
}

void AM::setPlayer(Team tm, int id) {
    this->team = SOSBrigade;
    this->ID = 3;
    this->name = SOS_Name[2];
}

class K : public Simple{
public:
    int bet(unsigned int bankroll, unsigned int minimum) {
        return Simple::bet(bankroll, minimum);
    }

    bool draw(Card dealer, const Hand& player) {
        return Simple::draw(dealer, player);
    }

    void expose(Card c) {
        Simple::expose(c);
    }

    void shuffled() {
        Simple::shuffled();
    }

    string getName() {
        return Simple::getName();
    }

    int getID() {
        return Simple::getID();
    }

    Team getTeam() {
        return Simple::getTeam();
    }

    void setPlayer(Team tm, int id);
};

void K::setPlayer(Team tm, int id) {
    this->team = SOSBrigade;
    this->ID = 4;
    this->name = SOS_Name[3];
}

//SC class

class JJ : public Counting{
private:
    int count = 0;
public:
//    int bet(unsigned int bankroll, int normalBankroll, unsigned int minimum);
    int bet(unsigned int bankroll, unsigned int minimum){
        return Counting::bet(bankroll, minimum);
    }

    bool draw(Card dealer, const Hand& player) {
        return Counting::draw(dealer, player);
    }

    void expose(Card c) {
        Counting::expose(c);
    }

    void shuffled() {
        Counting::shuffled();
    }

    string getName() {
        return Counting::getName();
    }

    int getID() {
        return Counting::getID();
    }

    Team getTeam() {
        return Counting::getTeam();
    }

    void setPlayer(Team tm, int id);

};

//int JJ::bet(unsigned int bankroll, int normalBankroll, unsigned int minimum) {
//    if(count >= 2 && bankroll >= normalBankroll * 0.5){
//        return 2 * int(minimum);
//    }
//    else{
//        return int(minimum);
//    }
//}

void JJ::setPlayer(Team tm, int id) {
    this->team = StardustCrusaders;
    this->ID = 1;
    this->name = SC_Name[0];
}

class KJ : public Counting{
private:
    int count = 0;
public:
    int bet(unsigned int bankroll, unsigned int minimum) {
        return Counting::bet(bankroll, minimum);
    }

    bool draw(Card dealer, const Hand& player) {
        return Counting::draw(dealer, player);
    }

    void expose(Card c) {
        Counting::expose(c);
    }

    void shuffled() {
        Counting::shuffled();
    }

    string getName() {
        return Counting::getName();
    }

    int getID() {
        return Counting::getID();
    }

    Team getTeam() {
        return Counting::getTeam();
    }

    void setPlayer(Team tm, int id);

};

void KJ::setPlayer(Team tm, int id) {
    this->team = StardustCrusaders;
    this->ID = 2;
    this->name = SC_Name[1];
}

class JPP : public Simple{
public:
    int bet(unsigned int bankroll, unsigned int minimum) {
        return Simple::bet(bankroll, minimum);
    }

    bool draw(Card dealer, const Hand& player) {
        return Simple::draw(dealer, player);
    }

    void expose(Card c) {
        Simple::expose(c);
    }

    void shuffled() {
        Simple::shuffled();
    }

    string getName() {
        return Simple::getName();
    }

    int getID() {
        return Simple::getID();
    }

    Team getTeam() {
        return Simple::getTeam();
    }

    void setPlayer(Team tm, int id);
};

void JPP::setPlayer(Team tm, int id) {
    this->team = StardustCrusaders;
    this->ID = 3;
    this->name = SC_Name[2];
}

class KN : public Counting{
private:
    int count = 0;
public:
    int bet(unsigned int bankroll, unsigned int minimum);

    bool draw(Card dealer, const Hand& player) {
        return Counting::draw(dealer, player);
    }

    void expose(Card c) {
        Counting::expose(c);
    }

    void shuffled() {
        Counting::shuffled();
    }

    string getName() {
        return Counting::getName();
    }

    int getID() {
        return Counting::getID();
    }

    Team getTeam() {
        return Counting::getTeam();
    }

    void setPlayer(Team tm, int id);
};

int KN::bet(unsigned int bankroll, unsigned int minimum) {
    if(count >= 4 && bankroll >= minimum * 2){
        return 2 * int(minimum);
    }
    else{
        return int(minimum);
    }
}

void KN::setPlayer(Team tm, int id) {
    this->team = StardustCrusaders;
    this->ID = 4;
    this->name = SC_Name[3];
}

static Simple simpleSOS;
static Simple simpleSC;
static Counting countingSOS;
static Counting countingSC;
static SH sh;
static NY ny;
static AM am;
static K k;
static JJ jj;
static KJ kj;
static JPP jpp;
static KN kn;

//Player *get_Simple(){
//    return & simple;
//}

Player* get_Player(string& dealerSide, string& playerType, int& ID){
//    std::cout << dealerSide << std::endl;
    if(dealerSide == "sc"){
//        std::cout << "here!" << std::endl;
        Team playerTeam = SOSBrigade;
        if(ID == 1){
//            std::cout << "here" << std::endl;
            sh.setPlayer(playerTeam, 1);
            return & sh;
        }
        if(ID == 2){
            ny.setPlayer(playerTeam, 2);
            return & ny;
        }
        if(ID == 3){
            am.setPlayer(playerTeam, 3);
            return & am;
        }
        if(ID == 4){
            k.setPlayer(playerTeam, 4);
            return & k;
        }
        if(ID == 5 && playerType == "simple"){
//            std::cout << "here sos" << std::endl;
            simpleSOS.setPlayer(playerTeam, 5);
            return & simpleSOS;
        }
        if(ID == 5 && playerType == "counting"){
            countingSOS.setPlayer(playerTeam, 5);
            return & countingSOS;
        }
    }
    else if(dealerSide == "sos"){
//        std::cout << "here!" << std::endl;
        Team playerTeam = StardustCrusaders;
        if(ID == 1){
            jj.setPlayer(playerTeam, 1);
            return & jj;
        }
        if(ID == 2){
            kj.setPlayer(playerTeam, 2);
            return & kj;
        }
        if(ID == 3){
            jpp.setPlayer(playerTeam, 3);
            return & jpp;
        }
        if(ID == 4){
            kn.setPlayer(playerTeam, 4);
            return & kn;
        }
        if(ID == 5 && playerType == "simple"){
//            std::cout << "here sc" << std::endl;
            simpleSC.setPlayer(playerTeam, 5);
            return & simpleSC;
        }
        if(ID == 5 && playerType == "counting"){
            countingSC.setPlayer(playerTeam, 5);
            return & countingSC;
        }
    }
    return nullptr;
}

string Player::getName() {
    return name;
}

int Player::getID() {
    return ID;
}

Team Player::getTeam() {
    return team;
}

void Player::setPlayer(Team tm, int id) {
    this->team = tm;
    this->ID = id;
    if(tm == SOSBrigade){

        this->name = SOS_Name[id - 1];
    }
    else if(tm == StardustCrusaders){

        this->name = SC_Name[id - 1];
    }
}
