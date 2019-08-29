// esp32 chaapter9
// esp32 bluetooth serial 2

#include <BluetoothSerial.h>

#define CH1 13
#define CH2 12
#define CH3 14
#define CH4 27

int incoming;                     // ตัวแปรเก็บค่าข้อมูลที่อ่านได้ากบลูทูธ
BluetoothSerial ESP32BT;

void setup() {
  Serial.begin(115200);           // เริ่ม Serial monitor
  ESP32BT.begin("ESP32_CONTROL");   // เริ่มการทำงานของบลูทูธ ให้ชื่อ ESP32_MyLED
  // แสดงข้อความพร้อมสำหรับการจับคู่บลูทูธ
  Serial.println("Bluetooth device is ready to pair");
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);
  pinMode(CH4, OUTPUT);
  // ให้ปิด Relay โดยเป็นสถานะ HIGH (รีเลย์ Active low)
  digitalWrite(CH1, HIGH);
  digitalWrite(CH2, HIGH);
  digitalWrite(CH3, HIGH);
  digitalWrite(CH4, HIGH);
}

void loop() {
  // ถ้าได้รับข้อมูลอะไรก็ตามทางบลูทูธ
  if(ESP32BT.available()){
    incoming = ESP32BT.read();    // อ่านค่าว่าค่าที่เข้ามาคืออะไร
    // เลข 1 ASCII = 49
    if(incoming == 49){
      digitalWrite(CH1, !(digitalRead(CH1)));
      Serial.println("CH1 Toggled");
      ESP32BT.println("CH1 Toggled");
    }
        // เลข 2 ASCII = 50
    if(incoming == 50){
      digitalWrite(CH2, !(digitalRead(CH2)));
      Serial.println("CH2 Toggled");
      ESP32BT.println("CH2 Toggled");
    }
        // เลข 3 ASCII = 51
    if(incoming == 51){
      digitalWrite(CH3, !(digitalRead(CH3)));
      Serial.println("CH3 Toggled");
      ESP32BT.println("CH3 Toggled");
    }
        // เลข 4 ASCII = 52
    if(incoming == 52){
      digitalWrite(CH4, !(digitalRead(CH4)));
      Serial.println("CH4 Toggled");
      ESP32BT.println("CH4 Toggled");
    }
  }
}
