#ifndef __STACK_H__
#define __STACK_H__

#include "exceptions.h"
#include "dll.h"
#include <iostream>
using namespace std;

template <typename T>
class Stack {
private: 
    Dll<T> list;
public:
    Stack(); // create an empty stack
    void push(T value);// add an item to the top of the stack
    T pop(); // remove of the value at the top of the stack and return its value
    T peek(); // return the value at the top of the stack, keeping it in the stack
    int size() const; // return how many items are in the stack
    bool empty() const; // return if the stack is empty
    void display(ostream &os) const; // write the contents of the stack to the ostream
};

template <typename T>
Stack<T>::Stack() {
    list = Dll<T>();
}

template <typename T>
void Stack<T>::push(T value) {
    list.insert(0, value); // insert at head so prints in order
}

template <typename T>
T Stack<T>::pop() {
    if (list.empty() == true) {
        throw InvalidOperationException("Stack empty.");
    }
    return list.remove(0); // remove "last in" element
}

template<typename T>
T Stack<T>::peek() {
    if (list.empty() == true) {
        throw InvalidOperationException("Stack empty.");
    }
    return list.at(0); // return "last in" element
}

template<typename T>
int Stack<T>::size() const {
    return list.size();
}

template <typename T>
bool Stack<T>::empty() const {
    return list.empty();
}

template <typename T>
void Stack<T>::display(ostream &os) const {
    list.display(os);
}


template <typename T>
ostream &operator<<(ostream &os, const Stack<T> &stack) {
    stack.display(os);
    return os;
} // write the contents of the stack to the ostream

#endif
