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
        CircularFIFO(int capacity);
        ~CircularFIFO();
        bool WriteElement(T element);
        T ReadElement();
        bool isEmpty() const;
        bool isFull() const;
        void printBufferElements() const;

    int getHead() const { return head; }
    int getTail() const { return tail; }
    int getCapacity() const { return capacity; }

};

// Define the construtor
template <typename T>
CircularFIFO<T>::CircularFIFO(int capacity) : capacity(capacity + 1), head(0), tail(0) { // Initialize all member variables
    buffer = new T[this->capacity]; // Allocate memory
    if (!buffer) {
        throw std::bad_alloc(); // Handle allocation failure
    }
}

// Free the buffer memory
template <typename T>
CircularFIFO<T>::~CircularFIFO(){
    delete[] buffer;                        // Free the allocted memory for the buffer
}

// Add an element to the Queue
template <typename T>
bool CircularFIFO<T>::WriteElement(T element){
    if (isFull()){
        //throw std::overflow_error("Queue is full and cannot write elements.");
        std::cout << "Error: Cannot write to full buffer!" << std::endl; // Print error message       
        return false;
    }
    buffer[tail] = element;                 //Write the element at the tail
    tail = (tail + 1) % capacity;           //Update the tail value (Move next)
    return true;
}

// Read an element from the Queue
template <typename T>
T CircularFIFO<T>::ReadElement(){
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty. Cannot read element");
        
    }
    T element = buffer[head];              //Read the elemet at the head
    head = (head + 1) % capacity;           // Move the head foward
    return element;        
}

// Check of queue is empty
template <typename T>
bool CircularFIFO<T>::isEmpty() const {
    return head == tail;                    //If head and tail are same, they are empty
}

//Check if queue is full
template <typename T>
bool CircularFIFO<T>::isFull() const {
    return (tail + 1) % capacity == head;     // If moving tail ahead, hits the head.
}

// Print Buffer elements
template <typename T>
void CircularFIFO<T>::printBufferElements() const {
    if (isEmpty()) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

   int current = head;

    std::cout << "Printing buffer elements: head = " << head 
              << ", tail = " << tail << ", capacity = " << capacity << std::endl;

    while (current != tail) {
        T ab = buffer[current]; // Access the AudioBuffer pointer
        if (ab) {  // Check if ab is not null
            std::cout << "AudioBuffer at location " << current 
                      << " is " << ab << ", sample count: " 
                      << ab->sample_count << std::endl;
            ab->printSamples();  // Print samples of the AudioBuffer
        } else {
            std::cout << "AudioBuffer at location " << current << " is nullptr." << std::endl;
        }
        current = (current + 1) % capacity;  // Move to the next index
    }
    std::cout << std::endl;  // New line after printing all elements
}

#endif // CIRCULAR_FIFO_H




