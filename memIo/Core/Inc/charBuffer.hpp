#include "stm32f1xx_hal.h"
class CharBuffer {
private:
    static const uint16_t NODE_SIZE = 16;
    struct Node {
        uint8_t data[NODE_SIZE];
        Node* next;
    };
    uint16_t size;
    Node* head;
    uint16_t headIndex;
    Node* tail;
    uint16_t tailIndex;

public:
    CharBuffer();
    ~CharBuffer();

    // Append a new Character to the end of the buffer 
    void append(uint8_t c);

    // Remove and return the first character in the buffer
    uint8_t pop();

    // Peaks at the value at a given index
    uint8_t peak(uint16_t) const;

    // Get the current size of the buffer
    uint16_t getSize() const;

    // Check if the buffer is empty
    bool isEmpty() const;

    // Clear the buffer and release memory
    void clear();

    // Print the contents of the buffer
    void print() const;
};