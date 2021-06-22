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

void courseData::printAllData(){
    for(int i = 0; i < num; i++){
        std::cout << course[i].code << " name is: " << course[i].name
                    << " instructor is: " << course[i].instructor << std::endl;
    }
}

std::string courseData::readCode(int i) {
    return course[i].code;
}

void courseData::printData(int i){
    std::cout << course[i].code << " name is: " << course[i].name
        << " instructor is: " << course[i].instructor << std::endl;

}

queryData::queryData() {};

void queryData::loadData(std::istream & queryText) {
    std::string time;
    std::string group;
    std::string name;
    std::string command;
    std::string commandArg;
    std::string arg;
    std::string mes;

    if(getline(queryText, time, ',')){
        this->message.time = time;
//        std::cout << time << "  here time " << std::endl;
        if(getline(queryText, group, ',')) {
            this->message.group = group;
//            std::cout << group << "  here group " << std::endl;
            if (getline(queryText, name, ',')){
                this->message.name = name;
//                std::cout << name << "  here name " << std::endl;
            }
        }
    }

    std::string rest;
    getline(queryText, rest);
    if(!rest.find('#')){
//        std::cout << rest << std::endl;
        std::istringstream restStream;
        restStream.str(rest);
        restStream >> this->message.command;
        //    std::cout << this->message.command << "  here command " << std::endl;
        char ch;
        restStream.get(ch);
        getline(restStream, arg);
        this->message.commandArg = arg;
        //    std::cout << this->message.commandArg << "  here commandArg " << std::endl;
    }
    else{
        std::istringstream restStream;
        restStream.str(rest);
        getline(restStream, mes);
        this->message.command = mes;
    }
    queryText.clear();
}


void queryData::printData() {
    std::cout << "time is: " << message.time << " group is: " << message.group
        << " name is: " << message.name << " command is: " << message.command
        << " commandArg is: " << message.commandArg << std::endl;

}

std::string queryData::readCommand() {
    return message.command;
}

std::string queryData::readCommandArg() {
    return message.commandArg;
}

groupData::groupData(int num) {
    this->num = num;
    this->group = new groupName[num];
}

void groupData::loadData(std::ifstream &fileList) {
    int counter = 0;
    //TODO: what is the loaded file has more lines than indicated
    while(fileList) {
        if (fileList) {
            std::string line;
            std::getline(fileList, line);
            this->group[counter].name = line;
            counter = counter + 1;
        }
    }
}

void groupData::printData() {
    for(int i = 0; i < num; i++){
        std::cout << group[i].name << " name is: " << std::endl;
    }
}
