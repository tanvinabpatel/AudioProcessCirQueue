# Audio Processing Queue

## Objective
This project implements a First-In, First-Out (FIFO) queue using a circular buffer in C++. A circular buffer is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end. The queue is designed to store pointers to audio sample buffers.

## Structure

```
AudioProcessingQueue/
├── scripts/
│   ├── audio_buffer.h              // Header file for AudioBuffer struct
│   └── circular_fifo.h             // Header file for CircularFIFO class
│
├── tests/                          // Contains test cases
│   ├── test_circular_fifo.cpp      // Test file for CircularFIFO
│   └── test_audio_buffer.cpp       // Test file for AudioBuffer
│
├── main.cpp                        // Main entry point of the application
└── README.md                       // Project Overview

```
- `scripts/`: Contains the main implementation files.
- `tests/`: Contains unit tests for the implemented classes.
- `main.cpp`: Demonstrates usage of the queue and audio buffer.
- `README.md`: Documentation for the project.


## Build Instructions
To compile the project, run:

```
g++  main.cpp -I scripts/ -o AudioProcessingQueue

./AudioProcessingQueue
```

## Running Tests
To run the tests, execute:

```
g++ tests/test_audio_buffer.cpp -I scripts/ -o test_audio_buffer 
g++ tests/test_CircularFIFO.cpp -I scripts/ -o test_circular_fifo 

./test_audio_buffer
./test_circular_fifo

```
## Function Descriptions
This section provides a brief overview of the key functionalities of the main implementation and test files.

```AudioBuffer.h:``` A struct for managing audio sample data using a dynamic array. It includes a constructor for initialization and a method to print the audio samples.

```CircularFIFO.h:``` Defines a templated CircularFIFO class that implements a circular first-in, first-out (FIFO) queue. This class manages a dynamic array of pointers to elements of type T, providing methods to add (write) and remove (read) elements, check if the queue is empty or full, and print the current elements in the buffer. The design ensures efficient memory usage and prevents overflow by using a capacity management approach.

```main.cpp:``` Demonstrates the use of a circular FIFO queue to manage audio buffers, showcasing adding, reading, and error handling. It initializes audio buffers with sample data, interacts with the queue, and prints its contents to illustrate the queue's behavior.

```test_audio_buffer.cpp:``` Verifies the functionality of the AudioBuffer class by assessing its behavior with various sample counts, including positive, zero, and negative values. Ensures correct handling of different data types and pointer validity.

```test_circular_fifo.cpp:``` Evaluates the functionality of the circular FIFO queue implementation by examining its behavior during initialization, element writing and reading, and handling of full conditions. Each test case ensures the queue operates correctly, validating that it maintains the expected states and processes audio buffer elements efficiently while managing memory appropriately.
