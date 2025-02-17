#include "SPITest.hpp"
#include "ESP32Port.hpp"
#include "AD5940Main.h"
//#include "TemperatureService.hpp"
#include "CVService.hpp"

void setup() {
  attachInterrupt(digitalPinToInterrupt(INT_PIN), handleISR, FALLING);
  pinMode(BLE_LED, OUTPUT);
  digitalWrite(BLE_LED, LOW);
  Serial.begin(115200);
  Serial.println("running setup");
  init_ESP32_SPI();
  delay(3000);
}

void loop() {
  Serial.println("hello from arduino");
  //SPI_LoopbackTest();
  // runSpiTest();
  //getTemperature();
  AD5940_Main();
  digitalWrite(BLE_LED, HIGH);
  delay(500);
  digitalWrite(BLE_LED, LOW);
  delay(500);
}
