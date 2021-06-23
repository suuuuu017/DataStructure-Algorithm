#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "bot.h"
#include "constants.h"

int main(int argc, char * argv[]){
    std::string courseDataDir;
    courseDataDir = argv[1];
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

    groups.printData();

    std::string line;

    while(getline(std::cin, line)){
        std::istringstream q;
        q.str(line);
        queryData query;
        query.loadData(q);
        query.printData();
        std::cin.clear();
        std::string com;
        com = query.readCommand();
        if(com == "#stop"){
            break;
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

        else if(com == "#time"){
            //TODO: what do if the command is time1
            std::string comArg = query.readCommandArg();
            std::cout << query.readTime() << std::endl;
        }

        else if(com == "#help"){
            std::cout << HELP_TEXT << std::endl;
        }

        std::cin.clear();
    }


}