/*
 * VE280 Lab 7, SU2021
 * Created by cyx on 20-5-22.
 * Modified by makersmelx on June 28th, 2021.
 */

#include <iostream>
#include "course.h"

void TechnicalCourse::updateTask(const std::string &type, int index, int dueMonth, int dueDay)
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its dueMonth & dueDay ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    // TODO: implement this function
    bool found = false;
    if(numTasks < sizeTasks){
        for(int i = 0; i < numTasks; i++){
            if(type == tasks[i].type && index == tasks[i].index){
                found = true;
                tasks[i].dueMonth = dueMonth;
                tasks[i].dueDay = dueDay;
                break;
            }
        }
    }
    if((!found) && numTasks < sizeTasks){
        tasks[numTasks].type = type;
        tasks[numTasks].index = index;
        tasks[numTasks].dueMonth = dueMonth;
        tasks[numTasks].dueDay = dueDay;
        numTasks = numTasks + 1;
        if(type == "Lab" || type == "Project"){
            std::cout << courseCode << " " << type << " " << index <<
                " is released! Submit it via oj!" << std::endl;
        }
        else{
            std::cout << courseCode << " " << type << " " << index <<
                      " is released! Submit it via canvas!" << std::endl;
        }
    }
    else if((!found) && numTasks >= sizeTasks){
        TooManyTasks tmt;
        throw tmt;
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finishMonth, int finishDay)
// REQUIRES: Task index of type is in tasks. finishMonth and finishDay are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    // TODO: implement this function
    bool overdue = false;
    int victim = 0;
    bool found = false;
    if(numTasks < sizeTasks && numTasks > 0){
        for(int i = 0; i < numTasks; i++){
            if(type == tasks[i].type && index == tasks[i].index){
                found = true;
                victim = i;
                break;
            }
        }
    }
    if(found){
        if(tasks[victim].dueMonth < finishMonth){
            overdue = true;
        }
        else if(tasks[victim].dueMonth == finishMonth){
            if(tasks[victim].dueDay < finishDay){
                overdue = true;
            }
            else{
                overdue = false;
            }
        }
        else if(tasks[victim].dueMonth > finishMonth){
            overdue = false;
        }
    }
    numTasks = numTasks - 1;
    for(int i = victim; i < numTasks; i++){
        tasks[i] = tasks[i+1];
    }
    if(found && overdue){
        std::cout << courseCode << " " << type << " " << index << " is overdue!" << std::endl;
    }
    else if(found && (!overdue)){
        std::cout << courseCode << " " << type << " " << index << " is finished!" << std::endl;
    }
    if(!found){
        return;
    }
}

void TechnicalCourse::print() {
    std::cout << courseCode << std::endl;
    for (int i = 0; i < numTasks; ++i) {
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].dueMonth << "/" << tasks[i].dueDay << std::endl;
    }
}

void UpperLevelTechnicalCourse::updateTask(const std::string &type, int index, int dueMonth, int dueDay)
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & dueMonth & dueDay if its dueMonth/dueDay is changed,
//          do nothing if its dueMonth/dueDay is unchanged.
{
    // TODO: implement this function
    bool found = false;
    if(numTasks < sizeTasks){
        for(int i = 0; i < numTasks; i++){
            if(type == tasks[i].type && index == tasks[i].index){
                found = true;
                tasks[i].dueMonth = dueMonth;
                tasks[i].dueDay = dueDay;
                break;
            }
        }
    }
    if((!found) && numTasks < sizeTasks){
        tasks[numTasks].type = type;
        tasks[numTasks].index = index;
        tasks[numTasks].dueMonth = dueMonth;
        tasks[numTasks].dueDay = dueDay;
        numTasks = numTasks + 1;
        if(type == "Lab" || type == "Project"){
            std::cout << courseCode << " " << type << " " << index <<
                      " is released! Submit it via oj!" << std::endl;
        }
        else if(type == "Team Project"){
            std::cout << courseCode << " " << type << " " << index <<
                      " is released! Submit it via github!" << std::endl;
        }
        else{
            std::cout << courseCode << " " << type << " " << index <<
                      " is released! Submit it via canvas!" << std::endl;
        }
    }
    else if((!found) && numTasks >= sizeTasks){
        TooManyTasks tmt;
        throw tmt;
    }
    for(int i = 0; i < numTasks - 1; i++){
        for(int j = 0; j < numTasks - 1 - i; j++){
            if(tasks[j].dueMonth > tasks[j+1].dueMonth){
                Task tmp;
                tmp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = tmp;
            }
            else if(tasks[j].dueMonth == tasks[j+1].dueMonth && tasks[j].dueDay > tasks[j+1].dueDay){
                Task tmp;
                tmp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = tmp;
            }
        }
    }
}

Course *create(const std::string &classType, const std::string &courseCode) {
    if (classType == "Technical") {
        return new TechnicalCourse(courseCode);
    } else if (classType == "Upper Level Technical") {
        return new UpperLevelTechnicalCourse(courseCode);
    } else {
        return nullptr;
    }
}

Course *create(const std::string &classType, const std::string &courseCode, const int &size) {
    if (classType == "Technical") {
        return new TechnicalCourse(courseCode, size);
    } else if (classType == "Upper Level Technical") {
        return new UpperLevelTechnicalCourse(courseCode, size);
    } else {
        return nullptr;
    }
}
