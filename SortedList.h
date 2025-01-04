#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template <typename T>
    struct Node {
    public:
        const T data;
        Node<T>* next;
        Node() : next(nullptr) {}
        explicit Node(const T data, Node<T> *ptr = nullptr) : data(data), next(ptr) {}

        //copy constructor - recursive
        Node (const Node& other) : data(other.data), next(nullptr) {
            if (other.next) { //if other.next is null stop
                next = new Node(*other.next); // Recursively copy the next node
            }
        }

        Node& operator= (Node const &other) = delete;

    };

    template <typename T>
    class SortedList {
        //head of the list and its tail.
        Node<T>* head;
        Node<T>* tail;
        int size;
        void deleteNodes()
        {
            Node<T>* temp = head;
            Node<T>* temp2 = temp;
            while (temp)
            {
                temp2 = temp;
                temp = temp->next;
                delete temp2;
            }
            delete temp;
            head = nullptr;
            this->size=0;
        }

    public:
        //returns length of list
        int length() const {
            return this->size;
        }

        //c`tors & d`tors:

        //default
        SortedList() {
            head = nullptr;
            size = 0;
        }

        //default
        ~SortedList() {
            deleteNodes();
        }

    };

    template <class T>
    class SortedList<T>::ConstIterator {
        /**
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
    };
}