#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "Dlist.h"
#include "Instr.h"

void addInstr(Dlist<int> &stack){
    int * ele1 = stack.removeFront();
    int * ele2 = stack.removeFront();
    int result = *ele1 + *ele2;
    int * ele3 = new int(result);
    stack.insertFront(ele3);
}

void norInstr(Dlist<int> &stack){
    int * ele1 = stack.removeFront();
    int * ele2 = stack.removeFront();
    int result = ~ (*ele1 | *ele2);
    int * ele3 = new int(result);
    stack.insertFront(ele3);
}

void ifzInstr(Instr& it, Dlist<int> &stack, Dlist<Instr> &queue){
    int * stackNum = stack.removeFront();
    if(*stackNum == 0){
        int removeNum = it.parameter;
        for(int i = 0; i < removeNum; i++){
            queue.removeFront();
        }
    }
}

void loadInstr(Dlist<int> &stack, int memoryArray[]){
    int * memoryAdd = stack.removeFront();
    int memoryCon = memoryArray[*memoryAdd];
    int * tmp = new int(memoryCon);
    stack.insertFront(tmp);
}

void storeInstr(Dlist<int> &stack, int memoryArray[]){
    int * address = stack.removeFront();
    int * value = stack.removeFront();
    memoryArray[*address] = *value;
}

void popInstr(Dlist<int> &stack){
    stack.removeFront();
}

void pushiInstr(Instr& it, Dlist<int> &stack){
    int * push = new int(it.parameter);
    stack.insertFront(push);
}

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

    std::cout << line << std::endl;
    std::istringstream ss(line);
    int memoryLength = 0;
    while(ss.peek() != EOF){
        int tmpVal = 0;
        ss >> tmpVal;
        int *ip = new int(tmpVal);
        memory.insertBack(ip);
        memoryLength = memoryLength + 1;
    }
    std::cout << "memory Length is " << memoryLength << std::endl;

    int memoryArray[memoryLength];
    for(int i = 0; i < memoryLength; i++){
        memoryArray[i] = *memory.removeFront();
    }

    std::cout << "memory is ";
    for(int i = 0; i < memoryLength; i++){
        std::cout << memoryArray[i] << " ";
    }
    std::cout << std::endl;

    while(!queue.isEmpty()){
        Instr * currentIntr = queue.removeFront();
        if(currentIntr->name == InstrName::HALT){
            break;
        }
        else if(currentIntr->name == InstrName::ADD){
            addInstr(stack);
        }
        else if(currentIntr->name == InstrName::NOR){
            norInstr(stack);
        }
        else if(currentIntr->name == InstrName::IFZ){
            ifzInstr(*currentIntr, stack, queue);
        }
        else if(currentIntr->name == InstrName::LOAD){
            loadInstr(stack, memoryArray);
        }
        else if(currentIntr->name == InstrName::STORE){
            storeInstr(stack, memoryArray);
        }
        else if(currentIntr->name == InstrName::POP){
            popInstr(stack);
        }
        else if(currentIntr->name == InstrName::PUSHI){
            pushiInstr(*currentIntr, stack);
        }
        else if(currentIntr->name == InstrName::NOOP){
            continue;
        }
    }

    std::cout << "resulting stack is " << stack << std::endl;
    std::cout << "resulting queue is " << queue << std::endl;
    std::cout << "memory is ";
    for(int i = 0; i < memoryLength; i++){
        std::cout << memoryArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
