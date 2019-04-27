/*
 * lsm9ds1.c
 *
 *  Created on: Apr 27, 2019
 *      Author: christopher
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

#define DEVICE "/dev/spidev0.0"

static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed = 15000000;	//TODO Why is this not the correct speed in MHZ? This about 9.09 MHZ
static uint16_t delay = 0;
