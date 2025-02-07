#include "SPITest.hpp"
#include "ESP32Port.hpp"
//#include "TemperatureService.hpp"
#include "CVService.hpp"

void setup() {
  init_ESP32();//init peripherals
}

void loop() {
  Serial.println("hello from arduino");
  //SPI_LoopbackTest();
  //runSpiTest();
  runCV();
  toggleLED();
}
