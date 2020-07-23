/**
 * API for upstream SPI communications
 *
 *
 * \author Etienne ARLAUD <earlaud@laas.fr>
 */

#ifndef SRC_SPIAPI_H_
#define SRC_SPIAPI_H_

// **************************************************************************
// the includes
#include "hal_2mtr.h"
#include <stdbool.h>
#include <stdint.h>

// **************************************************************************
// CRC

static const uint32_t crc32_table[] =
{
  0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9,
  0x130476dc, 0x17c56b6b, 0x1a864db2, 0x1e475005,
  0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
  0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd,
  0x4c11db70, 0x48d0c6c7, 0x4593e01e, 0x4152fda9,
  0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
  0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011,
  0x791d4014, 0x7ddc5da3, 0x709f7b7a, 0x745e66cd,
  0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
  0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5,
  0xbe2b5b58, 0xbaea46ef, 0xb7a96036, 0xb3687d81,
  0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
  0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49,
  0xc7361b4c, 0xc3f706fb, 0xceb42022, 0xca753d95,
  0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
  0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d,
  0x34867077, 0x30476dc0, 0x3d044b19, 0x39c556ae,
  0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
  0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16,
  0x018aeb13, 0x054bf6a4, 0x0808d07d, 0x0cc9cdca,
  0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
  0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02,
  0x5e9f46bf, 0x5a5e5b08, 0x571d7dd1, 0x53dc6066,
  0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
  0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e,
  0xbfa1b04b, 0xbb60adfc, 0xb6238b25, 0xb2e29692,
  0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
  0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a,
  0xe0b41de7, 0xe4750050, 0xe9362689, 0xedf73b3e,
  0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
  0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686,
  0xd5b88683, 0xd1799b34, 0xdc3abded, 0xd8fba05a,
  0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
  0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb,
  0x4f040d56, 0x4bc510e1, 0x46863638, 0x42472b8f,
  0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
  0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47,
  0x36194d42, 0x32d850f5, 0x3f9b762c, 0x3b5a6b9b,
  0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
  0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623,
  0xf12f560e, 0xf5ee4bb9, 0xf8ad6d60, 0xfc6c70d7,
  0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
  0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f,
  0xc423cd6a, 0xc0e2d0dd, 0xcda1f604, 0xc960ebb3,
  0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
  0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b,
  0x9b3660c6, 0x9ff77d71, 0x92b45ba8, 0x9675461f,
  0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
  0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640,
  0x4e8ee645, 0x4a4ffbf2, 0x470cdd2b, 0x43cdc09c,
  0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
  0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24,
  0x119b4be9, 0x155a565e, 0x18197087, 0x1cd86d30,
  0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
  0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088,
  0x2497d08d, 0x2056cd3a, 0x2d15ebe3, 0x29d4f654,
  0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
  0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c,
  0xe3a1cbc1, 0xe760d676, 0xea23f0af, 0xeee2ed18,
  0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
  0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0,
  0x9abc8bd5, 0x9e7d9662, 0x933eb0bb, 0x97ffad0c,
  0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
  0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

// **************************************************************************
// SPI packet definition

/* Position of the values in the command packet */
#define SPI_COMMAND_MODE 0
#define SPI_COMMAND_POS_1 1
#define SPI_COMMAND_POS_2 3
#define SPI_COMMAND_VEL_1 5
#define SPI_COMMAND_VEL_2 6
#define SPI_COMMAND_IQ_1 7
#define SPI_COMMAND_IQ_2 8
#define SPI_COMMAND_KP_1 9
#define SPI_COMMAND_KP_2 10
#define SPI_COMMAND_KD_1 11
#define SPI_COMMAND_KD_2 12
#define SPI_COMMAND_ISAT_12 13

/* Command packet -> mode : bits */
//! \brief Enable system
#define SPI_COMMAND_MODE_ES ((uint16_t) 1<<15)
//! \brief Enable motor 1
#define SPI_COMMAND_MODE_EM1 ((uint16_t) 1<<14)
//! \brief Enable motor 2
#define SPI_COMMAND_MODE_EM2 ((uint16_t) 1<<13)
//! \brief Raise an error if position rollover
#define SPI_COMMAND_MODE_EPRE ((uint16_t) 1<<12)
//! \brief Enable Index Offset Compensation for Motor 1
#define SPI_COMMAND_MODE_EI1OC ((uint16_t) 1<<11)
//! \brief Enable Index Offset Compensation for Motor 2
#define SPI_COMMAND_MODE_EI2OC ((uint16_t) 1<<10)
//! \brief Disable system if no valid SPI packet is received during this time [in ms]. (0 = disabled)
#define SPI_COMMAND_MODE_TIMEOUT ((uint16_t) 0xFF<<0)  //Timeout

/* Qvalues for each fields */
#define SPI_QN_POS  24
#define SPI_QN_VEL  11
#define SPI_QN_IQ   10
#define SPI_QN_ISAT 3
#define SPI_QN_CR   15
#define SPI_QN_ADC  16
#define SPI_QN_KP   16
#define SPI_QN_KD   16

/* Position of the values in the sensor packet */
#define SPI_SENSOR_STATUS 0
#define SPI_SENSOR_TIMESTAMP 1
#define SPI_SENSOR_POS_1 2
#define SPI_SENSOR_POS_2 4
#define SPI_SENSOR_VEL_1 6
#define SPI_SENSOR_VEL_2 7
#define SPI_SENSOR_IQ_1 8
#define SPI_SENSOR_IQ_2 9
#define SPI_SENSOR_CR_1 10
#define SPI_SENSOR_CR_2 11
#define SPI_SENSOR_ADC_1 12
#define SPI_SENSOR_ADC_2 13

/* sensor packet -> status : bits */
//! \brief System is enabled
#define SPI_SENSOR_STATUS_SE (1<<15)
//! \brief Motor 1 is enabled
#define SPI_SENSOR_STATUS_M1E (1<<14)
//! \brief Motor 1 is ready
#define SPI_SENSOR_STATUS_M1R (1<<13)
//! \brief Motor 2 is enabled
#define SPI_SENSOR_STATUS_M2E (1<<12)
//! \brief Motor 2 is ready
#define SPI_SENSOR_STATUS_M2R (1<<11)
//! \brief Encoder 1 index has been detected
#define SPI_SENSOR_STATUS_IDX1D (1<<10)
//! \brief Encoder 2 index has been detected
#define SPI_SENSOR_STATUS_IDX2D (1<<9)
//! \brief Flips each time encoder 1 index is detected
#define SPI_SENSOR_STATUS_IDX1T (1<<8)
//! \brief Flips each time encoder 1 index is detected
#define SPI_SENSOR_STATUS_IDX2T (1<<7)
//! \brief Error code
#define SPI_SENSOR_STATUS_ERROR (0xF<<0)

/* sensor packet -> status -> ERROR : values */
//! \brief No error
#define SPI_SENSOR_STATUS_ERROR_NO_ERROR 0
//! \brief Encoder error too high
#define SPI_SENSOR_STATUS_ERROR_ENCODER 1
//! \brief Timeout for receiving current references exceeded
#define SPI_SENSOR_STATUS_ERROR_SPI_RECV_TIMEOUT 2
//! \brief Motor temperature reached critical value
//! \note This is currently unused as no temperature sensing is done.
#define SPI_SENSOR_STATUS_ERROR_CRIT_TEMP 3  // currently unused
//! \brief Some error in the SpinTAC Position Convert module
#define SPI_SENSOR_STATUS_ERROR_POSCONV 4
//! \brief Position Rollover occured
#define SPI_SENSOR_STATUS_ERROR_POS_ROLLOVER 5
//! \brief Some other error
#define SPI_SENSOR_STATUS_ERROR_OTHER 7


#define SPI_TOTAL_INDEX 14
#define SPI_TOTAL_CRC 15

#define SPI_TOTAL_LEN 17

/* To properly handle SPI type conversion */
#define SPI_REG_u16(p_packet, pos) (*((uint16_t *) ((p_packet) + (pos))))
#define SPI_REG_u32(p_packet, pos) (*((uint32_t *) ((p_packet) + (pos))))

#define SPI_REG_16(p_packet, pos) (*((int16_t *) ((p_packet) + (pos))))
#define SPI_REG_32(p_packet, pos) (*((int32_t *) ((p_packet) + (pos))))



#define D32Q24_TO_D16QN(a,n)      ((a)>>(24-(n))&0xFFFF)
#define D32Q24_TO_D8QN(a,n)       ((a)>>(24-(n))&0xFF)

#define uD16QN_TO_D32Q24(a,n)      (((uint32_t)(a))<<(24-(n)))
#define uD8QN_TO_D32Q24(a,n)       (((uint32_t)(a))<<(24-(n)))

#define D16QN_TO_D32Q24(a,n)      (((int32_t)(a))<<(24-(n)))
#define D8QN_TO_D32Q24(a,n)       (((int32_t)(a))<<(24-(n)))

#define D32QN_TO_FLOAT(a,n)       ((float)(a)) / (1<<(n))
#define D16QN_TO_FLOAT(a,n)       ((float)(a)) / (1<<(n))
#define D8QN_TO_FLOAT(a,n)        ((float)(a)) / (1<<(n))

#define FLOAT_TO_uD32QN(a,n)      ((uint32_t) ((a) * (1<<(n))))
#define FLOAT_TO_uD16QN(a,n)      ((uint16_t) ((a) * (1<<(n))))
#define FLOAT_TO_uD8QN (a,n)      ((uint8_t)  ((a) * (1<<(n))))

#define FLOAT_TO_D32QN(a,n)       ((int32_t) ((a) * (1<<(n))))
#define FLOAT_TO_D16QN(a,n)       ((int16_t) ((a) * (1<<(n))))
#define FLOAT_TO_D8QN (a,n)       ((int8_t)  ((a) * (1<<(n))))


// **************************************************************************
// SUPER_packets : decide which packet to read, which to write

typedef struct spi_SUPER_packets_struct {
    uint16_t packets[2][SPI_TOTAL_LEN];
    bool first_ready;
} spi_SUPER_packets;

#define packet_to_write(packets_struct) ((packets_struct).first_ready ? (packets_struct).packets[1] : (packets_struct).packets[0])
#define packet_ready(packets_struct) ((packets_struct).first_ready ? (packets_struct).packets[0] : (packets_struct).packets[1])
#define spi_change_packets(packets_struct) ((packets_struct).first_ready = (packets_struct).first_ready ? false : true)

// **************************************************************************
// the globals

char spi_buffer_index = 0;
uint16_t spi_buffer[4];
_iq spi_set_current[2] = {0,0};
_iq spi_get_current[2] = {0,0};
_iq spi_get_position[2] = {0,0};
_iq spi_get_velocity[2] = {0,0};
_iq spi_get_adc6[2] = {0,0};
_iq spi_get_enc_index[2] = {0,0};

// **************************************************************************
// the function prototypes

//Words are 16 bit on the board. But CRC is computed 8 by 8 bits.
#define LSB_8(x) (x & 0xFFFF)
#define MSB_8(x) ((x >> 8) & 0xFFFF)

uint32_t spi_get_CRC(uint16_t *packet) {
    unsigned int len = SPI_TOTAL_LEN - 2; //Minus CRC
    unsigned int ptr = 0;

    uint32_t crc = 0xFFFFFFFF;
    while (len--)
    {
      crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ LSB_8(packet[ptr])) & 255];
      crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ MSB_8(packet[ptr])) & 255];

      ptr++;
    }
    return crc;
}

inline void updateCRC(uint32_t *crc, uint16_t data) {
    *crc = (*crc << 8) ^ crc32_table[((*crc >> 24) ^ MSB_8(data)) & 255];
    *crc = (*crc << 8) ^ crc32_table[((*crc >> 24) ^ LSB_8(data)) & 255];
}

bool spi_check_CRC(uint16_t *packet) {
    return (SPI_REG_u32(packet, SPI_TOTAL_CRC) == spi_get_CRC(packet));
}

void spi_compute_CRC(uint16_t *packet) {
   SPI_REG_u32(packet, SPI_TOTAL_CRC)  = spi_get_CRC(packet);
}

#endif /* SRC_SPIAPI_H_ */
