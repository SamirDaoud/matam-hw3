#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template<typename T>
    struct Node {
    public:
        T data;
        Node<T> *next;

        Node() : next(nullptr) {}

        explicit Node(const T data, Node<T> *next_ptr = nullptr) : data(data), next(next_ptr) {}

        //copy constructor - recursive
        Node(const Node &other) : data(other.data), next(nullptr) {
            if (other.next) { //if other.next is null stop
                next = new Node(*other.next); // Recursively copy the next node
            }
        }

        Node &operator=(Node const &other) {

            if (this == &other) return *this;

            data = other.data;
            Node *temp = next;
            delete temp;
            next = other.next;
            if (next) {
                next = Node(other.next); //copy constructor called
            }
        }


    };

    // SORTED LIST
    //Head is the largest
    template<typename T>
    class SortedList {
        //head of the list and its tail.
        Node<T> *head;
        Node<T> *tail;
        int size;

        void deleteNodes() {
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

        //copy constructor
        SortedList(SortedList<T> const &otherList) {

            SortedList<T> copy;
            if (!otherList.head) return;
            /*
            Node<T> *traversalO = otherList.head;
            Node<T> *traversalC = copy.head;

            while (traversalO) {
                traversalC = new Node<T>(*traversalO);
            }
             */



            try {
                Node<T>* headNode = otherList.head ? new Node<T>(*(otherList.head)) : nullptr; //copy constructor called

                head = headNode;
                Node<T> *temp = head;

                while (temp->next) { //reach the one bfr nullptr
                    temp = temp->next;
                }
                tail = temp;

            } catch (const std::bad_alloc &e) {
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
        void insert(const T &value) {
            Node<T>* newNode = new Node<T>(value);
            Node<T>* traversal = head;

            while (traversal->next != nullptr && traversal->next->data > value) {
                //for Task object this uses the > operator that is overloaded
                traversal = traversal->next;
            }

            newNode->next = traversal->next;
            traversal->next = newNode;
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

// ConstIterator definition
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
            if (!itr.current) return; //nullptr
            if (!head) return; //empty list

            if (itr.current == head) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                return;
            }

            // traverse until we find the node preceding the desired one

            Node<T>* prev = head;

            while (prev->next && prev->next != itr.current) {
                prev = prev->next;
            }

            // delete
            Node<T>* temp = prev->next;
            prev->next = temp->next;

            delete temp;

            if (prev->next == nullptr) {
                tail = prev; // Update the tail if the last node is removed
            }

            size--;

        }

/**
 * retruns size of list
 * @return
 */
        int length () {
            return size;
        }


// filter class, accepts an operation
        template<class Condition>
/**
 * filters the list according to a certain given condition
 * @tparam Condition condition generic class that has a condition
 * @param condition condition to filter by
 * @return
 */
        SortedList filter(Condition condition) const {
            SortedList result;
            Node<T>* current = head;
            while(current){
                if (condition(current->data)) {
                    result.insert(current->data);
                }
                current = current->next;
            }
            return result;
        }

/**
 * makes a new SortedList with operation applied on all the nodes in the list
 * @tparam Operation operation generic class
 * @param op operation to apply to nodes
 * @return SortedList with the modified nodes according to the operation
 */
        template<class Operation>
        SortedList apply(Operation op) const {
            SortedList result;
            Node<T>* current = head;
            while(current) {
                result.insert(op(current->data));
                current = current->next;
            }
            return result;
        }



    };
}