// esp32 chapter3 exm.3
// built in temperature sensor & ThingSpeak

#include <WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// ตั้งค่า WiFi ให้แทนด้วย SSID และ Password ของท่านเอง
const char* ssid = "xxxxxx";
const char* password = "xxxxxx";

WiFiClient client;

// ให้แทนด้วย Channel และ API ของตัวเอง
unsigned long chNumber = xxxxxx;
const char* writeKey = "AAAA1234567890";

#ifdef __cplusplus
  extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();
uint8_t inTemp;


void setup() {
  // เริ่ม serial monitor
  Serial.begin(115200);
  
// เชื่อมต่อกับ WiFi
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
// รอจนกว่าจะเชื่อมต่อสำเร็จ
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }
// แสดงสถานะเมื่อเชื่อมต่อสำเร็จ
  Serial.println("");  
  Serial.println("WiFi connected");

  ThingSpeak.begin(client);
}

void loop() {
  // อ่านค่าอุณหภูมิภายในโดยใช้ built-in sensor ในหน่วย C
  inTemp = ((temprature_sens_read() - 32) / 1.8);
  
  // แสดงค่าทาง serial monitor
  Serial.print("Internal Temp. : ");
  Serial.print(inTemp);
  Serial.println(" C");

  // ส่งค่าไปที่ Thingspeak
   ThingSpeak.writeField(chNumber, 1, inTemp, writeKey); 
   delay(50);
   Serial.println("Successful Update Data to ThingSpeak");
  
  // หน่างเวลา 1/2 นาที (30 วินาที * 1000 = 30000 มิลลิวินาที)
  delay(30000);
}
