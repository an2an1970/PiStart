#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pi.h"

/**
 * @brief Converts a hexadecimal string to a byte array.
 *
 * Converts the given hexadecimal string into a byte array. The length of the resulting
 * byte array is stored in `byteArrayLen`.
 *
 * @param hexString A string containing hexadecimal values.
 * @param byteArray Array to store the converted byte values.
 * @param byteArrayLen Pointer to store the length of the byte array.
 * @return Pointer to the byte array.
 */
const uint8_t * hexStringToByteArray(const char* hexString, uint8_t * byteArray, size_t* byteArrayLen);

/**
 * @brief Prints a byte array in hexadecimal format.
 *
 * Prints each byte in the array as a two-digit hexadecimal value.
 *
 * @param byteArray Array of bytes to print.
 * @param byteArrayLen Length of the byte array.
 */
void printByteArray(const unsigned char* byteArray, size_t byteArrayLen);

/**
 * @brief Parses a packet from its hexadecimal string representation and prints the packet details.
 *
 * Converts the packet's hexadecimal string representation into a byte array and then prints
 * the details using `printPacket`.
 *
 * @param packetHex Hexadecimal string of the packet.
 */
void parsePacket(const char * packetHex);

/**
 * @brief Prints the details of an IMU protocol packet.
 *
 * Validates the packet using `piCheckProtBuffer`, calculates the CRC32 checksum, and prints
 * the packet details including header, sequence, temperature, gyro, and accelerometer values.
 *
 * @param buffer Pointer to the byte array containing the IMU protocol packet data.
 */
void printPacket(const uint8_t * buffer);

/**
 * @brief Converts an ImuProtError_t error code to its string representation.
 *
 * @param error The ImuProtError_t error code.
 * @return A string describing the error.
 */
const char* PiProtErrorToString(PiProtError_t error);

