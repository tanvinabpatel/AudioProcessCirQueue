#include <iostream>
#include <vector>
#include "scripts/audio_buffer.h"      // Include the AudioBuffer header
#include "scripts/circular_fifo.h"     // Include the CircularFIFO header

int main() {
    // Create a Circular FIFO queue with capacity for 2 AudioBuffer pointers
    CircularFIFO<AudioBuffer<int16_t>*> audioQueue(2);

    // Create sample data using std::vector
    int sample_count = 10;
    std::vector<int16_t> SampleData1(sample_count);
    std::vector<int16_t> SampleData2(sample_count);

    //Fill the SampleData with data
    for (int i = 0; i < sample_count; i++) {
        SampleData1[i] = i;               
        SampleData2[i] = sample_count + i; 
    }

    // Create AudioBuffer instances using the sample vectors
    AudioBuffer<int16_t> *ab1 = new AudioBuffer<int16_t>(SampleData1);
    AudioBuffer<int16_t> *ab2 = new AudioBuffer<int16_t>(SampleData2);

     // Add AudioBuffers to the queue
    if (!audioQueue.writeElement(ab1)) {
        std::cout << "Failed to write ab1 to audioQueue!" << std::endl;
    }

    audioQueue.printBufferElements(); 

    if (!audioQueue.writeElement(ab2)) {
        std::cout << "Failed to write ab2 to audioQueue!" << std::endl;
    }

    audioQueue.printBufferElements(); 

    // Try to add ab2 again to test full queue behavior
    if (!audioQueue.writeElement(ab2)) {
        std::cout << "Failed to write ab2 to audioQueue!" << std::endl;
    }
    audioQueue.printBufferElements(); 

    // Read an element from the queue
    try {
        audioQueue.readElement();
    } catch (const std::underflow_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    try {
        audioQueue.readElement();
    } catch (const std::underflow_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    audioQueue.printBufferElements(); // Print buffer contents

    // Try to read from queue to check empty queue behavior
    try {
        audioQueue.readElement();
    } catch (const std::underflow_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
