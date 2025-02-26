#include "SPITest.hpp"
#include "ESP32Port.hpp"
#include "AD5940Main.h"
//#include "TemperatureService.hpp"

#define INT_PIN 17
#define BLE_LED 21

volatile static uint8_t ucInterrupted = 0;       /* Flag to indicate interrupt occurred */

void handleISR() {
  ucInterrupted = 1;
}

uint32_t  AD5940_GetMCUIntFlag(void) {
  return ucInterrupted;
}

uint32_t  AD5940_ClrMCUIntFlag(void) {
  ucInterrupted = 0;
	return 1;
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(INT_PIN), handleISR, FALLING);
  pinMode(BLE_LED, OUTPUT);
  digitalWrite(BLE_LED, LOW);
  Serial.begin(115200);
  Serial.println("running setup");
  init_ESP32_SPI();
  delay(3000);
  Serial.println("2s");
  delay(2000);
  digitalWrite(BLE_LED, HIGH);
  delay(500);
  AD5940_Main();
  digitalWrite(BLE_LED, LOW);
  delay(500);
}

void loop() {
  //Serial.println("hello from arduino");
  //SPI_LoopbackTest();
  // runSpiTest();
  //getTemperature();
}
