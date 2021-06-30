#include <iostream>
#include <regex>

//TODO: change the dir to plugin.h
#include "../../plugin.h"

class Styled : public Plugin{
public:
    Styled() : Plugin(){
        this->name = "styled";
        this->author = "Scond Lobster";
        this->description = "Print a styled message when asked who's your daddy";
        this->help = "Usage : type whosYourDaddy into the terminal";
    }

    int matchRule(const string &str) const override {
        return (str == "WhosYourDaddy");
    }

    string response(const string &str) const override {
        return "You are not playing Warcraft 3, guys...";
    }

    string toString() const override {
        string output = "Second Lobster writes styled because he thinks it is fun";
        return output;
    }
};

extern "C" Plugin *create() {
    return new Styled();
}

extern "C" int *destroy(Plugin *p) {
    delete p;
    return 0;
}