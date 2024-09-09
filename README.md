# PiStart

**PiStart** is a C library designed for handling communication protocols, including IMU data parsing and validation, in embedded systems.

## Features
- IMU protocol packet structure definition.
- Functions for validating IMU packet headers, sequence numbers, and CRC32 checksums.
- Simple and efficient implementation for embedded environments.

## Key Functions
- **piCheckProtBuffer**: Validates an IMU protocol packet by checking the header and CRC32 checksum.

## Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/pistart.git
    ```
2. Include `pi.h` in your project.

## Usage
```c
#include "pi.h"

// Example of buffer validation
PiProtError_t result = piCheckProtBuffer(buffer);
if (result == PI_PROT_OK) {
    // Packet is valid
}
