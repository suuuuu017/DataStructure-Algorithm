#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>

#include "bot.h"

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

    courses.printData();

    queryData query;

    std::string line;

    while(getline(std::cin, line)){
        std::istringstream q;
        q.str(line);
        query.loadData(q);
        query.printData();
        std::cin.clear();
        std::string com;
        com = query.readCommand();

    }


}