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

std::string courseData::readInstructor(int i){
    return course[i].instructor;
}

void courseData::printData(int i){
    std::cout << "Course Code: " << course[i].code << std::endl
        << "Course Name: " << course[i].name << std::endl
        << "Instructor: " << course[i].instructor << std::endl;
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
//    std::cout << rest.find_first_of('#') << std::endl;
    if(rest.find('#') != std::string::npos && (!rest.find_first_of('#'))){
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

std::string queryData::readTime() {
    return message.time;
}

std::string queryData::readGroup() {
    return message.group;
}

std::string queryData::readName() {
    return message.name;
}

groupList::groupList() {
}

adminName * groupList::admin(int numOfAdmin) {
    adminName * adminL = new adminName[numOfAdmin];
    return adminL;
}

groupData::groupData(int numofGroup, std::string detailedListDir) {
    this->numOfGroup = numofGroup;
    this->detailedList = detailedListDir;
    this->group = new groupList[numofGroup];
}

void groupData::loadData(std::ifstream &fileList) {
    int counter = 0;
    //TODO: what is the loaded file has more lines than indicated
    while(fileList && counter < numOfGroup) {
        if (fileList) {
            std::string line;
            std::getline(fileList, line);
            this->group[counter].name = line;
            counter = counter + 1;
        }
    }
}

void groupData::loadDetailedAdmin() {
    for(int i = 0; i < numOfGroup; i++){
        std::string adminFileAdd;
        adminFileAdd = detailedList + '/' + readGroupName(i);
        std::ifstream admNameRead;
        admNameRead.open(adminFileAdd);
        std::string numAdminThisGroup;
        getline(admNameRead, numAdminThisGroup);
        std::istringstream numAdminThisGroupNum;
        numAdminThisGroupNum.str(numAdminThisGroup);
        int numAdmin;
        numAdminThisGroupNum >> numAdmin;

//        std::cout << numAdmin << " is the number correct" << std::endl;

        this->group[i].numOfAdmin = numAdmin;
        this->group[i].adminList = group->admin(numAdmin);

        for(int j = 0; j < this->group[i].numOfAdmin; j ++){
            std::string name;
            getline(admNameRead, name);
//            std::cout << name << " is the name correct" << std::endl;
            this->group[i].adminList[j].name = name;
        }

    }
}

std::string groupData::readGroupName(int i) {
    return group[i].name;
}

int groupData::readnumOfGroup() {
    return numOfGroup;
}

int groupData::readNumAdmin(int groupNum) {
    return group[groupNum].numOfAdmin;
}

std::string groupData::readNumAdmin(int groupNum, int adminNum) {
    return group[groupNum].adminList[adminNum].name;
}

void groupData::printData() {
    std::cout << numOfGroup << " the num of group" << std::endl;
    std::cout << detailedList << " here is where to find the detail" << std::endl;
    for(int i = 0; i < numOfGroup; i++){
        std::cout << group[i].name << " name is: "
                 << std::endl;
        for(int j = 0; j < group[i].numOfAdmin ; j ++){
            std::cout << group[i].adminList[j].name << " detailed name is: "
                      << std::endl;
        }
    }
}









