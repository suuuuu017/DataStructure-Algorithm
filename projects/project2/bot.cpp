#include <fstream>
#include <sstream>
#include <string>
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
            }

        }
    }
}


