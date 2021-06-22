#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "bot.h"

courseData::courseData(int num) {
    this->num = num;
    this->course = new courseInfo[num];
}

int courseData::readNum() {
    return this->num;
}

void courseData::loadData(std::ifstream &fileList) {
    int counter = 0;
    while(fileList) {
        if(fileList) {
            std::string line;
            std::getline(fileList, line);

            std::istringstream iStream;
            iStream.str(line);

            std::string code;
            std::string name;
            std::string instructor;

            while(getline(iStream, code, ',')){
                this->course[counter].code = code;
//                std::cout << iStream.str() << "check istream before next while" << std::endl;
                while(getline(iStream, name, ',')) {
                    this->course[counter].name = name;
//                    std::cout << iStream.str() << "check istream" << std::endl;
                    break;
                }
                while(getline(iStream, instructor)){
                    this->course[counter].instructor = instructor;
                    break;
                }
                break;
            }
            counter = counter + 1;

        }
    }
}

void courseData::printData(){
    for(int i = 0; i < num; i++){
        std::cout << course[i].code << " name is: " << course[i].name
                    << " instructor is: " << course[i].instructor << std::endl;
    }
}


queryData::queryData() {
    this->length = 100;
    this->query = new messageInfo[length];
}

void queryData::loadData(std::ifstream &queryText) {
    int max = length;
    int counter = 0;
    while(queryText){
        if(queryText){
            std::string line;
            std::getline(queryText, line);

            std::istringstream iStream;
            iStream.str(line);

            std::string time;
            std::string group;
            std::string name;
            std::string command;
            std::string commandArg;

            while(getline(iStream, time, ',')){

            }

            counter = counter + 1;
        }
    }
}

void queryData::enlargeData(messageInfo * oldQuery) {
    int newLength = length * 10;
    messageInfo * newQuery = new messageInfo[newLength];
    for(int i = 0; i < length; i++){
        newQuery[i].time = oldQuery[i].time;
        newQuery[i].group = oldQuery[i].group;
        newQuery[i].name = oldQuery[i].name;
        newQuery[i].command = oldQuery[i].command;
        newQuery[i].commandArg = oldQuery[i].commandArg;

    }
    this->length = newLength;
    this->query = newQuery;
}

void queryData::printData() {
    for(int i = 0; i < length; i ++){
        std::cout << "time is: " << query->time << " group is: " << query->group
                << " name is: " << query->name << " command is: " << query->command
                << " commandArg is: " << query->commandArg << std::endl;
    }
}
