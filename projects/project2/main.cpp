#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "bot.h"
#include "constants.h"
#include "rand.h"

int main(int argc, char * argv[]){
    if(argc < 4 ){
        std::cout << MISSING_ARGUMENT_MESSAGE << std::endl;
        return 0;
    }
    if(argc > 4 ){
        return 0;
    }
    std::string checkSeed;
    checkSeed = argv[3];
    for(long unsigned int i = 0; i < checkSeed.length(); i++){
        if(!isdigit(checkSeed[i])){
            std::cout << INVALID_ARGUMENT_MESSAGE << std::endl;
            return 0;
        }
    }
    std::string courseDataDir;
    courseDataDir = argv[1];
    std::ifstream courseRead;
    courseRead.open(courseDataDir);
    if(courseRead.fail()){
        std::cout << CANNOT_OPEN_FILE_PREFIX << courseDataDir << std::endl;
        return 0;
    }

    std::string numOfCourse;
    int num;
    while(courseRead){
        getline(courseRead, numOfCourse);
        break;
    }
    std::istringstream numC;
    numC.str(numOfCourse);
    numC >> num;


    courseData courses(num);
    courses.loadData(courseRead);

    courseRead.close();
//    courses.printAllData();

    std::string groupDataDir;
    groupDataDir = argv[2];
    std::ifstream groupDataRead;
    groupDataRead.open(groupDataDir);
    if(groupDataRead.fail()){
        std::cout << CANNOT_OPEN_FILE_PREFIX << groupDataDir << std::endl;
        return 0;
    }
    std::string detailedListDir;
    std::string numOfGroup;
    while(groupDataRead){
        getline(groupDataRead, detailedListDir);
        break;
    }
    if(groupDataRead){
        getline(groupDataRead, numOfGroup);
    }
    std::istringstream numG;
    numG.str(numOfGroup);
    int numGroup;
    numG >> numGroup;

    groupData groups(numGroup, detailedListDir);
    groups.loadData(groupDataRead);
    groups.loadDetailedAdmin();


//    groups.printData();

    groupDataRead.close();

    std::string line;

    int randomSeed = atoi(argv[3]);
    initializeWithSeed(randomSeed);
    while(getline(std::cin, line)){
        std::istringstream q;
        q.str(line);
        queryData query;
        query.loadData(q);
//        query.printData();
        std::cin.clear();

        std::string comGroup;
        comGroup = query.readGroup();

        bool findGroup = false;

        for(int i = 0; i < groups.readnumOfGroup(); i++){
            if(comGroup == groups.readGroupName(i)){
                findGroup = true;
            }
        }

        if(findGroup) {

            std::string com;
            com = query.readCommand();
            if (com == "#stop") {
                bool adminFlag = false;
                for (int i = 0; i < groups.readnumOfGroup(); i++) {
                    if (groups.readGroupName(i) == comGroup) {
                        for (int j = 0; j < groups.readNumAdmin(i); j++) {
                            if (query.readName() == groups.readNumAdmin(i, j)) {
                                adminFlag = true;
                            }
                        }
                    }
                }
                if (adminFlag) {
                    std::cout << EXIT_PROMPT << std::endl;
                    std::cout << std::endl;
                    break;
                }
                else {
                    std::cout << STOP_BOT_FAIL << std::endl;
                    std::cout << std::endl;
                }
            }
            else if (com == "#course") {
                std::string comArg = query.readCommandArg();
                if (comArg.empty()) {
                    std::cout << MISSING_KEYWORD << std::endl;
                } else {
                    int dummy = courses.readNum();
                    bool flag = false;
                    for (int i = 0; i < dummy; i++) {
                        if ((courses.readCode(i).find(query.readCommandArg())) != std::string::npos) {
                            courses.printData(i);
                            flag = true;
                        }
                    }
                    if (!flag) {
                        std::cout << COURSE_NOT_FOUND << std::endl;
                    }
                }
                std::cout << std::endl;
            }
            else if (com == "#instructor") {
                std::string comArg = query.readCommandArg();
                if (comArg.empty()) {
                    std::cout << MISSING_KEYWORD << std::endl;
                }
                else {
                    int dummy = courses.readNum();
                    bool flag = false;
                    std::string nameBook[dummy];
                    int nameCounter = 0;
                    for (int i = 0; i < dummy; i++) {
                        if ((courses.readInstructor(i).find(query.readCommandArg())) != std::string::npos) {
                            bool findInstructor = false;
                            for (int j = 0; j < dummy; j++) {
                                if (nameBook[j] == courses.readInstructor(i)) {
                                    findInstructor = true;
                                    break;
                                }
                            }
                            if(!findInstructor){
                                nameBook[nameCounter] = courses.readInstructor(i);
                                nameCounter = nameCounter + 1;
                            }



                            flag = true;
                        }
                    }
                    for (int i = 0; i < nameCounter; i++) {
                        std::cout << "Instructor: " << nameBook[i] << std::endl;
                        std::cout << "Courses:";
                        for (int j = 0; j < dummy; j++) {
                            if ((courses.readInstructor(j).find(nameBook[i])) != std::string::npos) {
                                std::cout << " " << courses.readCode(j);
                            }
                        }
                        std::cout << std::endl;
                    }
                    if (!flag) {
                        std::cout << FACULTY_NOT_FOUND << std::endl;
                    }
                }
                std::cout << std::endl;
            }
            else if (com == "#time") {
                std::string comArg = query.readCommandArg();
                std::cout << query.readTime() << std::endl;
                std::cout << std::endl;
            }
            else if (com == "#help") {
                std::cout << HELP_TEXT << std::endl;
                std::cout << std::endl;
            }
            else {
                if (!query.readCommand().empty()) {

                    RespChoice choice = randomResponse();
                    if (choice == 1) {
                        std::cout << query.readCommand() << query.readCommandArg() << std::endl;
                    }
                    if (choice == 2) {
                        if (flipCoin()) {
                            std::cout << "Respect " << query.readCommand() << query.readCommandArg()  << std::endl;
                        } else {
                            std::cout << "I really admire " << query.readCommand() << query.readCommandArg()  << std::endl;
                        }
                    }
                    if (choice == 0) {
                    }
                    std::cout << std::endl;
                }
            }
        }

        std::cin.clear();
    }


}