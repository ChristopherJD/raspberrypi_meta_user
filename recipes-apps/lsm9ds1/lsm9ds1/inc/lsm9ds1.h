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
}lsm9ds1_status_t;

typedef enum lsm9ds1_bus_t {
	LSM9DS1_SPI_BUS, 
	LSM9DS1_I2C_BUS,
}lsm9ds1_bus_t;

lsm9ds1_status_t lsm9ds1_read(uint8_t register_addr, uint8_t *rx);
lsm9ds1_status_t lsm9ds1_init(lsm9ds1_bus_t bus_type);

#ifdef __cplusplus
}
#endif

#endif /* LSM9DS1_H_ */
