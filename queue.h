#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "exceptions.h"
#include "dll.h"
#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    Dll<T> list;
public:
    Queue(); // create an empty stack
    void enqueue(T value); // add an item to the front of the queue
    T dequeue(); // remove the value at the front of the queue and return its value 
    T peek(); // return the value at the front of the queue, keeping it in the queue
    int size() const; // return how many items are in the queue
    bool empty() const; // return if the queue is empty
    void display(ostream &os) const; // write the contents of the queue to the ostream
};

template<typename T>
Queue<T>::Queue() {
    list = Dll<T>();
}

template<typename T>
void Queue<T>::enqueue(T value) {
    list.insert(list.size(), value); // insert at rear so prints in order
}

template<typename T>
T Queue<T>::dequeue() {
    if (list.empty() == true) {
        throw InvalidOperationException("Queue empty.");
    }
    return list.remove(0); // remove "first in" value
}

template <typename T>
T Queue<T>::peek() {
    if (list.empty() == true) {
        throw InvalidOperationException("Queue empty.");
    }
    return list.at(0); // return "first in " value
}

template <typename T>
int Queue<T>::size() const {
    return list.size();
}

template <typename T>
bool Queue<T>::empty() const {
    return list.empty();
}

template<typename T>
void Queue<T>::display(ostream &os) const {
    list.display(os);
}


template <typename T>
ostream &operator<<(ostream &os, const Queue<T> &queue) {
    queue.display(os);
    return os;
} // write the contents of the queue to the ostream

#endif
