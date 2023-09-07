#include <iostream>
#include <cstring>
#include "charBuffer.hpp"


CharBuffer::CharBuffer() : head(nullptr), tail(nullptr), size(0),headIndex(0), tailIndex(0) {}

CharBuffer::~CharBuffer()
{
    clear();
}

// Add a character to the end of the buffer
void CharBuffer::append(uint8_t c)
{
    tailIndex++;
    if (tail == nullptr || tailIndex == NODE_SIZE)
    {
        Node *newNode = new Node();
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        tailIndex = 0;
    }
    tail->data[tailIndex] = c;
    size++;
}

// Remove and return the first character in the buffer
uint8_t CharBuffer::pop()
{
    if (size == 0)
    {
        throw std::out_of_range("Buffer is empty");
    }

    char value = head->data[headIndex];
    headIndex++;
    size--; 
    if (headIndex == NODE_SIZE)
    {
        Node *temp = head;
        head = head->next;
        if(head == nullptr){
            tail = nullptr;
        }
        delete temp;
        headIndex = 0;
    }
    return value;
}
// Peaks at a value at given index. Warning! This i O(index)
uint8_t CharBuffer::peak(uint16_t index) const
{
    if(index+1 >  size){
        throw std::out_of_range("requested:Index out of range :(");
    }
    uint16_t relIndex = index+headIndex;
    Node* curNode = head;
    while(relIndex >= NODE_SIZE){
        curNode = curNode->next;
        relIndex -= NODE_SIZE;
    }
    return curNode->data[relIndex]
}
// Get the current size of the buffer
size_t CharBuffer::getSize() const
{
    return size;
}

// Check if the buffer is empty
bool CharBuffer::isEmpty() const
{
    return size == 0;
}

// Clear the buffer and release memory
void CharBuffer::clear()
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
    tailIndex = 0;
    headIndex = 0;
}

// Print the contents of the buffer
void CharBuffer::print() const
{
    Node *current = head;
    size_t currentIndex = 0;

    while (current != nullptr)
    {
        while (currentIndex < tailIndex)
        {
            std::cout << current->data[currentIndex++];
        }
        currentIndex = 0;
        current = current->next;
    }
    std::cout << std::endl;
}