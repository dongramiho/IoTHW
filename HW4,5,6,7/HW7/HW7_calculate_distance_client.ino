// BLE Client Code (HW7 Client)
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define SERVER_NAME "ESP32-BLE-Server"
int txPower = -57;     // RSSI at 1 meter (환경에 맞게 조정)
float n = 2.0;          // Path-loss exponent

float estimateDistance(int rssi) {
  return pow(10.0, ((float)(txPower - rssi)) / (10.0 * n));
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveName() && advertisedDevice.getName() == SERVER_NAME) {
      int rssi = advertisedDevice.getRSSI();
      float distance = estimateDistance(rssi);
      Serial.print("RSSI: ");
      Serial.print(rssi);
      Serial.print(" dBm → Estimated Distance: ");
      Serial.print(distance, 2);
      Serial.println(" meters");
    }
  }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("");

  BLEScan* pScan = BLEDevice::getScan();
  pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pScan->setActiveScan(true);
  Serial.println("Scanning for BLE server...");
}

void loop() {
  BLEScan* pScan = BLEDevice::getScan();
  pScan->start(5, false);  // Scan for 5 seconds
  delay(1000);
}
