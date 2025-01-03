
#pragma once

#include "Task.h"
#include "Person.h"

/**
 * @brief Class managing tasks assigned to multiple persons.
 *
 * TaskManager includes and array of people (Person).
 * Each person has a number of tasks (SortedList of Tasks within the Person class).
 * TaskManager's job is to assign and manage tasks to the Persons within the array.
 */
class TaskManager {
private:
    /**
     * @brief Maximum number of persons the TaskManager can handle.
     */
    static const int MAX_PERSONS = 10;

    // Additional private fields

    Person persons [MAX_PERSONS]; // array of persons with tasks assigned
    //Note: first person added gets index 0, second 1,..., last MAX_PERSONS-1.

    int personsCount; // number of Persons already in the array
    int countID; // internal ID counter that is incremented whenever a person is added


    // Additional private functions

    /**
     * @brief adds a person to the people in the taskManager.
     * @param name - name of Person to be added.
     * @throw runtime_error - if adding person failed (no space left).
     */
    void addPerson (const string& name);

    /**
     * Finds index of person in the array persons
     * @param name name of person to find
     * @return index of person if found. If not returns MAX_PERSONS
     */
    int findPerson (const string& name) const;

    /**
     * Check if task has the desired type.
     * @param task Task to check its type.
     * @param type Desired type, string form.
     * @return true if task is of type type
     */
    static bool isTaskType (const Task& task, const string& type);

    /**
     * Merges all tasks lists of every person into a single list.
     * List is sorted chronologically by person and by priority ranking.
     * @param typeFilter (optional) filter to apply so that only elements with the specific type will be in the list.
     * @return a sortedList if type Task with all the tasks.
     */
    SortedList<Task> merge (const string& typeFilter = "no_filter") const;


public:
    /**
     * @brief Default constructor to create a TaskManager object.
     *
     * Note - you may add =default if needed.
     */
    TaskManager();

    /**
     * @brief Deleted copy constructor to prevent copying of TaskManager objects.
     */
    TaskManager(const TaskManager &other) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent assignment of TaskManager objects.
     */
    TaskManager &operator=(const TaskManager &other) = delete;

    /**
     * @brief Assigns a task to a person.
     *
     * @param personName The name of the person to whom the task will be assigned.
     * @param task The task to be assigned.
     */
    void assignTask(const string &personName, const Task &task);

    /**
     * @brief Completes the highest priority task assigned to a person.
     *
     * @param personName The name of the person who will complete the task.
     */
    void completeTask(const string &personName);

    /**
     * @brief Bumps the priority of all tasks of a specific type.
     *
     * @param type The type of tasks whose priority will be bumped.
     * @param priority The amount by which the priority will be increased.
     */
    void bumpPriorityByType(TaskType type, int priority);

    /**
     * @brief Prints all employees and their tasks.
     */
    void printAllEmployees() const;

    /**
     * @brief Prints all tasks of a specific type.
     *
     * @param type The type of tasks to be printed.
     */
    void printTasksByType(TaskType type) const;

    /**
     * @brief Prints all tasks assigned to all employees.
     */
    void printAllTasks() const;
};
