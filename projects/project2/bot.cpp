#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "bot.h"

courseData::courseData(int num) {
    //EFFECTS: construct a courseData class with the input num and a courseInfo array of size num
    this->num = num;
    this->course = new courseInfo[num];
}

int courseData::readNum() {
    //EFFECTS: return the number of total courses
    return this->num;
}

void courseData::loadData(std::ifstream &fileList) {
    //EFFECTS: load course data into the courseData class
    //MODIFIES: courseData
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
                while(getline(iStream, name, ',')) {
                    this->course[counter].name = name;
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
    //EFFECTS: print all the data in the courseData class to the standard output for debugging
    for(int i = 0; i < num; i++){
        std::cout << course[i].code << " name is: " << course[i].name
                    << " instructor is: " << course[i].instructor << std::endl;
    }
}

std::string courseData::readCode(int i) {
    //REQUIRES: a int i within the number of total course
    //EFFECTS: return the course code of the give index
    return course[i].code;
}

std::string courseData::readInstructor(int i){
    //REQUIRES: a int i within the number of total course
    //EFFECTS: return the instructor of the give index
    return course[i].instructor;
}

void courseData::printData(int i){
    //REQUIRES: a int i within the number of total course
    //EFFECTS: print the course info in the required syntax to the standard output
    std::cout << "Course Code: " << course[i].code << std::endl
        << "Course Name: " << course[i].name << std::endl
        << "Instructor: " << course[i].instructor << std::endl;
}

queryData::queryData() {};
    //EFFECTS: construct a queryData structure

void queryData::loadData(std::istream & queryText) {
    //REQUIRES: input data in the format of time,group,username,#command,optional argument
    //EFFECTS: load the query into the queryData structure
    //MODIFIES: queryData
    std::string time;
    std::string group;
    std::string name;
    std::string command;
    std::string commandArg;
    std::string arg;
    std::string mes;

    if(getline(queryText, time, ',')){
        this->message.time = time;
        if(getline(queryText, group, ',')) {
            this->message.group = group;
            if (getline(queryText, name, ',')){
                this->message.name = name;
            }
        }
    }

    std::string rest;

    getline(queryText, rest);
    if((rest.find('#') != std::string::npos && (!rest.find_first_of('#')))){
        std::istringstream restStream;
        restStream.str(rest);
        restStream >> this->message.command;
        if(this->message.command == "#course" ||
            this->message.command == "#instructor"||
            this->message.command == "#help"||
            this->message.command == "#time"||
            this->message.command == "#stop"){
            restStream >> this->message.commandArg;
        }
        else{
            getline(restStream, arg);
            this->message.commandArg = arg;
        }
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
    //EFFECTS: print the query message to the standard output for debugging
    std::cout << "time is: " << message.time << " group is: " << message.group
        << " name is: " << message.name << " command is: " << message.command
        << " commandArg is: " << message.commandArg << std::endl;

}

std::string queryData::readCommand() {
    //EFFECTS: return the command of the query message
    return message.command;
}

std::string queryData::readCommandArg() {
    //EFFECTS: return the optional argument of the query message
    return message.commandArg;
}

std::string queryData::readTime() {
    //EFFECTS: return the time of the query message
    return message.time;
}

std::string queryData::readGroup() {
    //EFFECTS: return the group of the query message
    return message.group;
}

std::string queryData::readName() {
    //EFFECTS: return the username of the query message
    return message.name;
}

groupList::groupList() {
}
    //EFFECTS: construct a groupList class

adminName * groupList::admin(int numOfAdmin) {
    //EFFECTS: construct a array of size of numOfAdmin to store admin names
    adminName * adminL = new adminName[numOfAdmin];
    return adminL;
}

groupData::groupData(int numofGroup, std::string detailedListDir) {
    //EFFECTS: construct a groupData class
    this->numOfGroup = numofGroup;
    this->detailedList = detailedListDir;
    this->group = new groupList[numofGroup];
}

void groupData::loadData(std::ifstream &fileList) {
    //EFFECTS: load the groupdata from file to groupData structure
    //MODIFIES: groupData
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
    //EFFECTS: load the detailed group admin data to groupData structure
    //MODIFIES: groupData
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

        this->group[i].numOfAdmin = numAdmin;
        this->group[i].adminList = group->admin(numAdmin);

        for(int j = 0; j < this->group[i].numOfAdmin; j ++){
            std::string name;
            getline(admNameRead, name);
            this->group[i].adminList[j].name = name;
        }

    }
}

std::string groupData::readGroupName(int i) {
    //REQUIRES: an int within the number of total group numbers
    //EFFECTS: return the name string of the indexed group
    return group[i].name;
}

int groupData::readnumOfGroup() {
    //EFFECTS: return the number of total group
    return numOfGroup;
}

int groupData::readNumAdmin(int groupNum) {
    //REQUIRES: an int within the number of total group numbers
    //EFFECTS: return number of admins of the indexed group
    return group[groupNum].numOfAdmin;
}

std::string groupData::readNumAdmin(int groupNum, int adminNum) {
    //REQUIRES: an int within the number of total group numbers, an int within the number of indexed group admin number
    //EFFECTS: return the indexed admin name
    return group[groupNum].adminList[adminNum].name;
}

void groupData::printData() {
    //EFFECTS: read the detailed group data for debugging
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









