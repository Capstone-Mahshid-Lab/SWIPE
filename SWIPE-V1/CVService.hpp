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

void runCV(void);

#endif