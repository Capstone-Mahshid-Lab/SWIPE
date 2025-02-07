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

#define INT_PIN_GPIO0 17
#define INT_PIN_GPIO1 16

#define BLE_LED 21

static const int spiClk = 1000000;  // 1 MHz

void init_ESP32(void);
void init_ESP32_SPI(void);
void toggleLED(void);
void handleISR(void);
uint32_t  AD5940_GetMCUIntFlag(void);
uint32_t  AD5940_ClrMCUIntFlag(void);


void SPI_LoopbackTest(void);

#endif

