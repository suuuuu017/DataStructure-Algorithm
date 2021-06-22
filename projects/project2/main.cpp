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

    courses.printAllData();



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
        std::cin.clear();
    }


}