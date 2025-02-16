#include "BLEService.hpp"

BLEHandler::BLEHandler() {
    // Initialize mock data buffer
    for (int i = 0; i < sizeof(mockData); i++) {
        mockData[i] = i % 256;
    }
}

void BLEHandler::begin() {
    // Initialize BLE
    BLEDevice::init("ESP32_BLE");
    pServer = BLEDevice::createServer();
    pService = pServer->createService(SERVICE_UUID);

    // Create a characteristic
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ
    );

    // Set callback to send data synchronously on read
    pCharacteristic->setCallbacks(new MyCallbacks(mockData, sizeof(mockData)));

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    BLEDevice::startAdvertising();
}

// Constructor for MyCallbacks
BLEHandler::MyCallbacks::MyCallbacks(uint8_t *buffer, size_t size) {
    dataBuffer = buffer;
    bufferSize = size;
}

// Callback for when a client reads the characteristic
void BLEHandler::MyCallbacks::onRead(BLECharacteristic *pCharacteristic) {
    pCharacteristic->setValue(dataBuffer, bufferSize);
}
