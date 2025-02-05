//
// Created by Samir Daoud and Mohammad Agbaria on 2/1/25.
//

#include "TaskManager.h"

// Private Functions

void TaskManager::addPerson(const string &name) {

    if (personsCount == MAX_PERSONS) {
        throw std::runtime_error("Employees limit reached.");
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

int TaskManager::findPerson (const string& name) const {
    for (int i = 0; i < MAX_PERSONS; i++) {
        if (persons[i].getName() == name) return i;
    }
    return MAX_PERSONS;
}

bool TaskManager::isTaskType(const Task &task, const string &type) {

    string ogType = taskTypeToString(task.getType());
    return (ogType == type) ;
}

// Constructors

TaskManager::TaskManager() : personsCount(0), tasksCount(0) {} // default constructor


// Public Functions

void TaskManager::assignTask(const string &personName, const Task &task) {

    int index = findPerson(personName);

    //check if person is already in the system
    if (index == MAX_PERSONS) {
        //person not found, check if full

        if (personsCount == MAX_PERSONS) {
            throw std::runtime_error("Employees limit reached.");
        }
        //there is still room for one more person
        addPerson(personName);
        index = personsCount-1; //set index to latest person
    }

    Task copy = task;
    copy.setId(tasksCount);
    tasksCount++;
    persons[index].assignTask(copy); //assign task called for Person class
}


SortedList<Task> TaskManager::merge(const string& typeFilter) const {

    typedef mtm::SortedList<Task> TaskList;

    TaskList merged;

    for (int i = 0; i < personsCount; i++) {
        TaskList currTasks = persons[i].getTasks();

        if (typeFilter != "no_filter") { //we want filter
            //lambda expression
            currTasks = currTasks.filter([typeFilter](const Task& task) { return isTaskType(task, typeFilter); });
        }

        for (const auto &taskLocal : currTasks) {
            merged.insert(taskLocal);
        }
    }


    return merged;
}


void TaskManager::completeTask(const string &personName) {

    int index = findPerson(personName);
    if (index == MAX_PERSONS) return; // not in company, nothing to do here.

    persons[index].completeTask();
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {

    typedef mtm::SortedList<Task> TasksList;

    if (priority <= 0) return; // nothing to do if negative or 0.

    string typeFilter = taskTypeToString(type);

    for (int i = 0; i < personsCount; i++) {
        TasksList tasksList = persons[i].getTasks(); // REFERENCE to getTasks, NOT A COPY
        TasksList updatedTasksList; //new empty list made using default ctor

        //traverse the list
        //code for iterator not done yet -> syntax error
        for (const Task &task : tasksList) { //iterate over tasks in list

            if (taskTypeToString(task.getType()) == typeFilter) { //found the type
                Task updatedTask(task.getPriority() + priority, type, task.getDescription());
                updatedTask.setId(task.getId());
                updatedTasksList.insert(updatedTask);
            } else {
                updatedTasksList.insert(task);
            }
        } //tasksList loo[

        persons[i].setTasks(updatedTasksList);
        //delete &tasksList; no need wasn't allocated here

    } //persons loop
}


// Print functions

void TaskManager::printAllEmployees() const {

    for (int i = 0; i < personsCount && i < MAX_PERSONS; i++) {
        std::cout << persons[i] << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {

    typedef mtm::SortedList<Task> TaskList;

    string typeString = taskTypeToString(type);
    TaskList mergedList = merge(typeString);

    for (const Task& localTasks : mergedList) {
        std::cout << localTasks << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    typedef mtm::SortedList<Task> TaskList;

    //string typeString = taskTypeToString(type);
    TaskList mergedList = merge();

    for (const Task& localTasks : mergedList) {
        std::cout << localTasks << std::endl;
    }

}













