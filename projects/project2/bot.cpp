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


