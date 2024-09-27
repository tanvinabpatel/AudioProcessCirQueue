# Audio Processing Queue

## Objective
This project implements a First-In, First-Out (FIFO) queue using a circular buffer in C++. A circular buffer is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end. The queue is designed to store pointers to audio sample buffers.

## Structure

```
AudioProcessingQueue/
├── scripts/
│   ├── audio_buffer.h              // Header file and for AudioBuffer struct
│   └── circular_fifo.h             // Header file for CircularFIFO class
│
├── tests/                          // Contains test cases
│   ├── test_circular_fifo.cpp      // Test file for CircularFIFO
│   └── test_audio_buffer.cpp       // Test file for AudioBuffer
│
├── main.cpp                        // Main entry point of the application
├── README.md                       // Project documentation
│
```
- `srcipts/`: Contains the main implementation files.
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
g++ tests/test_audio_buffer.cpp -o test_audio_buffer ../scripts/audio_buffer.h
g++ tests/test_circular_fifo.cpp -o test_circular_fifo ../scripts/circular_fifo.h

./test_audio_buffer
./test_circular_fifo

```
## Usage

## Function descriptions

```AudioBuffer.h:```  Define the AudioBuffer struct that will store a pointer to audio samples and the sample count.

```CircularFIFO.h:``` Contains the class declaration for CircularFIFO and the implementation of the CircularFIFO class. 
Define the queue operations such as WriteElement, ReadElement, isEmpty, isFull, and printBufferElements.

```main.cpp:``` Create instances of CircularFIFO and AudioBuffer, and demonstrate their usage with some sample data.


```test_CircularFIFO.cpp``` Contains unit tests for the CircularFIFO class. Include various test cases to validate functionality and edge cases.

```test_audio_buffer.cpp``` Contains unit tests specifically for the AudioBuffer struct. 