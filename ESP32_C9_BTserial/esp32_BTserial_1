// esp32 chaapter9
// esp32 bluetooth serial

#include <BluetoothSerial.h>

#define LED 2                     // Built in LED อยู่ที่ GPIO2
int incoming;                     // ตัวแปรเก็บค่าข้อมูลที่อ่านได้ากบลูทูธ
BluetoothSerial ESP32BT;

void setup() {
  Serial.begin(115200);           // เริ่ม Serial monitor
  ESP32BT.begin("ESP32_MyLED");   // เริ่มการทำงานของบลูทูธ ให้ชื่อ ESP32_MyLED
  // แสดงข้อความพร้อมสำหรับการจับคู่บลูทูธ
  Serial.println("Bluetooth device is ready to pair");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);         // ให้ LED ดับไว้ก่อน
}

void loop() {
  // ถ้าได้รับข้อมูลอะไรก็ตามทางบลูทูธ
  if(ESP32BT.available()){
    incoming = ESP32BT.read();    // อ่านค่าว่าค่าที่เข้ามาคืออะไร
    // ถ้าข้อมูลที่เข้ามาคือ ASCII รหัส 49 (เลข 1) ให้กลับสถานะ LED 
    // และแสดงทาง Serial monitor, Bluetooth
    if(incoming == 49){
      digitalWrite(LED, !(digitalRead(LED)));
      Serial.println("LED Toggled");
      ESP32BT.println("LED Toggled");
    }
  }
}
