#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template <typename T>
    struct Node {
    public:
        T data;
        Node<T>* next;
        Node() : next(nullptr) {}
        explicit Node(const T data, Node<T> *ptr = nullptr) : data(data), next(ptr) {}

        //copy constructor - recursive
        Node (const Node& other) : data(other.data), next(nullptr) {
            if (other.next) { //if other.next is null stop
                next = new Node(*other.next); // Recursively copy the next node
            }
        }

        Node& operator= (Node const &other) {

            if (this == &other) return *this;

            data = other.data;
            Node* temp = next;
            delete temp;
            next = other.next;
            if (next) {
                next = Node(other.next); //copy constructor called
            }
        }


    };

    // SORTED LIST
    //Head is the largest
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

        //copy constructor
        SortedList(SortedList<T> const &otherList) {
            /*
            SortedList<T> copy = new SortedList<T> ();
            if (!otherList.head) return copy;
            Node<T> *traversalO = otherList;
            Node<T> *traversalC = copy;

            while (traversalO) {
                traversalC = new Node(*traversalO);
            }
             */

            //copy constructor called

            Node<T> headNode = otherList.head ? new Node<T> (otherList.head): nullptr;

            head = headNode;
            Node<T>* temp = head;

            while (temp->next) { //reach the one bfr nullptr
                temp = temp->next;
            }
            tail = temp;

            temp = nullptr;
            delete temp;
        }

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