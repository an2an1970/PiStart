# Pistart Project

## Overview

The Pistart project is a C-based application designed to parse and validate IMU (Inertial Measurement Unit) protocol packets. It serves as an example of how to use and verify the IMU protocol, including handling different packet rates and baud rates.

## Project Goals

The primary goal of this project is to demonstrate the use of the IMU protocol by processing and validating IMU data packets. The application parses hexadecimal representations of these packets, checks their integrity, and prints detailed information about the packet contents and any validation errors.

## Packet Rates and Baud Rates

The IMU protocol supports three different packet rates:
- **250 Hz**: Corresponds to a baud rate of **230400** bps.
- **500 Hz**: Corresponds to a baud rate of **460800** bps.
- **1000 Hz**: Corresponds to a baud rate of **921600** bps.

Ensure that the baud rate set for communication matches the packet rate used in the protocol.

## Files

- **pi.h**: Header file defining data structures, error codes, and functions used for handling IMU protocol packets.
- **pistart.c**: Main application file that includes functions for parsing packets, converting hexadecimal strings to byte arrays, and printing packet details.

## Functions

### `hexStringToByteArray`

Converts a hexadecimal string to a byte array.

**Parameters:**
- `hexString`: Hexadecimal string to convert.
- `byteArray`: Array to store the converted bytes.
- `byteArrayLen`: Pointer to store the length of the byte array.

**Returns:** Pointer to the byte array.

### `printByteArray`

Prints the contents of a byte array in hexadecimal format.

**Parameters:**
- `byteArray`: Array of bytes to print.
- `byteArrayLen`: Length of the byte array.

### `parsePacket`

Parses a packet from its hexadecimal string and prints the packet details.

**Parameters:**
- `packetHex`: Hexadecimal string representation of the packet.

### `printPacket`

Prints the details of an IMU protocol packet, including validation results.

**Parameters:**
- `buffer`: Pointer to the byte array containing the IMU protocol packet data.

### `PiProtErrorToString`

Converts an `ImuProtError_t` error code to its string representation.

**Parameters:**
- `error`: Error code to convert.

**Returns:** String describing the error.

## Compilation

To compile the project, use the following command:

```bash
gcc -o pistart pistart.c -I.
