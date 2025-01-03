//
// Created by Samir Daoud and Mohammad Agbaria on 2/1/25.
//

#include "TaskManager.h"

// Private Functions
void TaskManager::addPerson(const string &name) {

    if (personsCount == MAX_PERSONS) {
        throw std::runtime_error("Persons limit reached. Max is ten people.");
    }

    //space left - add new person
    Person newPerson (name);

    typedef SortedList<Task> TaskList ; //import SortedList type Task
    TaskList emptyList; // create new list using default constructor
    newPerson.setTasks(emptyList);
    persons[personsCount] = newPerson; //added using default assignment operator
    //we can use default assignment op since we want to add by reference
    personsCount++;

}

int TaskManager::findPerson (const string& name) {
    for (int i = 0; i < MAX_PERSONS; i++) {
        if (persons[i].getName() == name) return i;
    }
    return MAX_PERSONS;
}

bool TaskManager::isTaskType(const Task &task, string &type) {

    string ogType = taskTypeToString(task.getType());
    return (ogType == type) ;
}

// Constructors

TaskManager::TaskManager() : personsCount(0), countID(0) {} // default constructor


// Public Functions

void TaskManager::assignTask(const string &personName, const Task &task) {

    int index = findPerson(personName);

    if (index == MAX_PERSONS) {
        //person not found, we need to add
        addPerson(personName);
        index = personsCount; //set ID to latest person
    }

    persons[index].assignTask(task);
}



