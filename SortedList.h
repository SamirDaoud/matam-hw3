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
        explicit Node(const T data, Node<T> *next_ptr = nullptr) : data(data), next(next_ptr) {}

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


            try {
                Node<T> headNode = otherList.head ? new Node<T> (otherList.head): nullptr; //copy constructor called

                head = headNode;
                Node<T>* temp = head;

                while (temp->next) { //reach the one bfr nullptr
                    temp = temp->next;
                }
                tail = temp;

                temp = nullptr;
                delete temp;
            } catch (const std::bad_alloc& e) {
                deleteNodes();
                throw;
            }

        }

        //default constructor
        SortedList() {
            head = nullptr;
            size = 0;
        }

        //default
        ~SortedList() {
            deleteNodes();
        }

        //insert
        void insert (const T& value) {
            Node<T> newNode  = new Node<T> (value);
            Node<T>* traversal = head;

            while (traversal->next != nullptr && traversal->next->data > value) {
                //for Task object this uses the > operator that is overloaded
                traversal = traversal->next;
            }

            newNode.next = traversal->next;
            traversal->next = newNode;
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

        class ConstIterator {
            const Node<T>* current;
        public:
            friend SortedList<T>;
            ConstIterator() = default;
            explicit ConstIterator(Node<T>* current): current(current){}
            // Overload for the comparison operator !=
            bool operator!=(const ConstIterator& itr) const {
                return current != itr.current;
            }

            // Overload for the dereference operator *
            const T& operator*() const {
                return current->data;
            }

            // Overload for the postincrement operator ++
            ConstIterator& operator++() {
                if (!current) {
                    throw  std::out_of_range("iterating out of bounds");
                }
                current = current->next;
                return *this;
            }
        };
        ConstIterator begin() const{
            return SortedList::ConstIterator(head);
        }
        ConstIterator end() const{
            return ConstIterator(nullptr);
        }
    };
}