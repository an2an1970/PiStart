#ifndef pi_h_included
#define pi_h_included

#include <stdint.h>

#define PI_HEADER	0x3141

#define PI_MUXFACTOR	64

#define PI_GYRO_SCALE	(1 << 17)
#define PI_ACCL_SCALE	(1 << 17)
#define PI_MAGN_SCALE	(1 << 21)
#define PI_PRES_SCALE	(1 << 15)
#define PI_TEMP_SCALE	(1 << 8)
#define PI_VOLT_SCALE	(1 << 8)
#define PI_AMPR_SCALE	(1 << 12)

static inline float fp1_14_17ToFloat(int32_t fp) {
	return 1.0f / (1 << 17) * fp;
}

static inline float fp1_10_21ToFloat(int32_t fp) {
	return 1.0f / (1 << 21) * fp;
}

static inline float fp17_15ToFloat(uint32_t fp) {
	return 1.0f / (1 << 15) * fp;
}


#pragma pack(1)
typedef union {
	uint16_t date;				// 4	uint16	Build date (Year.Month.Day: 7.4.5р)
	struct {
		uint16_t	day:5;
		uint16_t	mon:4;
		uint16_t	year:7;
	};
} PiDate_t;

typedef union {
	uint16_t version;			// 3	uint16	Version (Major.Minor.Build: 3.5.8р)
	struct {
		uint16_t	build:8;
		uint16_t	minor:5;
		uint16_t	major:3;
	};
} PiVersion_t;

typedef	union {
	struct {
		uint16_t	fault:1;					// 0 - IMU fault

		uint16_t	xAcclFault:1;				// 1 - Accel XYZ fault

		uint16_t	xGyroFault:1;				// 2 - Gyro XYZ fault

		uint16_t	xMagnFault:1;				// 3 - Magnetometer XYZ fault

		uint16_t	pressureFault:1;			// 4 - pressuremeter fault

		uint16_t	undervoltage:1;				// 5 - undervoltage
		uint16_t	overvoltage:1;				// 6 - overvoltage

		uint16_t	undertemperature:1;			// 7 - undertemperature
		uint16_t	overtemperature:1;			// 8 - overtemperature

		uint16_t	firmwareCRCError:1;			// 9 - firmware CRC error

		uint16_t	configCRCError:1;			// 10 - config CRCerror

		uint16_t	reserved:5;
	};
	uint16_t ui16;
} PiFault_t;

typedef	union {
	struct {
		uint16_t	state:3;		// state 0 = ready, 1 = prepare, 2 = warmup, 3 = fault

		int16_t		gyroXOverange:1;
		int16_t		gyroYOverange:1;
		int16_t		gyroZOverange:1;

		int16_t		acclXOverange:1;
		int16_t		acclYOverange:1;
		int16_t		acclZOverange:1;

		int16_t		magnetometerXOverange:1;
		int16_t		magnetometerYOverange:1;
		int16_t		magnetometerZOverange:1;

		int16_t		pressureOverange:1;
	};
	uint16_t ui16;
} PiFlags_t;

typedef union {
	struct {
		uint32_t uptime;

		uint32_t gitShort;

		PiDate_t buildDate;				// 	uint16	Дата сборки ПО (Год.Месяц.День: 7.4.5р)
		PiDate_t manufacturedDate;		// 	uint16	Дата производства ПО (Год.Месяц.День: 7.4.5р)

		PiVersion_t version;
		uint16_t humanSerial;

		uint32_t hwSerial;

		int16_t	tInternal;	// 1.7.8 Celsius degree
		int16_t	tExternal;

		uint16_t voltage;		//  input voltage in 8.8V format
		uint16_t current;		// 	input current in 3.13V format

		PiFault_t triggered;
		uint16_t  packetRate;

		uint32_t reserved[];	// 10..31	–	Резерв
	};
	uint8_t  ui8[0];
	uint16_t ui16[0];
	uint32_t ui32[PI_MUXFACTOR];
} PiMux_t;

typedef	struct {
	PiFlags_t	flags;
	PiFault_t	fault;

	int32_t	accl[3];
	int32_t	gyro[3];
	int32_t	magn[3];

	uint32_t	pressure;	// 21.11
} PiMainData_t;

typedef union {
	struct {
		uint16_t	header;
		uint16_t	sequence;

		PiMainData_t data;

		uint32_t	mux;
    
		uint32_t	crc32;
	};

	uint8_t ui8[0];
	uint8_t ui16[0];
	uint8_t ui32[0];
} PiProt_t;
#pragma pack()

/**
 * @enum ImuProtError_t
 * @brief Defines error codes used to indicate issues with the IMU protocol.
 *
 * This enum is used to signal different types of errors that may occur
 * while processing IMU data packets, such as incorrect headers, invalid
 * sequences, or CRC validation failures.
 */
