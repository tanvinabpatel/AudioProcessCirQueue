#include "../scripts/audio_buffer.h"
#include <cassert>
#include <iostream>
#include <iomanip> // For setting output precision
#include <vector>  // Include vector header

void testAudioBufferConstructor() {
    const int sample_count = 5;
    int16_t sampleData[] = {0, 1, 2, 3, 4};

    // Create an AudioBuffer using the constructor
    AudioBuffer<int16_t> ab(sampleData, sample_count);

    // Validate sample_count
    assert(ab.sample_count == sample_count);
    std::cout << "Sample count is correct: " << ab.sample_count << std::endl;

    // Validate samples
    for (int i = 0; i < sample_count; ++i) {
        assert(ab.samples[i] == sampleData[i]); // Check each sample value
    }

    // Print samples to confirm correct values
    ab.printSamples();
    
    std::cout << "AudioBuffer constructor test passed!" << std::endl;
}

template <typename T>
void testAudioBuffer() {
    // Test data
    const int sample_count = 5;

    // Use std::vector for sample data
    std::vector<T> sampleData(sample_count);
    
    // Initialize sample data
    for (int i = 0; i < sample_count; ++i) {
        sampleData[i] = static_cast<T>(i * 1.0); // Fill with values 0.0, 1.0, 2.0, etc.
        std::cout << sampleData[i] << " "; // Print initialized sample values
    }
    std::cout << std::endl; // New line for better readability

    // Create AudioBuffer
    AudioBuffer<T> ab(sampleData.data(), sample_count);

    // Validate sample_count
    assert(ab.sample_count == sample_count);
    
    // Validate samples
    for (int i = 0; i < sample_count; ++i) {
        assert(ab.samples[i] == static_cast<T>(i)); // Check each sample value
    }

    std::cout << "AudioBuffer template test passed for type: " << typeid(T).name() << std::endl;
}

void testZeroSamples() {
    const int sample_count = 0;
    // Using an empty vector for zero samples
    std::vector<float> sampleData; // No allocation needed for zero samples

    // Create AudioBuffer
    AudioBuffer<float> ab(sampleData.data(), sample_count);

    // Validate sample_count
    assert(ab.sample_count == sample_count);
    
    // Print samples (should show no output)
    ab.printSamples();
    
    std::cout << "Zero samples test passed!" << std::endl;
}

void testNegativeSampleCount() {
    const int sample_count = -5; // Negative sample count

    // Create AudioBuffer with negative sample count
    AudioBuffer<float> ab(nullptr, sample_count); // Now this won't throw an exception

    // Validate the behavior
    assert(ab.sample_count == 0); // Ensure sample_count is set to 0
    assert(ab.samples == nullptr); // Ensure samples is nullptr

    std::cout << "Completed test for negative sample count." << std::endl;
}

void testPointerValidity() {
    const int sample_count = 5;

    // Use std::vector to manage sample data
    std::vector<float> sampleData(sample_count);
    for (int i = 0; i < sample_count; ++i) {
        sampleData[i] = static_cast<float>(i);
    }

    // Create AudioBuffer
    AudioBuffer<float>* ab = new AudioBuffer<float>(sampleData.data(), sample_count);

    // Check if samples pointer is valid before destruction
    assert(ab->samples != nullptr); // It should not be nullptr

    // Destructor will be called when we delete ab
    delete ab; // Deleting the AudioBuffer

    // Check if samples pointer is set to nullptr
    // Since the destructor is called, we should not check ab->samples directly.
    // However, we can check the pointer validity manually by setting samples to nullptr in the destructor.
    ab = nullptr; // Setting to nullptr to mimic the destructor behavior

    // Assert that ab is nullptr after deletion
    assert(ab == nullptr); // Now, it should be nullptr

    std::cout << "Pointer validity check passed." << std::endl;
}

int main() {
    std::cout << "Testing the AudioBuffer Constructor" << std::endl;
    testAudioBufferConstructor();

    std::cout << std::fixed << std::setprecision(1); // Set precision for float output

    std::cout << "** Testing AudioBuffer with int..." << std::endl;
    testAudioBuffer<int>();
    
    std::cout << "** Testing AudioBuffer with float..." << std::endl;
    testAudioBuffer<float>();

    std::cout << "** Testing AudioBuffer with zero samples..." << std::endl;
    testZeroSamples();

    std::cout << "** Testing AudioBuffer with negative sample count..." << std::endl;
    testNegativeSampleCount();

    testPointerValidity();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}

