#include "SPITest.hpp"
#include "ESP32Port.hpp"
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
  // put your setup code here, to run once:
  //attachInterrupt(digitalPinToInterrupt(INT_PIN), handleISR, CHANGE);
  pinMode(BLE_LED, OUTPUT);
  digitalWrite(BLE_LED, LOW);
  Serial.begin(115200);
  Serial.println("running setup");
  init_ESP32_SPI();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("hello from arduino");
  //ReadDeviceID();
  //SPI_LoopbackTest();
  runSpiTest();
  //getTemperature();
  //AD5940_HWReset();
  digitalWrite(BLE_LED, HIGH);
  delay(500);
  digitalWrite(BLE_LED, LOW);
  delay(500);
}