typedef enum {
    PI_PROT_OK = 0,                // No error, the data packet is valid.
    PI_PROT_BAD_HEADER = 1,        // The packet header is invalid or does not match the expected value.
    PI_PROT_BAD_CRC = 3            // The CRC check failed, indicating data corruption.
} PiProtError_t;

#define CRC32_INITIAL 0xFFFFFFFFUL
#define CRC32_POLYNOM 0xEDB88320UL
#define CRC32_REMINDER 0x2144df1cUL

#ifdef PI_SOFT_CRC
/**
 * @brief Computes the CRC32 checksum of a buffer using a software-based implementation.
 *
 * This function calculates the CRC32 checksum of a given buffer using a 
 * software-based algorithm. It uses a polynomial and an initial value to 
 * compute the CRC, processing each byte of the buffer and updating the 
 * checksum accordingly.
 *
 * @param buff Pointer to the buffer containing the data to be checked.
 * @param len Length of the buffer in bytes.
 * @return uint32_t The computed CRC32 checksum.
 */
static inline uint32_t piCrc32(const uint8_t *buff, unsigned short len) {
	uint32_t crc = CRC32_INITIAL;
	unsigned short i, j;
	for (i = 0; i < len; i++)
	{
		crc = crc ^ *buff++;
		for (j = 0; j < 8; j++)
		{
			if (crc & 1)
				crc = (crc >> 1) ^ CRC32_POLYNOM;
			else
				crc = crc >> 1;
		}
	}
	return crc ^ CRC32_INITIAL;
}
#else
/**
 * @brief Precomputed CRC32 lookup table for optimizing CRC32 calculations.
 *
 * This table contains precomputed values for the CRC32 algorithm, used in
 * a table-based implementation to speed up the CRC32 checksum computation.
 * Each entry in the table corresponds to a possible value of the least 
 * significant byte of the CRC, facilitating quick lookups during CRC 
 * calculations.
 *
 * The table is indexed by the value of the current byte in the buffer being 
 * processed, and it helps to reduce the number of computations required to 
 * update the CRC value.
 */
static uint32_t crc32_ccitt_table[256] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419,
	0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4,
	0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07,
	0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856,
	0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4,
	0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
	0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3,
	0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a,
	0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599,
	0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190,
	0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f,
	0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e,
	0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
	0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed,
	0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3,
	0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
	0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a,
	0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5,
	0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010,
	0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17,
	0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6,
	0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615,
	0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
	0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344,
	0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a,
	0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
	0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1,
	0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c,
	0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef,
	0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe,
	0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31,
	0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c,
	0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
	0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b,
	0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1,
	0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
	0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278,
	0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7,
	0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66,
	0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605,
	0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8,
	0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b,
	0x2d02ef8d};

/**
 * @brief Computes the CRC32 checksum of a buffer using a table-based implementation.
 *
 * This function calculates the CRC32 checksum of a given buffer using a 
 * table-based algorithm. A precomputed table is used to speed up the CRC 
 * computation, processing each byte of the buffer and updating the checksum 
 * based on the precomputed values.
 *
 * @param buff Pointer to the buffer containing the data to be checked.
 * @param len Length of the buffer in bytes.
 * @return uint32_t The computed CRC32 checksum.
 */
static inline uint32_t piCrc32(const uint8_t *buff, unsigned short len) {
	uint32_t crc32 = CRC32_INITIAL;
	unsigned short i;
	for (i = 0; i < len; i++)
	{
		crc32 = crc32_ccitt_table[(crc32 ^ buff[i]) & 0xff] ^ (crc32 >> 8);
	}
	return crc32 ^ CRC32_INITIAL;
}
#endif

/**
 * @brief Validates the contents of an IMU protocol data packet buffer.
 *
 * This function checks the integrity of the IMU protocol packet by verifying its header, 
 * sequence numbers, and CRC32 checksum. If any validation fails, the corresponding 
 * error code from the ImuProtError_t enum is returned.
 *
 * @param buffer Pointer to the buffer containing the IMU protocol packet.
 * @return ImuProtError_t The result of the validation:
 *         - IMU_PROT_OK: The packet is valid.
 *         - IMU_PROT_BAD_HEADER: The header is invalid.
 *         - IMU_PROT_BAD_SEQUENCER: The sequence numbers do not match.
 *         - IMU_PROT_BAD_CRC: The CRC32 checksum is incorrect.
 */
static inline PiProtError_t piCheckProtBuffer(const void * buffer) {
    const PiProt_t* prot = (const PiProt_t*)buffer;

    if (PI_HEADER != prot->header) {
        return PI_PROT_BAD_HEADER;
    }

    if (piCrc32((void*)&prot->sequence, sizeof(PiProt_t) - sizeof(uint32_t) - sizeof(prot->header)) != prot->crc32) {
        return PI_PROT_BAD_CRC;
    }
	return PI_PROT_OK;
}

#endif	/* #ifdef pi_h_included */
