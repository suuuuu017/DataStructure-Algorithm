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
    std::string courseDataDir;
    courseDataDir = argv[1];
    //TODO program argument check
    std::ifstream courseRead;
    courseRead.open(courseDataDir);

    std::string numOfCourse;
    int num;
    while(courseRead){
        getline(courseRead, numOfCourse);
//        std::cout << "num is string " << numOfCourse;
        break;
    }
    std::istringstream numC;
    numC.str(numOfCourse);
    numC >> num;

//    std::cout << "num is " << num;

    courseData courses(num);
    courses.loadData(courseRead);

    courseRead.close();
//    courses.printAllData();

    std::string groupDataDir;
    groupDataDir = argv[2];
    std::ifstream groupDataRead;
    groupDataRead.open(groupDataDir);
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


    groups.printData();

    groupDataRead.close();

    std::string line;

    int randomSeed = atoi(argv[3]);
    initializeWithSeed(randomSeed);

    while(getline(std::cin, line)){
        std::istringstream q;
        q.str(line);
        queryData query;
        query.loadData(q);
        query.printData();
        std::cin.clear();

        std::string comGroup;
        comGroup = query.readGroup();

        bool findGroup = false;

        for(int i = 0; i < groups.readnumOfGroup(); i++){
            if(comGroup == groups.readGroupName(i)){
                findGroup = true;
            }
        }

//        if(!findGroup){
//            //TODO: check if it will break out here
//            break;
//        }

        std::string com;
        com = query.readCommand();
        if(com == "#stop"){
            bool adminFlag = false;
            for(int i = 0; i < groups.readnumOfGroup(); i++){
                if(groups.readGroupName(i) == comGroup){
                    for(int j = 0; j < groups.readNumAdmin(i); j++){
                        if(query.readName() == groups.readNumAdmin(i, j)){
                            adminFlag = true;
                        }
                    }
                }
            }
            if(adminFlag){
                std::cout << EXIT_PROMPT << std::endl;
                break;
            }
            else{
                std::cout << STOP_BOT_FAIL <<std::endl;
            }
        }

        else if(com == "#course"){
            std::string comArg = query.readCommandArg();
            if(comArg.empty()){
                std::cout << MISSING_KEYWORD << std::endl;
            }
            else {
                int dummy = courses.readNum();
                bool flag = false;
                for (int i = 0; i < dummy; i++) {
                    //TODO: why here is find while # is !find
                    //TODO: what if the input command is ## in a roll
                    if ((courses.readCode(i).find(query.readCommandArg())) != std::string::npos) {
                        courses.printData(i);
                        flag = true;
                    }
                }
                if (!flag) {
                    std::cout << COURSE_NOT_FOUND << std::endl;
                }
            }
        }

        else if(com == "#instructor"){
            std::string comArg = query.readCommandArg();
            if(comArg.empty()){
                std::cout << MISSING_KEYWORD << std::endl;
            }
            else {
                int dummy = courses.readNum();
                bool flag = false;
                for (int i = 0; i < dummy; i++) {
                    if ((courses.readInstructor(i).find(query.readCommandArg())) != std::string::npos) {
                        courses.printData(i);
                        flag = true;
                    }
                }
                if (!flag) {
                    std::cout << FACULTY_NOT_FOUND << std::endl;
                }
            }
        }

        else if(com == "#time"){
            //TODO: what do if the command is time1
            std::string comArg = query.readCommandArg();
            std::cout << query.readTime() << std::endl;
        }

        else if(com == "#help"){
            std::cout << HELP_TEXT << std::endl;
        }

        else{
            if(!query.readCommand().empty()){
//                std::cout << query.readCommand() << " to repeat" << std::endl;

                RespChoice choice = randomResponse();
//                std::cout << choice << " to repeat" << std::endl;
                if(choice == 1){
                    std::cout << query.readCommand() << std::endl;
                }
                if(choice == 2){
                    if(flipCoin()){
                        std::cout << "Respect " << query.readCommand() << std::endl;
                    }
                    else{
                        std::cout << "I really admire " << query.readCommand() << std::endl;
                    }
                }
                if(choice == 0){
                    std::cout << std::endl;
                }
            }
        }

        std::cin.clear();
    }


}