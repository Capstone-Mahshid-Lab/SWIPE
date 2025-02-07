#include "SPITest.hpp"
#include "ESP32Port.hpp"
//#include "TemperatureService.hpp"
#include "CVService.hpp"

void setup() {
  Serial.begin(115200);
  Serial.println("running setup");
  init_ESP32();//init peripherals
  delay(3000);
}

void loop() {
  Serial.println("hello from arduino");
  //SPI_LoopbackTest();
  //runSpiTest();
  runCV();
  digitalWrite(BLE_LED, HIGH);
  delay(500);
  digitalWrite(BLE_LED, LOW);
  delay(500);
}
