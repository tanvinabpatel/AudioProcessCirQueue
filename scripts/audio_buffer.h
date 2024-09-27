#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include <iostream>
#include <vector>                       

// Define the struct AudioBuffer
template <typename T>
struct AudioBuffer {
    std::vector<T> samples;             // Use vector to manage audio samples
    int sample_count;                   // Number of samples

    // Constructor for AudioBuffer
    AudioBuffer(const std::vector<T>& input_samples)
        : samples(input_samples), sample_count(input_samples.size()) {
        if (samples.empty()) {
        std::cout << "Error: Sample count cannot be zero." << std::endl;
        }
    }

    // Method to print the samples
    void printSamples() const {
        std::cout << "Contents: ";
        for (const auto &sample : samples) {
            std::cout << sample << " "; 
        }
        std::cout << std::endl;
    }

};

#endif // AUDIO_BUFFER_H

