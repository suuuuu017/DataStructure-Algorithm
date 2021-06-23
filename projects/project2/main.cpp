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
        //TODO: does this need an empty line?
        return 1;
    }
    if(argc > 4 ){
        //TODO: what if argument is more than 3
        return 1;
    }
    std::string checkSeed;
    checkSeed = argv[3];
    for(int i = 0; i < checkSeed.length(); i++){
        if(!isdigit(checkSeed[i])){
            std::cout << INVALID_ARGUMENT_MESSAGE << std::endl;
            //TODO: does this need an empty line?
            return 1;
        }
    }
    std::string courseDataDir;
    courseDataDir = argv[1];
    //TODO program argument check
    std::ifstream courseRead;
    courseRead.open(courseDataDir);
    if(courseRead.fail()){
        std::cout << CANNOT_OPEN_FILE_PREFIX << courseDataDir << std::endl;
        //TODO: does this need an empty line?
        return 1;
    }

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
    if(groupDataRead.fail()){
        std::cout << CANNOT_OPEN_FILE_PREFIX << groupDataDir << std::endl;
        //TODO: does this need an empty line?
        return 1;
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
        //TODO: test if there is space around the comma
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
                std::cout << std::endl;
                break;
            }
            else{
                std::cout << STOP_BOT_FAIL <<std::endl;
                std::cout << std::endl;
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
            std::cout << std::endl;
        }

        else if(com == "#instructor"){
            std::string comArg = query.readCommandArg();
            if(comArg.empty()){
                std::cout << MISSING_KEYWORD << std::endl;
            }
            else {
                int dummy = courses.readNum();
                bool flag = false;
                std::string nameBook[dummy];
                int nameCounter = 0;
                for (int i = 0; i < dummy; i++) {
                    if ((courses.readInstructor(i).find(query.readCommandArg())) != std::string::npos) {
                        for(int j = 0; j < dummy; j++){
                            if(nameBook[j] == courses.readInstructor(i)){
//                                std::cout << "here! " << courses.readInstructor(i) << std::endl;
                                break;
                            }
                            else{
//                                std::cout << "here " << courses.readInstructor(i) << std::endl;
                                nameBook[nameCounter] = courses.readInstructor(i);
                                nameCounter = nameCounter + 1;
                                std::cout << nameCounter << std::endl;
                                break;
                            }
                        }
//                        courses.printData(i);
                        flag = true;
                    }
                }
                std::cout << nameCounter << std::endl;
                for(int i = 0; i < nameCounter; i++){
                    std::cout << nameBook[i] << std::endl;
                }
                for(int i = 0; i < nameCounter; i++){
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

        else if(com == "#time"){
            //TODO: what do if the command is time1
            std::string comArg = query.readCommandArg();
            std::cout << query.readTime() << std::endl;
            std::cout << std::endl;
        }

        else if(com == "#help"){
            std::cout << HELP_TEXT << std::endl;
            std::cout << std::endl;
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
                }
                //TODO: does do nothing needs to print out an empty line
                //TODO: check if the command can be empty
                std::cout << std::endl;
            }
        }

        std::cin.clear();
    }


}