#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "Dlist.h"
#include "Instr.h"

int main(int argc, char *argv[])
{
    //TODO:write your code here.
    bool slient = false;
    if(argc == 2){
        std::string option = argv[1];
        if(option == "-s"){
            slient = true;
        }
    }
//    std::cout << "slient is " << slient << std::endl;

    std::string line;

    int stackNum = 0;
    int queueNum = 0;

    while(getline(std::cin, line)) {
        std::cout << line << std::endl;
        std::istringstream ss(line);
        ss >> stackNum >> queueNum;
        break;
    }
    std::cout << stackNum << " " << queueNum << std::endl;

    Dlist<int> stack;

    while(getline(std::cin, line)) {
        std::cout << line << std::endl;
        std::istringstream ss(line);
        while(ss.peek() != EOF){
            int tmpVal = 0;
            ss >> tmpVal;
            int *ip = new int(tmpVal);
            stack.insertFront(ip);
        }
        break;
    }
    std::cout << "stack is " << stack << std::endl;

    Dlist<Instr> queue;

    while(getline(std::cin, line)) {
        std::istringstream ss(line);
        auto *instr = new Instr;
        ss >> *instr;
        queue.insertBack(instr);
    }
    std::cout << "queue is " << queue << std::endl;

    Dlist<int> memory;

    while(getline(std::cin, line)) {
        std::cout << line << std::endl;
        std::istringstream ss(line);
        while(ss.peek() != EOF){
            int tmpVal = 0;
            ss >> tmpVal;
            int *ip = new int(tmpVal);
            memory.insertFront(ip);
        }
        break;
    }
    std::cout << "memory is " << memory << std::endl;


    return 0;
}
