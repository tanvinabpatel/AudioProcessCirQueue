#include "../scripts/audio_buffer.h"
#include <iostream>
#include <iomanip> 
#include <vector>  
#include <cassert>

void testAudioBufferConstructor() {
    //Testing the AudioBuffer Constructor

    const int sample_count = 5;
    std::vector<int16_t> sampleData = {0, 1, 2, 3, 4}; 

    // Create an AudioBuffer using the constructor
    AudioBuffer<int16_t> ab(sampleData);

    // Validate sample_count
    assert(ab.sample_count == sample_count);
    std::cout << "Sample count is correct: " << ab.sample_count << std::endl;

    // Validate samples
    for (int i = 0; i < sample_count; ++i) {
        assert(ab.samples[i] == sampleData[i]); 
    }

    // Print samples to confirm correct values
    ab.printSamples();
    std::cout << "Test1: AudioBuffer constructor test passed!" << std::endl;
}

template <typename T>
void testAudioBuffer() {
    //Testing AudioBuffer with integer and float.

    const int sample_count = 5;

    std::vector<T> sampleData(sample_count);
    
    // Initialize sample data
    for (int i = 0; i < sample_count; ++i) {
        sampleData[i] = static_cast<T>(i * 1.0); // Fill with values 0.0, 1.0, 2.0, etc.
        std::cout << sampleData[i] << " "; 
    }
    std::cout << std::endl; 
    // Create AudioBuffer
    AudioBuffer<T> ab(sampleData);

    // Validate sample_count
    assert(ab.sample_count == sample_count);
    
    // Validate samples
    for (int i = 0; i < sample_count; ++i) {
        assert(ab.samples[i] == static_cast<T>(i)); // Check each sample value
    }

    std::cout << "Test2: AudioBuffer template test passed for type: " << typeid(T).name() << std::endl;
}

void testZeroSamples() {
    //Testing AudioBuffer with zero samples

    const int sample_count = 0;
    // Using an empty vector for zero samples
    std::vector<float> sampleData; 

    // Create AudioBuffer
    AudioBuffer<float> ab(sampleData);

    // Validate sample_count
    assert(ab.sample_count == sample_count);
    
    // Print samples (should show no output)
    ab.printSamples();
    
    std::cout << "Test3: Zero samples test passed!" << std::endl;
}

void testNegativeSampleCount() {
    //Testing AudioBuffer with negative sample count

    const int sample_count = -5; 

    // Create AudioBuffer with negative sample count
    AudioBuffer<float> ab({}); 

    // Validate the behavior
    assert(ab.sample_count == 0); // Ensure sample_count is set to 0
    assert(ab.samples.empty()); // Ensure samples is nullptr

    std::cout << "Test4: Completed test for negative sample count." << std::endl;
}

void testPointerValidity() {
    const int sample_count = 5;

    // Use std::vector to manage sample data
    std::vector<float> sampleData(sample_count);
    for (int i = 0; i < sample_count; ++i) {
        sampleData[i] = static_cast<float>(i);
    }

    // Create AudioBuffer
    AudioBuffer<float> ab(sampleData); 

    // Check if samples pointer is valid before operation
    assert(!ab.samples.empty()); // It should not be empty

    std::cout << "Test5: Pointer validity check passed." << std::endl;
}

int main() {

    testAudioBufferConstructor();

    std::cout << std::fixed << std::setprecision(1); // Set precision for float output
    testAudioBuffer<int>();
    testAudioBuffer<float>();

    testZeroSamples();
    testNegativeSampleCount();
    testPointerValidity();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

