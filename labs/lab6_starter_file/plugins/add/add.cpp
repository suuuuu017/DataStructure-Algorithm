#include <iostream>
#include <sstream>
#include <regex>

//TODO: change the dir to plugin.h
#include "../../plugin.h"

class Add : public Plugin{
public:
    Add() : Plugin(){
        this->name = "add";
        this->author = "Meual";
        this->description = "add two integers";
        this->help = "add <integer> <integer>";
    }

    int matchRule(const string &str) const override {
        std::regex r("^(add)(\\s)+[0-9]+(\\s)+[0-9]+");
        return regex_match(str.begin(), str.end(), r);
    }

    string response(const string &str) const{
        stringstream ss(str);
        string buffer;
        int first = 0;
        int second = 0;
        ss >> buffer >> first >> second;
        int result = 0;
        result = first + second;
        return to_string(result);
    }

    string toString() const override {
        //TODO: how to concat \n
        string output = "Add operations is great    --Meual";
        return output;
    }
};

extern "C" Plugin *create() {
    return new Add();
}

extern "C" int *destroy(Plugin *p) {
    delete p;
    return 0;
}