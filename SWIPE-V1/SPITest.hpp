#ifndef SPITest_HPP
#define SPITest_HPP


#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "ad5940.h"
#include <Arduino.h>


static int32_t AD5940PlatformCfg2(void);
void _ad5940_analog_init2(void);
void runSpiTest(void);
void SPI_RW_TEMPERATURE(void);
void SPI_RW_REG(void);

#endif