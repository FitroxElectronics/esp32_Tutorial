// esp32 chapter6 exm.1
// Basic Over-The-Air

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// เปลี่ยนเป็น SSID และ PASSWORD ของตัวเอง
const char* ssid = "xxxxxx";
const char* password = "xxxxxx";


void setup() {
  Serial.begin(115200);

  // เริ่มเชื่อมต่อกับ WiFi
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // หากเชื่อมต่อไม่สำเร็จ รอ 5 วินาทีแล้ว Restart ใหม่
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

// หากต้องการเพิ่มเติมคำสั่งอื่นๆ สามารถลบ Comment ออกได้
  // ตั้งค่าพอร์ตเป็นพอร์ต 3232
  // ArduinoOTA.setPort(3232);

  // ตั้งค่า Hostname เป็น esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");

  // ไม่มีการตรวจสอบความปลอดภัย
  // ArduinoOTA.setPassword("admin");

  // สามารถตั้งค่า Password ได้ (ใช้การเข้ารหัส MD5 ดีที่สุด)
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

// ส่วนของ OTA
  ArduinoOTA
    .onStart([]() {
      String type;          // ประเภทของ OTA ที่เข้ามา
      if (ArduinoOTA.getCommand() == U_FLASH)         // แบบ U_FLASH
        type = "sketch";
      else          // แบบ U_SPIFFS
        type = "filesystem";

      // NOTE: ถ้าใช้เป็นแบบ SPIFFS อาจใช้คำสั่ง SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })

    // เริ่มทำงาน (รับข้อมูลโปรแกรม) พร้อมแสดงความคืบหน้าทาง Serial Monitor
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })

    // แสดงข้อความต่างๆหากเกิด Error ขึ้น
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // ทำงาน ArduinoOTA (ทุก Loop การทำงาน พร้อมรับโปรแกรมใหม่ตลอดเวลา)
  ArduinoOTA.handle();
}
