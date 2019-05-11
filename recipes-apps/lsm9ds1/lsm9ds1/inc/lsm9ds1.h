/*
 * Copyright (C) Your copyright.
 *
 * Author: Christopher Jordan-Denny
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef LSM9DS1_H_
#define LSM9DS1_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define DEVICE "/dev/spidev0.0"

#define SPI_READ 0x80
#define SPI_WRITE 0x0

typedef enum lsm9ds1_status {
	LSM9DS1_SUCCESS = 0,
	LSM9DS1_NOT_FOUND = -1,
	LSM9DS1_SPI_BUS_XFER_ERROR = -2,
	LSM9DS1_UNABLE_TO_GET_SPI_MODE = -3,
	LSM9DS1_MODE_3_NOT_SET = -4,
	LSM9DS1_NUM_BITS_NOT_SET = -5,
	LSM9DS1_CLOCK_NOT_SET = -6,
	LSM9DS1_BUS_NOT_SUPPORTED = -7,
	LSM9DS1_UNKNOWN_ERROR = -8,
	LSM9DS1_ALREADY_INIT_ERROR = -9,
} lsm9ds1_status_t;

typedef enum lsm9ds1_bus_t {
	LSM9DS1_SPI_BUS, LSM9DS1_I2C_BUS,
} lsm9ds1_bus_t;

typedef enum {
	LSM9DS1_REGISTER_WHO_AM_I_XG = 0x0F,
	LSM9DS1_REGISTER_CTRL_REG1_G = 0x10,
	LSM9DS1_REGISTER_CTRL_REG2_G = 0x11,
	LSM9DS1_REGISTER_CTRL_REG3_G = 0x12,
	LSM9DS1_REGISTER_TEMP_OUT_L = 0x15,
	LSM9DS1_REGISTER_TEMP_OUT_H = 0x16,
	LSM9DS1_REGISTER_STATUS_REG = 0x17,
	LSM9DS1_REGISTER_OUT_X_L_G = 0x18,
	LSM9DS1_REGISTER_OUT_X_H_G = 0x19,
	LSM9DS1_REGISTER_OUT_Y_L_G = 0x1A,
	LSM9DS1_REGISTER_OUT_Y_H_G = 0x1B,
	LSM9DS1_REGISTER_OUT_Z_L_G = 0x1C,
	LSM9DS1_REGISTER_OUT_Z_H_G = 0x1D,
	LSM9DS1_REGISTER_CTRL_REG4 = 0x1E,
	LSM9DS1_REGISTER_CTRL_REG5_XL = 0x1F,
	LSM9DS1_REGISTER_CTRL_REG6_XL = 0x20,
	LSM9DS1_REGISTER_CTRL_REG7_XL = 0x21,
	LSM9DS1_REGISTER_CTRL_REG8 = 0x22,
	LSM9DS1_REGISTER_CTRL_REG9 = 0x23,
	LSM9DS1_REGISTER_CTRL_REG10 = 0x24,

	LSM9DS1_REGISTER_OUT_X_L_XL = 0x28,
	LSM9DS1_REGISTER_OUT_X_H_XL = 0x29,
	LSM9DS1_REGISTER_OUT_Y_L_XL = 0x2A,
	LSM9DS1_REGISTER_OUT_Y_H_XL = 0x2B,
	LSM9DS1_REGISTER_OUT_Z_L_XL = 0x2C,
	LSM9DS1_REGISTER_OUT_Z_H_XL = 0x2D,

} lsm9ds1AccGyroRegisters_t;

typedef enum {

	LSM9DS1_REGISTER_WHO_AM_I_M = 0x0F,
	LSM9DS1_REGISTER_CTRL_REG1_M = 0x20,
	LSM9DS1_REGISTER_CTRL_REG2_M = 0x21,
	LSM9DS1_REGISTER_CTRL_REG3_M = 0x22,
	LSM9DS1_REGISTER_CTRL_REG4_M = 0x23,
	LSM9DS1_REGISTER_CTRL_REG5_M = 0x24,
	LSM9DS1_REGISTER_STATUS_REG_M = 0x27,
	LSM9DS1_REGISTER_OUT_X_L_M = 0x28,
	LSM9DS1_REGISTER_OUT_X_H_M = 0x29,
	LSM9DS1_REGISTER_OUT_Y_L_M = 0x2A,
	LSM9DS1_REGISTER_OUT_Y_H_M = 0x2B,
	LSM9DS1_REGISTER_OUT_Z_L_M = 0x2C,
	LSM9DS1_REGISTER_OUT_Z_H_M = 0x2D,
	LSM9DS1_REGISTER_CFG_M = 0x30,
	LSM9DS1_REGISTER_INT_SRC_M = 0x31,
} lsm9ds1MagRegisters_t;

typedef enum {
	LSM9DS1_ACCELRANGE_2G = (0b00 << 3),
	LSM9DS1_ACCELRANGE_16G = (0b01 << 3),
	LSM9DS1_ACCELRANGE_4G = (0b10 << 3),
	LSM9DS1_ACCELRANGE_8G = (0b11 << 3),
} lsm9ds1AccelRange_t;

typedef enum {
	LSM9DS1_ACCELDATARATE_POWERDOWN = (0b0000 << 4),
	LSM9DS1_ACCELDATARATE_3_125HZ = (0b0001 << 4),
	LSM9DS1_ACCELDATARATE_6_25HZ = (0b0010 << 4),
	LSM9DS1_ACCELDATARATE_12_5HZ = (0b0011 << 4),
	LSM9DS1_ACCELDATARATE_25HZ = (0b0100 << 4),
	LSM9DS1_ACCELDATARATE_50HZ = (0b0101 << 4),
	LSM9DS1_ACCELDATARATE_100HZ = (0b0110 << 4),
	LSM9DS1_ACCELDATARATE_200HZ = (0b0111 << 4),
	LSM9DS1_ACCELDATARATE_400HZ = (0b1000 << 4),
	LSM9DS1_ACCELDATARATE_800HZ = (0b1001 << 4),
	LSM9DS1_ACCELDATARATE_1600HZ = (0b1010 << 4)
} lm9ds1AccelDataRate_t;

typedef enum {
	LSM9DS1_MAGGAIN_4GAUSS = (0b00 << 5),  // +/- 4 gauss
	LSM9DS1_MAGGAIN_8GAUSS = (0b01 << 5),  // +/- 8 gauss
	LSM9DS1_MAGGAIN_12GAUSS = (0b10 << 5),  // +/- 12 gauss
	LSM9DS1_MAGGAIN_16GAUSS = (0b11 << 5)   // +/- 16 gauss
} lsm9ds1MagGain_t;

typedef enum {
	LSM9DS1_MAGDATARATE_3_125HZ = (0b000 << 2),
	LSM9DS1_MAGDATARATE_6_25HZ = (0b001 << 2),
	LSM9DS1_MAGDATARATE_12_5HZ = (0b010 << 2),
	LSM9DS1_MAGDATARATE_25HZ = (0b011 << 2),
	LSM9DS1_MAGDATARATE_50HZ = (0b100 << 2),
	LSM9DS1_MAGDATARATE_100HZ = (0b101 << 2)
} lsm9ds1MagDataRate_t;

typedef enum {
	LSM9DS1_GYROSCALE_245DPS = (0b00 << 3), // +/- 245 degrees per second rotation
	LSM9DS1_GYROSCALE_500DPS = (0b01 << 3), // +/- 500 degrees per second rotation
	LSM9DS1_GYROSCALE_2000DPS = (0b11 << 3) // +/- 2000 degrees per second rotation
} lsm9ds1GyroScale_t;

lsm9ds1_status_t lsm9ds1_read(uint8_t register_addr, uint8_t *rx);
lsm9ds1_status_t lsm9ds1_init(lsm9ds1_bus_t bus_type);

#ifdef __cplusplus
}
#endif

#endif /* LSM9DS1_H_ */