int main(void) {
    printf("Size Header Sequencer GyroX      GyroY      GyroZ      AcclX      AcclY"
	       "      AcclZ    CRC32      Check      Validation result\n");
	parsePacket("41310b31000000002edbffff65a3ffff127f1300920f0000fcecffffefddffff560efefffed4ffff560e0d006847f50100000000118b05a7");
	parsePacket("41310c310000000021d7ffffefacffffec911300f8940000a6fbffff4decffff560efefffed4ffff560e0d006847f501000000007d162721");
	parsePacket("41310d3100000000c3d9ffff70c2ffffec9413006494000020f1ffffea100000560efefffed4ffff560e0d006847f5010000000091f15ddd");
	parsePacket("41310e310000000073ddffff34adffff02a313002b0400003a000000ad0100006811feffecd1ffff7b140d008846f50100000000c6f189c3");
	parsePacket("41310f3100000000e7d8ffffb698fffff19a130053b8ffff91200000fce0ffff6811feffecd1ffff7b140d008846f501000000000db29a51");
	parsePacket("413110310000000070c8ffff31b1ffffd08413004012000059120000f7faffff6811feffecd1ffff7b140d008846f5010000000044c014f1");
	parsePacket("4131113100000000f9d9ffffc2a9ffffdba613001028000058e0ffffae2b00006811feffecd1ffff7b140d008846f501000000009a05822b");
	parsePacket("413112310000000065f2ffffeeadffff5b911300c4fdffff11e4ffff460200006811feffecd1ffff7b140d008846f50100000000cf7d7fc4");
	parsePacket("41311331000000001ac7ffff4ab0ffff8b8113004d240000862b0000e6e4ffff1f05feff48e1ffffb21d0d008846f501000000000c6ad8b4");
	parsePacket("413114310000000073d1ffff9ba7ffffc19d1300ac4e00009c000000050700001f05feff48e1ffffb21d0d008846f50100000000ecdbe12f");
	parsePacket("413115310000000068f9ffffb3befffff0951300cc590000deb4ffffb42500001f05feff48e1ffffb21d0d008846f501000000006d50cdbb");
	parsePacket("413116310000000084caffff62baffff23961300fd05000087160000de3300001f05feff48e1ffffb21d0d008846f501000000002a6d678f");
	parsePacket("4131173100000000c2c9ffff4da4fffffe9213007965ffffae300000331200001f05feff48e1ffffb21d0d008846f501000000007524328d");
	parsePacket("41311831000000000ff0ffff1f96ffffca8b13000562ffff3fc9ffffc71400000c02feff48e1ffffb21d0d00a845f5010000000039f597aa");
	parsePacket("413119310000000049d5ffff269fffff548a1300c0ffffffdeeeffff391c00000c02feff48e1ffffb21d0d00a845f501000000006ee8c428");
	parsePacket("41311a3100000000cdccfffff0b3ffff049a1300c18200004b130000f4fbffff0c02feff48e1ffffb21d0d00a845f501000000006b2a26a8");
	parsePacket("41311b310000000038e9ffff9cb5ffff99a61300c0a00000b4cdffff540d00000c02feff48e1ffffb21d0d00a845f501000000007a6dae1c");
	parsePacket("41311c31000000006cdbffff51b7ffff7d9b1300233a000090f9ffff7c0500000c02feff48e1ffffb21d0d00a845f5010000000065563f06");
	parsePacket("41311d310000000005d4ffff41b1ffff8e941300ceb2ffff971f000062ebffffb0f2fdff35deffff31080d00a845f5010000000068a2cf36");
	parsePacket("41311e3100000000eae6ffff1eabffff1a881300a596ffffede4ffffc0e6ffffb0f2fdff35deffff31080d00a845f50100000000208bb5e9");
	parsePacket("41311f3100000000dad3ffffe2a8ffffb88e13004aa6ffff13fbffffdcceffffb0f2fdff35deffff31080d00a845f501000000004835791c");
	parsePacket("413120310000000090d3ffff6ea8ffffbe8f13002be2ffff32030000a3d2ffffb0f2fdff35deffff31080d00a845f50100000000310ab94a");
	parsePacket("4131213100000000c6dfffff98abffffac8d1300334700003de9ffffe4f8ffffb0f2fdff35deffff31080d00a845f5010000000074fded62");
	parsePacket("4130213100000000c6dfffff98abffffac8d1300334700003de9ffffe4f8ffffb0f2fdff35deffff31080d00a845f5010000000074fded62");
	// Wrong bit ---^
	parsePacket("4131213100100000c6dfffff98abffffac8d1300334700003de9ffffe4f8ffffb0f2fdff35deffff31080d00a845f5010000000074fded62");
	// Wrong bit ----------^
	parsePacket("4131213100100000c6dfffff98abffffac8d1300334700003de9ffffe4f8ffffb0f2fdff35deffff31080d00a845f5010000000074fded60");
	// Wrong bit ---------------------------------------------------------------------------------------------------------------^

	// parsePacket("74951FE00000000000007F79AFFEFFFFCFF4FFFFEAFBFFFF36F1FFFFC5E3FFFFA8C30900C14BE115");
	// parsePacket("749520DF3F03000000007F79F2F6FFFFD7EEFFFF13F6FFFF82EFFFFF5AE6FFFF01C90900022D0189");
	// parsePacket("749522DD0000000000007F7912EFFFFF99F4FFFFFEF9FFFFBFEAFFFFAADCFFFFB5CA0900C8E47F2F");
	// parsePacket("749422DD0000000000007F7912EFFFFF99F4FFFFFEF9FFFFBFEAFFFFAADCFFFFB5CA0900C8E47F2F");	// Broken packet
	// // Wrong bit ---^
	// parsePacket("749522CD0000000000007F7912EFFFFF99F4FFFFFEF9FFFFBFEAFFFFAADCFFFFB5CA0900C8E47F2F");	// Broken packet
	// // Wrong bit ------^
	// parsePacket("749522DD0000100000007F7912EFFFFF99F4FFFFFEF9FFFFBFEAFFFFAADCFFFFB5CA0900C8E47F2F");	// Broken packet
	// // Wrong bit ------------^

	return 0;
}

