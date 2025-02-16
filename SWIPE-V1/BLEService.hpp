#ifndef BLEService_HPP
#define BLEService_HPP

#include <stdio.h>
#include "string.h"
#include <Arduino.h>
#include "ESP32Port.hpp"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

class BLEHandler {
    public:
        BLEHandler();
        void begin(); // Initializes BLE service
    
    private:
        BLEServer *pServer;
        BLEService *pService;
        BLECharacteristic *pCharacteristic;
        uint8_t mockData[1024];
    
        class MyCallbacks : public BLECharacteristicCallbacks {
        public:
            MyCallbacks(uint8_t *buffer, size_t size);
            void onRead(BLECharacteristic *pCharacteristic) override;
        
        private:
            uint8_t *dataBuffer;
            size_t bufferSize;
        };
    };

#endif