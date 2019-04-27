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

#include <stdint.h>
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
static uint32_t speed = 15000000;	//TODO Why is this not the correct speed in MHZ? This about 9.09 MHZ
static uint16_t delay = 0;

static void pabort(const char *s) {
	perror(s);
	abort();
}

static void transfer(int fd)
{
	int ret;
	uint8_t tx[] = {
		0x80 | 0xF,
	};
	uint8_t rx[sizeof(tx)] = {0, };
	struct spi_ioc_transfer tr[2] = {
		{
			.tx_buf = (unsigned long)tx,
			.len = sizeof(tx),
			.delay_usecs = delay,
			.speed_hz = speed,
			.bits_per_word = bits,
		},
		{
			.rx_buf = (unsigned long)rx,
			.len = sizeof(rx),
			.delay_usecs = delay,
			.speed_hz = speed,
			.bits_per_word = bits,
		}
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(2), tr);
	if (ret < 1)
		pabort("can't send spi message");

	for (ret = 0; ret < sizeof(tx); ret++) {
		if (!(ret % 6))
			puts("");
		printf("%.2X ", rx[ret]);
	}
	puts("");
}

int main(void) {
	int fd = -1;	// SPI file descriptor
	int ret = -1;	// Function return codes.

	fd = open(DEVICE, O_RDWR);
	if (fd < 0) {
		pabort("can't open device");
	}

	mode |= SPI_CPOL | SPI_CPHA;	//Mode 3

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
		pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");

	transfer(fd);
}
