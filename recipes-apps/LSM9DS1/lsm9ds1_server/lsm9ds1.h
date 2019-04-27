/*
 * lsm9ds1.h
 *
 *  Created on: Apr 27, 2019
 *      Author: christopher
 */

#ifndef LSM9DS1_H_
#define LSM9DS1_H_

#include <stdint.h>

#define DEVICE "/dev/spidev0.0"

typedef enum lsm9ds1_error {
	LSM9DS1_NOT_FOUND = -1, 
	LSM9DS1_SPI_BUS_XFER_ERROR = -2,
	LSM9DS1_UNABLE_TO_GET_SPI_MODE = -3,
	LSM9DS1_MODE_3_NOT_SET = -4,
	LSM9DS1_NUM_BITS_NOT_SET = -5,
	LSM9DS1_CLOCK_NOT_SET = -6,
	LSM9DS1_BUS_NOT_SUPPORTED = -7,
	LSM9DS1_UNKNOWN_ERROR = -8,
}lsm9ds1_error_t;

typedef enum lsm9ds1_bus_t {
	LSM9DS1_SPI_BUS, 
	LSM9DS1_I2C_BUS,
}lsm9ds1_bus_t;

lsm9ds1_error_t lsm9ds0_read(uint8_t register_addr, uint8_t *rx);
lsm9ds1_error_t lsm9ds0_init(lsm9ds1_bus_t bus_type);

#endif /* LSM9DS1_H_ */
