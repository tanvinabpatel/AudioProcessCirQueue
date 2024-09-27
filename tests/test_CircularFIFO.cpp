#include "../scripts/circular_fifo.h"
#include "../scripts/audio_buffer.h"
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

    std::cout << "Default constructor test passed!" << std::endl;
}

void testWriteRead() {
    CircularFIFO<AudioBuffer<int16_t>*> fifo(3); // Capacity of 3

    // Prepare test data
    int16_t sampleData1[] = {1, 2, 3};
    AudioBuffer<int16_t>* ab1 = new AudioBuffer<int16_t>(sampleData1, 3);
    fifo.WriteElement(ab1);

    AudioBuffer<int16_t>* readAb1 = fifo.ReadElement();
    assert(readAb1->samples[0] == 1);
    delete readAb1; // Clean up

    std::cout << "Write/Read test passed!" << std::endl;
}

void testQueueFull() {
    CircularFIFO<AudioBuffer<int16_t>*> fifo(2); // Capacity of 2

    // Fill the queue
    int16_t sampleData1[] = {1, 2, 3};
    AudioBuffer<int16_t>* ab1 = new AudioBuffer<int16_t>(sampleData1, 3);
    fifo.WriteElement(ab1);

    int16_t sampleData2[] = {4, 5, 6};
    AudioBuffer<int16_t>* ab2 = new AudioBuffer<int16_t>(sampleData2, 3);
    fifo.WriteElement(ab2);

    // Attempt to write when queue is full
    int16_t sampleData3[] = {7, 8, 9};
    AudioBuffer<int16_t>* ab3 = new AudioBuffer<int16_t>(sampleData3, 3);

    // Check if WriteElement() blocks or returns false (depending on your implementation)
    // This is the critical part for checking full behavior
    bool writeSuccess = fifo.WriteElement(ab3); // Should either block or return false

    if (!writeSuccess) {
        std::cout << "Write failed as expected, queue is full!" << std::endl;
    } else {
        std::cout << "Error: Queue should not accept more elements when full!" << std::endl;
        assert(false);  // Fail the test if write was successful
    }

    // Clean up
    delete ab1;
    delete ab2;
    delete ab3;

    std::cout << "CircularFIFO full behavior test passed!" << std::endl;
}

int main() {
    testWriteRead();
    testDefaultConstructor();
    testQueueFull();
    return 0;
}
