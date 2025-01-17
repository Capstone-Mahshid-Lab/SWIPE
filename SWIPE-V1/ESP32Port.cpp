#include "ESP32Port.hpp"

SPIClass *vspi = nullptr;

/* MCU specific funtions used by AD5940 lib
*/
void init_ESP32_SPI(void) {
  pinMode(VSPI_SS, OUTPUT);  //VSPI SS
  digitalWrite(VSPI_SS, HIGH);
  pinMode(AD_RST, OUTPUT);  //AD5940 reset pin (active low)
  digitalWrite(AD_RST, HIGH);
  vspi = new SPIClass(VSPI);
  vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  //SCLK, MISO, MOSI, SS
}


void AD5940_ReadWriteNBytes(unsigned char *pSendBuffer,unsigned char *pRecvBuff,unsigned long length) {
  //make a copy of Tx buffer to not override sent data
  //memcpy(pRecvBuff, pSendBuffer, length);

  //Transfer routine
  for (unsigned long i = 0; i < length; i++) {
      pRecvBuff[i] = vspi->transfer(pSendBuffer[i]); // Properly handle SPI transfer
  }
}

void AD5940_CsClr(void) { //Pulls down AD5940 CS pin
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0)); 
  digitalWrite(VSPI_SS, LOW);
}

void AD5940_CsSet(void) { //Pulls AD5940 CS high
  digitalWrite(VSPI_SS, HIGH);
  vspi->endTransaction();  
}

void AD5940_RstClr(void) { //AD5940 HW Reset
  digitalWrite(AD_RST, LOW);
}

void AD5940_RstSet(void) { //AD5940 Release Reset Button
  digitalWrite(AD_RST, HIGH);
}

void AD5940_Delay10us(uint32_t time) {
  delayMicroseconds(time/10);
}



void SPI_LoopbackTest(void) {
    uint8_t tx_buffer[3] = {0xA5, 0x5A, 0xFF};  // Test data
    uint8_t rx_buffer[3] = {0};

    vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(VSPI_SS, LOW);
    for (int i = 0; i < 3; i++) {
        rx_buffer[i] = vspi->transfer(tx_buffer[i]);
    }
    digitalWrite(VSPI_SS, HIGH);
    vspi->endTransaction();

    Serial.print("Sent: ");
    for (int i = 0; i < 3; i++) {
        Serial.print(tx_buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    Serial.print("Received: ");
    for (int i = 0; i < 3; i++) {
        Serial.print(rx_buffer[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}


uint16_t ReadDeviceID(void) {
    AD5940_HWReset();
    AD5940_CsClr();  // Pull CS low
    uint8_t cmd[2] = {0x00, 0x00};  // Replace with correct read command
    uint8_t response[2] = {0};
    vspi->transfer(cmd, 2);         // Send read command
    response[0] = vspi->transfer(0x00);  // Clock out response
    response[1] = vspi->transfer(0x00);  // Clock out response
    AD5940_CsSet();  // Pull CS high
    Serial.println((response[0] << 8) | response[1]);  // Combine bytes
}
