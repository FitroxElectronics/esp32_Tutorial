// esp32 chapter6 exm.2
// Basic Over-The-Air

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// เปลี่ยนเป็น SSID และ PASSWORD ของตัวเอง
const char* ssid = "xxxxxx";
const char* password = "xxxxxx";

// กำหนด LED = GPIO2 (ใช้ Built-in LED)
int LED = 2;

void setup() {
  Serial.begin(115200);

  // ส่วนของ WiFi
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // หากเชื่อมต่อไม่สำเร็จ รอ 5 วินาทีแล้ว Restart ใหม่
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

// ส่วนของ OTA
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else          // แบบ U_SPIFFS
        type = "filesystem";
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
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

// กำหนด pinMode เหมือนเขียนโปรแกรมปกติ
  pinMode(LED, OUTPUT);
}

void loop() {
// ทำงาน ArduinoOTA ทุก Loop
  ArduinoOTA.handle();

// เขียนโปรแกรมปกติเพิ่มลงไป
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}
