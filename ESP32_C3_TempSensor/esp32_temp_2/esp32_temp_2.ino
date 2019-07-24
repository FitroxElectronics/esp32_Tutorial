// esp32 chapter3 exm.2
// built in temperature sensor

#include <WiFi.h>

#ifdef __cplusplus
  extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

// เปลี้ยน xxxxxx เป็น SSID และ PASSWORD ของท่านเอง
const char* ssid     = "xxxxxx";
const char* password = "xxxxxx";

uint8_t temprature_sens_read();

void setup() {
  // เริ่ม serial monitor
  Serial.begin(115200);

  // เชื่อมต่อ WiFi
   WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected");
    delay(3000);
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(temprature_sens_read());               // อ่านค่าอุณหภูมิและแสดงเป็น F
  Serial.print(" F : ");
  Serial.print((temprature_sens_read() - 32) / 1.8);  // อ่านค่าอุณหภูมิและแสดงเป็น C โดยใช้สูตรคำนวณ C = (F-32)/1.8
  Serial.println(" C");
  delay(3000);
}
