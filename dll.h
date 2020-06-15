#ifndef __DLL_H__
#define __DLL_H__

#include "exceptions.h"
#include <iostream>

using namespace std;

template <typename T>
class DllNode {
public:
    T value;
    DllNode *prev;
    DllNode *next;
    DllNode(T data); // constructor
    DllNode(); //default constructor
};

// non default const.
template <typename T>
DllNode<T>::DllNode(T data) {
    this->value = data;
    this->prev = nullptr;
    this->next = nullptr;
}

// default const
template <typename T>
DllNode<T>::DllNode() {
    this->value = nullptr;
    this->prev = nullptr;
    this->next = nullptr;
}

template <typename T>
class Dll {
private:
    DllNode<T> *head;
    int listSize;
    DllNode<T> *tail;
public:
    Dll(); // creates an empty list   
    Dll(const Dll &src);// creates a deep copy of the src list   
    Dll(const T arr[], int size); // create a linked list containing the elements of the array     
    Dll &operator=(const Dll &src);// create a deep copy of the src list    
    ~Dll();// free all memory    
    bool empty() const; // return if the list is empty in O(1)    
    int size() const;// return how many items are in the list in O(1)    
    T &at(int rank) const;// return a reference to the value of the list at a rank/index    
    void insert(int rank, T value);// insert a value at the rank/index   
    T remove(int rank); // remove the node at the rank/index and return its value
    void clear(); // reset the list to an empty list
    void display(ostream &os) const{ // write the contents of the list to the ostream
    os << "[ ";
    DllNode<T> *curr = head;
    for (int i = 0; i < listSize; i++) { // output all elements
        os << curr->value << " ";
        curr = curr->next;
    }
    os << "]";
    }
};

template <typename T>
Dll<T>::Dll() { // create an empty list
    this->head = nullptr;
    this->tail = head;
    this->listSize = 0;
}

template <typename T>
Dll<T>::Dll(const Dll &src) { // create a deep copy of src 
    this->head = nullptr;
    this->tail = head;
    for (int i = 0; i < src.listSize; i++) { // must add elements one by one as to not change orig. list
        insert(i, src.at(i));
    }
}

template <typename T>
Dll<T>::Dll(const T arr[], int size) { // create a dll from an array
    this->head = nullptr;
    this->tail = head;
    for (int i = 0; i < size; i++) {
        insert(i, arr[i]); // insert elements by array value
    }
}

template <typename T>
Dll<T>& Dll<T>::operator=(const Dll<T> &src) { // create a deep copy by using deep copy method, return reference
    Dll *a = new Dll<T>(src);
    return *a;
}

template <typename T>
Dll<T>::~Dll() { // deconstructor, call clear
    clear();
}

template <typename T>
bool Dll<T>::empty() const { // is empty function
    if (head == nullptr) return true;

    return false;
}

template <typename T>
int Dll<T>::size() const {
    return this->listSize;
}

template <typename T>
T& Dll<T>::at(int rank) const{
    if (rank < 0 || rank >= listSize) { // if rank is out of bounds
        throw IndexOutOfRangeException("at(): Index was outside the bounds of the linked list.", rank);
    }
    DllNode<T> *curr = head;
    for (int i = 0; i < rank; i++) { // iterate through values until reach wanted index
        curr = curr->next;
    }
    return curr->value; // return target value
}

template <typename T>
void Dll<T>::insert(int rank, T value) { // insert a value at specified rank with specified value
    if (rank < 0 || rank > listSize) { // if rank does not exist and is not new tail
        throw IndexOutOfRangeException("insert(): Index was outside the bounds of the linked list.", rank);
    }
    if (rank == 0) { // insert at head
            if (head == nullptr) { // create new list with value
                head = new DllNode<T>(value);
                tail = head;
                listSize++;
            }
            else { // insert node at beginning of list
                DllNode<T> *curr = new DllNode<T>(value);
                curr->next = head; // must rearrange nodes
                curr->prev = nullptr;
                head->prev = curr;
                head = curr;
                listSize++;
            }
        }
        else if (rank == listSize) { // insert at tail
            DllNode<T> *insert = new DllNode<T>(value);
            insert->prev = tail; // must rearrange nodes
            tail->next = insert; 
            tail = insert;
            listSize++;
        }
        else { // insert between
            DllNode<T> *curr = head;
            DllNode<T> *insert = new DllNode<T>(value);
            for (int i=0; i < rank; i++) { // iterate to reach right spot
                curr = curr->next;
            }
            curr->prev->next = insert;
            insert->next = curr;
            insert->prev = curr->prev;
            curr->prev = insert;
            listSize++;
        }
}

template <typename T>
T Dll<T>::remove(int rank) { // function to remove from a rank
    if (rank < 0 || rank >= listSize) { // rank does not exist to remove
        throw IndexOutOfRangeException("remove(): Index was outside the bounds of the linked list.", rank);
    }
        DllNode<T> *curr = head;
        if (rank == 0) { // remove head
            head = head->next;
            T val = curr->value;
            delete curr;
            listSize--;
            return val;
        }
        if (rank == listSize-1) { // remove tail
            curr = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            T val = curr->value;
            delete curr;
            listSize--;
            return val;
        }
        // else, remove between
        for (int i = 0; i < rank; i++) {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        T value = curr->value;
        delete curr;
        listSize--;
        return value;
}



template<typename T>
void Dll<T>::clear() { // deallocate all memory for nodes
    DllNode<T> *curr = head;
    DllNode<T> *next;
    for (int i = 0; i < listSize; i++) {
        next = curr->next;
        delete curr;
        curr = next;
    }
    head = nullptr;
    tail = nullptr;
    this->listSize = 0;
}


template <typename T>
// write the contents of the list to the ostream
ostream &operator<<(ostream &os, const Dll<T> &list) {
    list.display(os);
    return os;
}

#endif
