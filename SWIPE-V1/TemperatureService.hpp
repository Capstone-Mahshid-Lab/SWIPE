#ifndef TemperatureService_HPP
#define TemperatureService_HPP

#include "ad5940.h"
#include <stdio.h>
#include "string.h"
#include <Arduino.h>

#define SINC3OSR_SEL  ADCSINC3OSR_4
#define SINC2OSR_SEL  ADCSINC2OSR_22
#define MEASURE_FREQ	4.0f	//4Hz(4SPS)
#define FIFO_THRESHOLD	4		//generate FIFO threshold interrupt every 4 data.

#define BUFF_SIZE 128

static int32_t AD5940PlatformCfg(void);
void _ad5940_analog_init(void);
void AD5940_TemperatureInit(void);
void AD5940_TemperatureISR(void);
void AD5940_PrintResult(void);

void initTemperature(void);

void getTemperature(void);

#endif