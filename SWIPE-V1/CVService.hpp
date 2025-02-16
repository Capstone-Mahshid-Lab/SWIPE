#ifndef CVService_HPP
#define CVService_HPP

#include "ad5940.h"
#include <stdio.h>
#include "string.h"
#include <Arduino.h>
#include "ESP32Port.hpp"

extern "C" {
#include "RampTest.h"
}


#define APPBUFF_SIZE 1024
#define NB_SAMPLES 256 //maximum without ping pong is 256 steps for 4KB (256*4 commands * 4 Bytes/command=4KB)
//more data can be sent but it requires INT0 + ping pong

void runCV(void);

#endif