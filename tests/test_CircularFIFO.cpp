#include "../scripts/circular_fifo.h"
#include "../scripts/audio_buffer.h"
#include <iostream>
#include <vector>
#include <cassert>

void testDefaultConstructor() {
    CircularFIFO<AudioBuffer<int16_t>*> fifo(2); // Using the default constructor

    // Check if the FIFO is empty right after initialization
    assert(fifo.isEmpty());      // Should be empty
    assert(!fifo.isFull());      // Should not be full

    // Check head and tail initialization
    assert(fifo.getHead() == 0);      // Head should be initialized to 0
    assert(fifo.getTail() == 0);      // Tail should be initialized to 0
    assert(fifo.getCapacity() > 0);   // Assuming default capacity is set to 10

    std::cout << "Test1: Default constructor test passed!" << std::endl;
}

void testWriteRead() {

    CircularFIFO<AudioBuffer<int16_t>*> fifo(3);                        // Capacity of 3

    // Prepare test data using std::vector
    std::vector<int16_t> sampleData1 = {1, 2, 3};
    AudioBuffer<int16_t>* ab1 = new AudioBuffer<int16_t>(sampleData1); // Pass vector instead of raw array

    fifo.writeElement(ab1);

    AudioBuffer<int16_t>* readAb1 = fifo.readElement();
    assert(readAb1->samples[0] == 1);
    delete readAb1; // Clean up

    std::cout << "Test2: Write/Read test passed!" << std::endl;
}

void testQueueFull() {
    CircularFIFO<AudioBuffer<int16_t>*> fifo(2);                        // Capacity of 2

    // Fill the queue
    std::vector<int16_t> sampleData1 = {1, 2, 3};
    AudioBuffer<int16_t>* ab1 = new AudioBuffer<int16_t>(sampleData1);
    fifo.writeElement(ab1);

    std::vector<int16_t> sampleData2 = {4, 5, 6};
    AudioBuffer<int16_t>* ab2 = new AudioBuffer<int16_t>(sampleData2);
    fifo.writeElement(ab2);

    // Attempt to write when queue is full
    std::vector<int16_t> sampleData3 = {7, 8, 9};
    AudioBuffer<int16_t>* ab3 = new AudioBuffer<int16_t>(sampleData3);

    // This is the part for checking full behavior
    bool writeSuccess = fifo.writeElement(ab3);             // Should either block or return false

    if (!writeSuccess) {
        std::cout << "Write failed as expected, queue is full!" << std::endl;
    } else {
        std::cout << "Error: Queue should not accept more elements when full!" << std::endl;
        assert(false);         
    }

    // Clean up
    delete ab1;
    delete ab2;
    delete ab3;

    std::cout << "Test3: CircularFIFO full behavior test passed!" << std::endl;
}

int main() {
    testWriteRead();
    testDefaultConstructor();
    testQueueFull();
    return 0;
}
