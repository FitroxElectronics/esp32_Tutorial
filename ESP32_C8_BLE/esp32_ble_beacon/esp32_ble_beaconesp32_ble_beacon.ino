// esp32 chapter8
// esp32 ble beacon

#include "BLEDevice.h"

#define LED 2

static BLEAddress *pServerAddress;
BLEScan* pBLEScan;
BLEClient*  pClient;
bool deviceFound = false;

String knownAddresses[] = { "เปลี่ยนเป็น MACAddress ที่เตรียมไว้"};
unsigned long entry;

// สร้างฟังก์ชั่น Callback เมื่ออุปกรณ์เชื่อมต่อ(จับสัญญาณได้)
static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
}

// สร้าง Class Callback เพื่อตรวจจับระยะของอุปกรณ์
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice Device){
      Serial.print("BLE Advertised Device found: ");
      Serial.println(Device.toString().c_str());
      pServerAddress = new BLEAddress(Device.getAddress());
// ให้ known = false
      bool known = false;
// ถ้าจับสัญญาณของอุปกรณ์ที่เรากำหนดไว้ได้ ให้ known = true
      for (int i = 0; i < (sizeof(knownAddresses) / sizeof(knownAddresses[0])); i++) {
        if (strcmp(pServerAddress->toString().c_str(), knownAddresses[i].c_str()) == 0) 
          known = true;
      }
// เมื่อ known = true ทำการเช็คค่า RSSI ถ้าถึงค่าที่กำหนด DeviceFound = true ถ้ายังไม่ถึง(เข้าใกล้ไม่พอ) DeviceFound = false
      if (known) {
        Serial.print("Device found: ");
        Serial.println(Device.getRSSI());
        // สามารถเปลี่ยนค่า RSSI ตรงนี้ได้ตามต้องการ
        if (Device.getRSSI() > -85) {
          deviceFound = true;
        }
        else {
          deviceFound = false;
        }
        Device.getScan()->stop();
        delay(100);
      }
    }
};

// ฟังก์ชั่นการทำงาน ถ้า DeviceFound = true ให้ LED เปิด และถ้า DeviceFound = false ให้ LED ปิด
void Working() {
  Serial.println();
  Serial.println("BLE Scan restarted.....");
  deviceFound = false;
  BLEScanResults scanResults = pBLEScan->start(5);
  if (deviceFound) {
    digitalWrite(LED, HIGH);
    delay(10000);
  }
  else{
    digitalWrite(LED, LOW);
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  BLEDevice::init("");
  pClient  = BLEDevice::createClient();
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  Serial.println("Done");
}

void loop() {
  // เรียกฟังก์ชั่น Working มาทำงาน
  Working();
}
