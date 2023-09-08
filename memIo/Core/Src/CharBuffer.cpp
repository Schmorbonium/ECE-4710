#include "charBuffer.hpp"

CharBuffer::CharBuffer() : size(0), head(nullptr), headIndex(0), tail(nullptr), tailIndex(0) {}

CharBuffer::~CharBuffer()
{
    clear();
}

// Add a character to the end of the buffer
void CharBuffer::append(uint8_t c)
{
    __disable_irq();
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
    __enable_irq();
}

// Remove and return the first character in the buffer
uint8_t CharBuffer::pop()
{
    __disable_irq();
    if (size == 0)
    {
        // throw std::out_of_range("Buffer is empty");
    }

    char value = head->data[headIndex];
    headIndex++;
    size--;
    if (headIndex == NODE_SIZE)
    {
        Node *temp = head;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        delete temp;
        headIndex = 0;
    }
    __enable_irq();
    return value;
}
// Peaks at a value at given index. Warning! This i O(index)
uint8_t CharBuffer::peak(uint16_t index) const
{
    if (index + 1 > size)
    {
    }
    uint16_t relIndex = index + headIndex;
    Node *curNode = head;
    while (relIndex >= NODE_SIZE)
    {
        curNode = curNode->next;
        relIndex -= NODE_SIZE;
    }
    return curNode->data[relIndex];
}
// Get the current size of the buffer
uint16_t CharBuffer::getSize() const
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
    __disable_irq();
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
    __enable_irq();
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
        }
        currentIndex = 0;
        current = current->next;
    }
}