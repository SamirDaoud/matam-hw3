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
        explicit Node(const T data, Node<T> *ptr = nullptr) :
                data(data), next(ptr) {}
    };
        template <typename T>
        class SortedList {
            //head of the list and its tail.
            Node<T>* head;
            Node<T>* tail;
            int size;
            void deleteNodes()
            {
                Node<T>* temp=head;
                while (temp)
                {
                    Node<T>* temp2= temp;
                    temp = temp->next;
                    delete temp2;
                }

                this->size=0;
            };

    public:


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