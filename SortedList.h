#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    template<typename T>
    struct Node {
    public:
        T data;
        Node *next;

        Node() : next(nullptr) {}

        //parametrized constructor
        explicit Node(const T& data, Node *next_ptr = nullptr) : data(data), next(next_ptr) {}

        //copy constructor - recursive
        Node(const Node &other) : data(other.data), next(nullptr) {
            /*
            try {
                if (other.next) { //if other.next is null stop
                    next = new Node(*other.next); // Recursively copy the next node
                }
            } catch (std::bad_alloc) {
                //delete next;
                //delete this;
                throw;
            }
             */

        }


        /*
         * no need for assignment operator here
        Node &operator=(Node const &other) {

            if (this == &other) return *this;

            data = other.data;
            Node *temp = next;
            if (next) {
                delete temp;
            }
            next = other.next;
            if (next) {
                next = Node(other.next); //copy constructor called
            }
        }
         */


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
        [[maybe_unused]] Node<T>* tail () {
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

        //copy constructor
        SortedList(SortedList<T> const &otherList) : head(nullptr), size (0) {

            //SortedList<T> copy;
            if (!otherList.head) return;

            try {
                head = new Node<T>(*(otherList.head)); // Node copy constructor called
                Node<T>* travT = head; //this traversak
                Node<T>* travO = otherList.head;
                size++;
                while (travO->next) {
                    travT->next = new Node<T> (*(travO->next));
                    travO = travO->next;
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
        SortedList() : head(nullptr), size(0) { }

        //default
        ~SortedList() {
            deleteNodes();
        }

        /**
         * insert a new node to list
         * @param value
         */
        void insert(const T &value) {
            Node<T>* newNode = nullptr;
            try {
                newNode = new Node<T>(value);

                if (!head) {
                    head = newNode;
                    size++;
                    return;
                }

                Node<T>* traversal = head;

                while (traversal->next != nullptr && traversal->next->data > value) {
                    //for Task object this uses the > operator that is overloaded
                    traversal = traversal->next;
                }

                newNode->next = traversal->next;
                traversal->next = newNode;
                size++;

            }  catch (const std::bad_alloc& e) {
                    delete newNode;
                    throw;
            }


        }

        //assignment operator for SortedList
        SortedList<T>& operator= (const SortedList<T> &other) {

            if (this == &other) {
                return *this;
            }

            //delete this list's nodes to make room for new ones
            deleteNodes();

            //in case of empty list
            if (!&other) {
                head = nullptr;
                //tail = nullptr;
                size = 0;
                return *this;
            }

            //not empty - fill this list with other list's stuff
            try { //to get error thrown from insert
                Node<T>* traversal = other.head;

                while (traversal) {
                    insert(traversal->data);
                    traversal = traversal->next;
                }

                return *this;
            } catch (...) {
                deleteNodes();
            }

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
            if (!itr.current || !head) return;

            if (itr.current == head) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                size--;
                return;
            }

            Node<T>* prev = head;
            while (prev->next && prev->next != itr.current) {
                prev = prev->next;
            }

            if (!prev->next) return; // Node not found

            Node<T>* temp = prev->next;
            prev->next = temp->next;

            delete temp;

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