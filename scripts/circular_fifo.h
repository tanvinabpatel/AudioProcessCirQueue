#ifndef CIRCULAR_FIFO_H
#define CIRCULAR_FIFO_H

#include <iostream>
#include <stdexcept>
#include "audio_buffer.h"

template <typename T>
class CircularFIFO {
private:
    T *buffer;          // Pointer to array of samples
    int head;           // Index of the head (front to read) of the queue
    int tail;           // Index of the tail (rear to write) of the queue
    int capacity;       // Capacity of the queue

public:

    //Constructor Code
    CircularFIFO(int capacity) : capacity(capacity + 1), head(0), tail(0) {
        buffer = new T[this->capacity];                 // Allocate memory
        if (!buffer) {
            throw std::bad_alloc();                     // Handle allocation failure
        }
    }

    // Get methods
    int getHead() const { return head; }

    int getTail() const { return tail; }

    int getCapacity() const { return capacity; }

    // Check if the queue is empty
    bool isEmpty() const {
        return head == tail;                            // If head and tail are the same, the queue is empty
    }

    // Check if the queue is full
    bool isFull() const {
        return (tail + 1) % capacity == head;           // If moving tail ahead hits the head, the queue is full
    }

    // Write an element to the queue
    bool writeElement(T element) {
        if (isFull()) {
            std::cout << "Error: Cannot write to full buffer!" << std::endl; // Print error message       
            return false;                                // Return false to indicate the operation failed
        }
        buffer[tail] = element;                         // Write the element at the tail
        tail = (tail + 1) % capacity;                   // Update the tail value (move next)
        return true;                                    // Return true to indicate success
    }

    // Read an element from the queue
    T readElement() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty. Cannot read element");
        }
        T element = buffer[head];                       // Read the element at the head
        head = (head + 1) % capacity;                   // Move the head forward
        return element;        
    }

    // Print buffer elements
    void printBufferElements() const {
        if (isEmpty()) {
            std::cout << "Queue is empty." << std::endl;
            return;
        }

        std::cout << "Printing buffer elements: head = " << getHead() 
                  << ", tail = " << getTail() << ", capacity = " << getCapacity() << std::endl;
        
        // Access the AudioBuffer pointer
        int current = head;
        while (current != tail) {
            T abPtr = buffer[current];                  // abPtr is a pointer to AudioBuffer
            if (abPtr) {                                // Check if abPtr is not null
                std::cout << "AudioBuffer at location " << current 
                          << " is " << abPtr << ", sample count: " 
                          << abPtr->sample_count << std::endl;
                abPtr->printSamples();                  // Print samples using the reference
            } else {
                std::cout << "AudioBuffer at location " << current << " is nullptr." << std::endl;
            }
            current = (current + 1) % capacity;         // Move to the next index
        }
        std::cout << std::endl; 
    }

    // Destructor
    ~CircularFIFO() {
        delete[] buffer;                                // Free the allocated memory for the buffer
    }

};

#endif // CIRCULAR_FIFO_H