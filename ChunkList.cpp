# include <iostream>

template<class T>
ChunkList<T>::ChunkList()
{
    head = nullptr;
    tail = nullptr;

    iterNode = head;
    arrPos = 0;

    listLen = 0;
    numChunks = 0;
}

template<class T>
ChunkList<T>::ChunkList(T arr[], int arrLen)
{
    if(arrLen < 0)
    {
        throw InvalidArrayLength();
    }

    listLen = 0;
    numChunks = 0;

    for(int i = 0; i < arrLen; i++)
    {
        Append(arr[i]);
    }

    iterNode = head;
    arrPos = 0;
}

template<class T>
ChunkList<T>::~ChunkList()
{
    Node* curr = head;

    while(curr != nullptr)
    {
        Remove(curr->values[curr->len - 1]);

        curr = curr->next;
    }
}

template<class T>
void ChunkList<T>::Append(T value)
{
    // if the current list is empty or the tail node is full
    if(IsEmpty() || tail->len >= ARRAY_SIZE)
    {
        // make a new node and insert the value at index 0
        Node* temp = new Node();
        temp->next = nullptr;
        temp->len = 0;
        temp->values[temp->len++] = value;

        // update either head or tail, depending on whether the list was empty or full
        if(IsEmpty())
        {
            head = temp;
        }
        else
        {
            tail->next = temp;
        }

        // regardless, the tail pointer will end up pointing to the newly made node
        tail = temp;

        listLen++;
        numChunks++;
    }
    // otherwise, just add the value to the end of the array and increment listLen
    else
    {
        tail->values[tail->len++] = value;
        listLen++;
    }
}

template<class T>
void ChunkList<T>::Remove(T value)
{
    if(IsEmpty())
    {
        throw EmptyList();
    }

    Node* curr = head;
    Node* prev = curr;
    while(curr != nullptr)
    {
        // look through the array on the current node
        for(int i = 0; i < curr->len; i++)
        {
            // if the value is found
            if(curr->values[i] == value)
            {
                curr->len--;
                listLen--;

                // if the current node would be empty after removing the value
                if(curr->len == 0)
                {
                    // if the entire list would be empty after removing the value
                    if(!IsEmpty())
                    {
                        if(curr == head)
                        {
                            head = head->next;
                        }
                        else if(curr == tail)
                        {
                            tail = prev;
                        }
                        else
                        {
                            prev->next = curr->next;
                        }
                    }
                    else
                    {
                        head = nullptr;
                        tail = nullptr;
                    }

                    delete curr;
                    numChunks--;
                }
                // otherwise, go through the "normal" procedure
                else
                {
                    // start from i, the index stopped at when the value was found, go through the rest of the array and
                    // shift everything over by 1, this will overwrite the value
                    for(int j = i; j < curr->len; j++)
                    {
                        curr->values[j] = curr->values[j + 1];
                    }
                }

                // after finding the value and doing what's needed, stop searching and get out
                return;
            }
        }

        prev = curr;
        curr = curr->next;
    }
}

template<class T>
int ChunkList<T>::GetLength()
{
    return listLen;
}

template<class T>
double ChunkList<T>::LoadFactor()
{
    if(IsEmpty())
    {
        throw EmptyList();
    }

    return (double)listLen / (double)(numChunks * ARRAY_SIZE);
}

template<class T>
bool ChunkList<T>::Contains(T value)
{
    if(IsEmpty())
    {
        throw EmptyList();
    }

    // go through every element of every array of every node to find the value
    Node* temp = head;
    while(temp != nullptr)
    {
        for(int i = 0; i < temp->len; i++)
        {
            if(temp->values[i] == value)
            {
                return true;
            }
        }

        temp = temp->next;
    }

    return false;
}

template<class T>
T ChunkList<T>::GetIndex(int i)
{
    if(IsEmpty())
    {
        throw EmptyList();
    }
    if(i < 0 || i >= listLen)
    {
        throw IndexOutOfBounds();
    }

    Node* temp = head;
    while(temp != nullptr)
    {
        // if the local index is within the current array, return the value
        if(i < temp->len)
        {
            break;
        }

        // translates i, the overall index, to the local index of the current array
        i -= temp->len;
        temp = temp->next;
    }

    return temp->values[i];
}

template<class T>
void ChunkList<T>::ResetIterator()
{
    iterNode = head;
    arrPos = 0;
}

template<class T>
T ChunkList<T>::GetNextItem()
{
    if(arrPos >= listLen)
    {
        throw IteratorOutOfBounds();
    }

    // this is arrPos translated into the index of the current array
    int localIndex = arrPos;

    // excise the length of every chunk until iterNode is hit, this is the translation
    Node* curr = head;
    while(curr != iterNode)
    {
        localIndex -= curr->len;
        curr = curr->next;
    }

    // if at the end of the array, move on to the next node at index 0
    if(localIndex >= curr->len)
    {
        localIndex = 0;
        iterNode = iterNode->next;
        curr = iterNode;
    }

    arrPos++;
    return iterNode->values[localIndex];
}

template<class T>
bool ChunkList<T>::IsEmpty()
{
    return listLen == 0;
}

#include "ChunkList.h"