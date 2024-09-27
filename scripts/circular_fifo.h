#ifndef CIRCULAR_FIFO_H
#define CIRCULAR_FIFO_H

#include <iostream>
#include <stdexcept>
#include "audio_buffer.h"

template <typename T>
class CircularFIFO {
private:
    T* buffer;          // Pointer to array of T pointers
    int head;           // Index of the head (front to read) of the queue
    int tail;           // Index of the tail (rear to write) of the queue
    int capacity;       // Capacity of the queue

public:
    CircularFIFO(int capacity) : capacity(capacity + 1), head(0), tail(0) {
        buffer = new T[this->capacity]; // Allocate memory
        if (!buffer) {
            throw std::bad_alloc(); // Handle allocation failure
        }
    }

    ~CircularFIFO() {
        delete[] buffer; // Free the allocated memory for the buffer
    }

    bool WriteElement(T element) {
        if (isFull()) {
            std::cout << "Error: Cannot write to full buffer!" << std::endl; // Print error message       
            return false;                                // Return false to indicate the operation failed
        }
        buffer[tail] = element;                         // Write the element at the tail
        tail = (tail + 1) % capacity;                   // Update the tail value (move next)
        return true;                                    // Return true to indicate success
    }

    T ReadElement() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty. Cannot read element");
        }
        T element = buffer[head];                       // Read the element at the head
        head = (head + 1) % capacity;                   // Move the head forward
        return element;        
    }

    bool isEmpty() const {
        return head == tail;                            // If head and tail are the same, the queue is empty
    }

    bool isFull() const {
        return (tail + 1) % capacity == head;           // If moving tail ahead hits the head, the queue is full
    }

    void printBufferElements() const {
        if (isEmpty()) {
            std::cout << "Queue is empty." << std::endl;
            return;
        }

        int current = head;
        std::cout << "Printing buffer elements: head = " << head 
                  << ", tail = " << tail << ", capacity = " << capacity << std::endl;
        // Access the AudioBuffer pointer
        while (current != tail) {
            T ab = buffer[current]; 
            if (ab) {                                   // Check if ab is not null
                std::cout << "AudioBuffer at location " << current 
                          << " is " << ab << ", sample count: " 
                          << ab->sample_count << std::endl;
                ab->printSamples();                     // Print samples of the AudioBuffer
            } else {
                std::cout << "AudioBuffer at location " << current << " is nullptr." << std::endl;
            }
            current = (current + 1) % capacity;         // Move to the next index
        }
        std::cout << std::endl; 
    }

    int getHead() const { return head; }
    int getTail() const { return tail; }
    int getCapacity() const { return capacity; }
};

#endif // CIRCULAR_FIFO_H