#include "stm32f1xx_hal.h"
class CharBuffer {
private:
    static const size_t NODE_SIZE = 16;
    struct Node {
        uint8_t data[NODE_SIZE];
        Node* next;
        Node() : next(nullptr) {
            // std::memset(data, 0, NODE_SIZE);
        }
    };
    size_t size;

    Node* head;
    size_t headIndex;
    Node* tail;
    size_t tailIndex;

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
    size_t getSize() const;

    // Check if the buffer is empty
    bool isEmpty() const;

    // Clear the buffer and release memory
    void clear();

    // Print the contents of the buffer
    void print() const;
};