/**
 * @brief Parses a packet given its hexadecimal string representation and prints the packet details.
 *
 * This function converts the hexadecimal string representation of the packet into a byte array,
 * then prints the details of the packet using the `printPacket` function.
 *
 * @param packetHex A string containing the hexadecimal representation of the packet.
 */
void parsePacket(const char * packetHex) {
	uint8_t buffer[256];
	size_t size;
	printPacket(hexStringToByteArray(packetHex, buffer, &size));
}

/**
 * @brief Prints the details of an IMU protocol packet.
 *
 * This function checks the validity of the packet using `checkImuProtBuffer`, calculates the CRC32 checksum
 * of the packet, and prints the packet details including header, sequencer, temperature, gyro, and accelerometer values.
 *
 * @param buffer A pointer to the byte array containing the IMU protocol packet data.
 */
void printPacket(const uint8_t * buffer) {
	PiProt_t * imuBuffer = (PiProt_t*)buffer;
	PiProtError_t result = piCheckProtBuffer(buffer);
	uint32_t crc32 = piCrc32((void*)&(imuBuffer->sequence), sizeof(PiProt_t) - 4 - 2);

	printf("%d   0x%04X %05d % 10.3f % 10.3f % 10.3f % 10.3f % 10.3f % 10.3f  0x%08X 0x%08X (%d) %s\n", 
		(int)sizeof(PiProt_t), imuBuffer->header, imuBuffer->sequence,
		fp1_14_17ToFloat(imuBuffer->data.gyro[0]), fp1_14_17ToFloat(imuBuffer->data.gyro[1]), fp1_14_17ToFloat(imuBuffer->data.gyro[2]), 
		fp1_14_17ToFloat(imuBuffer->data.accl[0]), fp1_14_17ToFloat(imuBuffer->data.accl[1]), fp1_14_17ToFloat(imuBuffer->data.accl[2]),
		imuBuffer->crc32, crc32, (int)result, PiProtErrorToString(result));
}

/**
 * @brief Converts a hexadecimal string to a byte array.
 *
 * This function takes a string representing hexadecimal values and converts it into a byte array.
 * The length of the resulting byte array is computed and stored in the provided `byteArrayLen` pointer.
 *
 * @param hexString A string containing hexadecimal values, with each pair of characters representing a byte.
 * @param byteArray A pointer to an array where the converted byte values will be stored.
 * @param byteArrayLen A pointer to a size_t variable where the length of the byte array will be stored.
 *
 * @return A pointer to the byte array containing the converted values.
 */
const uint8_t * hexStringToByteArray(const char* hexString, uint8_t * byteArray, size_t* byteArrayLen) {
    size_t strLen = strlen(hexString);
    *byteArrayLen = strLen / 2;
    
    for (size_t i = 0; i < *byteArrayLen; i++) {
        char byteStr[3] = { hexString[i * 2], hexString[i * 2 + 1], '\0' };
        byteArray[i] = (uint8_t )strtol(byteStr, NULL, 16);
    }

	return byteArray;
}

/**
 * Prints a byte array in hexadecimal format.
 *
 * @param byteArray Array of bytes to print.
 * @param byteArrayLen Length of the byte array.
 */
void printByteArray(const unsigned char* byteArray, size_t byteArrayLen) {
    printf("Byte array: ");
    for (size_t i = 0; i < byteArrayLen; i++) {
        printf("%02X ", byteArray[i]);
    }
    printf("\n");
}

/**
 * @brief Converts an ImuProtError_t error code to its corresponding string representation.
 *
 * @param error The ImuProtError_t error code.
 * @return A string that describes the error.
 */
const char* PiProtErrorToString(PiProtError_t error) {
    switch (error) {
        case PI_PROT_OK:
            return "OK.";
        case PI_PROT_BAD_HEADER:
            return "Invalid header!";
        case PI_PROT_BAD_CRC:
            return "CRC validation failed!";
    }
	return "Unknown error.";
}
