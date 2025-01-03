#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList
    {

      struct Node {
            T data;
            Node *next;
                Node(const T &data) : data(data), next(nullptr) {}
            };
            Node *head;
            int list_size;
    public:
        //defalut constructor
        SortedList();
        //paramitrizied constructor
        SortedList(const SortedList &other);
        // assignment operator
        SortedList& operator=(const SortedList &other);
        //adding new element
        void insert(const Node &other);
        //destructor
        ~SortedList();
        //remove element
       // void remove(ConstIterator it);
       int length() const;
        template<typename Predicate>
        SortedList filter(Predicate condition) const{};
        template<typename Operation>
        SortedList apply(Operation operation) const{};
        ConstIterator begin()const{};
        ConstIterator end()const{};

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
/* */