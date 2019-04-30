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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "lsm9ds1.h"

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 15000000;
static uint16_t delay = 0;
static int32_t fd = -1;	// File descriptor for LSM9DS0

static lsm9ds1_error_t transfer(uint8_t tx, uint8_t *rx)
{
	int8_t ret;

	struct spi_ioc_transfer tr[2] = {0};

	tr[0].tx_buf = (unsigned long)&tx;
	tr[0].len = sizeof(tx);
	tr[0].speed_hz = speed;
	tr[0].delay_usecs = delay;
	tr[0].bits_per_word = bits;

	tr[1].tx_buf = (unsigned long)rx;
	tr[1].len = sizeof(rx);
	tr[1].speed_hz = speed;
	tr[1].delay_usecs = delay;
	tr[1].bits_per_word = bits;

	ret = ioctl(fd, SPI_IOC_MESSAGE(2), tr);

	if (ret < 1) {
		return LSM9DS1_SPI_BUS_XFER_ERROR;
	}

	return 0;
}

static lsm9ds1_error_t get_spi_mode() {

	int8_t ret = -1;	// Function return codes.

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1) {
		return LSM9DS1_UNABLE_TO_GET_SPI_MODE;
	}

	return 0;
}

static lsm9ds1_error_t init_spi(void) {

	int8_t ret = -1;	// Function return codes.

	fd = open(DEVICE, O_RDWR);
	if (fd < 0) {
		return LSM9DS1_NOT_FOUND;
	}

	// Set to mode 3
	mode |= SPI_CPOL | SPI_CPHA;
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1) {
		return LSM9DS1_MODE_3_NOT_SET;
	}

	// Set the number of bits per word.
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1) {
		return LSM9DS1_NUM_BITS_NOT_SET;
	}

	// Set the max clock speed in hz
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1) {
		return LSM9DS1_CLOCK_NOT_SET;
	}
}

static lsm9ds1_error_t init_i2c(void) {
	// Probably won't implement for raspberrypi
	return LSM9DS1_BUS_NOT_SUPPORTED;
}

lsm9ds1_error_t lsm9ds1_read(uint8_t register_addr, uint8_t *rx) {

	lsm9ds1_error_t ret = LSM9DS1_UNKNOWN_ERROR;
	uint8_t tx = 0x80 | register_addr;
	ret = transfer(tx, rx);
	return ret;
}

lsm9ds1_error_t lsm9ds1_init(lsm9ds1_bus_t bus_type) {

	// If we have already opened the fd then return early
	if(fd >= 0) {
		return 0;
	}

	// Determine bus type being used.
	int8_t ret = -1;	// Function return codes.
	switch(bus_type) {
		case LSM9DS1_SPI_BUS:
			ret = init_spi();
			break;
		case LSM9DS1_I2C_BUS:
			ret = init_i2c();
			break;
		default:
			ret = LSM9DS1_BUS_NOT_SUPPORTED;
			break;

	}

	return ret;
}
