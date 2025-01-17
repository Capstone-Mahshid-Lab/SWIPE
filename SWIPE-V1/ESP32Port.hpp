#ifndef ESP32Port_HPP
#define ESP32Port_HPP


#include <Arduino.h>
#include "ad5940.h"
#include "stdio.h"
#include <SPI.h>

#define VSPI_MISO 19 //GPIO number, no pin number
#define VSPI_MOSI 23
#define VSPI_SCLK 18
#define VSPI_SS   5 //chip select

#define AD_RST 25

static const int spiClk = 1000000;  // 1 MHz

void init_ESP32_SPI(void);

void SPI_LoopbackTest(void);
uint16_t ReadDeviceID(void);

#endif

