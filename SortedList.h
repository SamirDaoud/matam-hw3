#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template<typename T>
    /**
     * Generic simple linked list.
     * @tparam T generic object - type of object to store in LinkedList.
     */
    struct Node {
        //struct: public by default

        T data; // data stored in the list
        Node *next; // pointer to the next node

        Node() : next(nullptr) {}

        //parametrized constructor
        explicit Node(const T &data, Node *next_ptr = nullptr) : data(data), next(next_ptr) {}

        //constructor that accepts data
        //next is nullptr
        Node(const Node &other) : data(other.data), next(nullptr) {}

        //assignment and destructor used are the default ones.

    };

    // SORTED LIST
    //Head is the largest
    template<typename T>
    class SortedList {
        //head of the list and its tail.
        Node<T> *head;
        //Node<T> *tail;
        int size;

        /**
         * gets a pointer to the last node (before nullptr)
         * the last node is the smallest in terms of the value we are sorting by
         * @return node pointer to the last node in the list
         */
        [[maybe_unused]] Node<T> *tail() {
            Node<T> current = head;
            while (current.next) {
                current = current.next;
            }

            return current;
        }

        void deleteNodes() {
            if (!head) return; // Avoid double deletion
            Node<T> *temp = head;
            Node<T> *temp2 = temp;
            while (temp) {
                temp2 = temp;
                temp = temp->next;
                delete temp2;
            }
            delete temp;
            head = nullptr;
            this->size = 0;
        }

    public:
        //returns length of list
        int length() const {
            return this->size;
        }

        //c`tors & d`tors:

        static const int ZERO = 0;


        //copy constructor
        SortedList(const SortedList<T> &otherList) : head(nullptr), size(ZERO) {

            //SortedList<T> copy;
            if (!otherList.head)
                return;

            try {
                head = new Node<T>(*(otherList.head)); // Node copy constructor called
                Node<T> *travT = head; //this traversak
                Node<T> *travO = otherList.head->next;
                size++;
                while (travO) {
                    travT->next = new Node<T>(*(travO));
                    travO = travO->next;
                    travT = travT->next;
                    size++;
                }
                //head = headNode;
                //Node<T> *temp = head;


            } catch (const std::bad_alloc &e) {
                deleteNodes();
                throw;
            }

        }

        //default constructor
        SortedList() : head(nullptr), size(0) {}

        //default
        ~SortedList() {
            deleteNodes();
        }

        /**
         * insert a new node to list
         * @param value
         */
        void insert(const T &value) {
            //Node<T>* newNode = nullptr;
            //try {

            if (!head) {
                head = new Node<T>(value);
                size++;
                return;
            }

            Node<T> *newNode = new Node<T>(value);


            if (value > head->data) {
                newNode->next = head;
                head = newNode;
                size++;
                return;
            }
            Node<T> *traversal = head;
            /* if(value>traversal->data){

             }*/
            while (traversal->next != nullptr && traversal->next->data > value) {
                //for Task object this uses the > operator that is overloaded
                traversal = traversal->next;
            }

            newNode->next = traversal->next;
            traversal->next = newNode;
            size++;

        }

        /**
         * Assignment operator for SortedList.
         * @param other SortedList to copy into the caller.
         * @return pointer *this to caller.
         */
        SortedList<T> &operator=(const SortedList<T> &other) {

            if (this == &other) {
                return *this;
            }

            // use a temporary list so that it can be deleted safely in case of exception
            SortedList<T> temp; //default constructor call

            try {

                Node<T> *traversal = other.head;
                while (traversal) {
                    temp.insert(traversal->data);
                    traversal = traversal->next;
                }
                //if other is an empty list then temp will also be an empty list - it will not enter while
            } catch (...) {
                // Cleanup of `temp` happens automatically when it goes out of scope
                throw; // Rethrow the exception
            }

            // manually swap this and other's fields
            Node<T> *headTemp = head;
            head = temp.head;
            temp.head = headTemp;

            int sizeTemp = size;
            size = temp.size;
            temp.size = sizeTemp;

            return *this; //deletes temp and with it the original "this" object
        }


        /** ConstIterator
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. a ctor(or ctors) your implementation needs
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~ConstIterator() - destructor
         *
         * operators:
         * 5. operator* - returns the element the iterator points to
         * 6. operator++ - advances the iterator to the next element
         * 7. operator!= - returns true if the iterator points to a different element
         *
         */

        class ConstIterator {
        public:
            const Node<T> *current; // Pointer to the current node

            ConstIterator() : current(nullptr) {}

            explicit ConstIterator(const Node<T> *node) : current(node) {}

            // Dereference operator
            const T &operator*() const {
                return current->data;
            }

            // Pre-increment operator
            ConstIterator &operator++() {
                if (!current) { //if current i
                    throw std::out_of_range("Iterator out of bounds");
                }
                current = current->next;
                return *this;
            }

            // Inequality operator
            bool operator!=(const ConstIterator &other) const {
                return current != other.current;
            }
        };

// begin() and end() methods
        ConstIterator begin() const {
            return ConstIterator(head);
        }

        ConstIterator end() const {
            return ConstIterator(nullptr);
        }

/**
 * removes the node the itr iterator points to.
 * @param itr iterator to delete
 */
        void remove(const ConstIterator &itr) {
            if (!itr.current || !head) return;

            if (itr.current == head) {
                Node<T> *temp = head;
                head = head->next;
                delete temp;
                size--;
                return;
            }

            Node<T> *prev = head;
            while (prev->next && prev->next != itr.current) {
                prev = prev->next;
            }

            if (!prev->next) return; // Node not found

            Node<T> *temp = prev->next;
            prev->next = temp->next;

            delete temp;

            size--;
        }

/**
 * return size of list
 * @return
 */
        int length() {
            return size;
        }


/**
 * filter class, accepts a condition to filter by. condition can be a function
 */
        template<class Condition>
/**
 * filters the list according to a certain given condition
 * @tparam Condition condition generic class that has a condition
 * @param condition condition to filter by
 * @return
 */
        SortedList filter(Condition condition) const {
            SortedList filteredList;
            Node<T> *traversal = head;

            while (traversal) {
                if (condition(traversal->data)) {

                    filteredList.insert(traversal->data);
                }
                traversal = traversal->next;
            }
            return filteredList;
        }

/**
 * Operation template accepts an operation object - function, boolean expression...
 * makes a new SortedList with operation applied on all the nodes in the list
 * @tparam Operation operation generic class
 * @param op operation to apply to nodes
 * @return SortedList with the modified nodes according to the operation
 */
        template<class Operation>
        SortedList apply(Operation op) const {

            SortedList moddedCopy; //return this
            Node<T> *traversal = head;

            while (traversal) {
                moddedCopy.insert(op(traversal->data));
                traversal = traversal->next;
            }
            return moddedCopy;
        }


    };
}