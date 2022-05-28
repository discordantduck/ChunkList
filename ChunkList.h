//
// Created by Varick Erickson 2/3/2021.
//

#ifndef CHUNKLIST_CHUNKLIST_H
#define CHUNKLIST_CHUNKLIST_H

#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

// These error classes are done. No modifications are required.
// See ChunkList_demo.cpp for an example of how they are used.
class InvalidArrayLength{
public:
    string Msg() {
        return "Invalid array length used for constructor.";
    }
};

class IndexOutOfBounds {
public:
    string Msg() {
        return "Index is out of bounds";
    }
};

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

class EmptyList {
public:
    string Msg() {
        return "List is empty";
    }
};

// Put your pre/post conditions here.

template<class T>
class ChunkList {
public:
    // Constructors
    // function: default constructor
    // pre: none
    // post: sets head and tail to nullptr, iterNode will point to head, arrPos to 0, and listLen as well as numChunks
    //       to 0
    ChunkList();
    // function: normal constructor
    // pre: the given array length is non negative
    // post: a list of arrLen size is generated using append, iterNode is set to head and arrPos to 0
    ChunkList(T arr[], int arrLen);

    // Deconstructor
    // function: delete the list
    // pre: none
    // post: the entire list is deleted using Remove()
    ~ChunkList();

    // Add/remove elements
    // function: appends the given value to the end of the list
    // pre: none
    // post: listLen will be incremented, and numChunks will also be if the tail is full and a new node needs to be
    //       made, also, the pointers will be reallocated
    void Append(T value);
    // function: removes the first instance of the given value
    // pre: the list isn't empty
    // post: if the value is found, if it's the last item in a node, delete the node, reallocate the pointers and
    //       decrement numChunks, otherwise, shift all the values in the array by 1 to overwrite the value
    void Remove(T value);

    // Stuff to find out about the ChunkList
    // function: gets the length of the list
    // pre: none
    // post: returns listLen
    int GetLength();
    // function: gets the percentage of the list that's occupied
    // pre: the list isn't empty
    // post: returns the number of occupied space over the total number of spaces in the list as a double
    double LoadFactor();
    // function: checks if the given value is in the list
    // pre: the list isn't empty
    // post: returns true if the value is in the list, false otherwise
    bool Contains(T value);

    // Accessing elements
    // function: get the value at the given index
    // pre: the list isn't empty and the given index isn't out of bounds
    // post: returns the value at the given index, if
    T GetIndex(int i);
    // function: resets all iterators
    // pre: none
    // post: iterNode is set to head and arrPos is set to 0
    void ResetIterator();
    // function: gets the value at the current index
    // pre: there are still items left in the list
    // post: returns the value at the current arrPos, increment arrPos and move iterNode to the next node if reached the
    //       end of the array
    T GetNextItem();

    // function: tells the user if the list is empty
    // pre: none
    // post: returns true if the list is empty, false otherwise
    bool IsEmpty();
private:

    // Note we did not need to make this a template
    // since this struct is part of a template class.
    struct Node {
        Node* next;
        int len;
        T values[ARRAY_SIZE];
    };

    Node* head;
    Node* tail;

    // iterator
    Node* iterNode;     // What node are were currently on?
    int arrPos;         // Within the node, what element are we looking at?

    int listLen;        // Total elements
    int numChunks;      // Total chunks/nodes
};

#include "ChunkList.cpp"

#endif //CHUNKLIST_CHUNKLIST_H
