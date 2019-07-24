// esp32 chapter3 exm.1
// built in temperature sensor

#ifdef __cplusplus
  extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif


uint8_t temprature_sens_read();

void setup() {
  // เริ่ม serial monitor
  Serial.begin(115200);
}

void loop() {
  Serial.print("Temperature: ");
  Serial.print(temprature_sens_read());               // อ่านค่าอุณหภูมิและแสดงเป็น F
  Serial.print(" F : ");
  Serial.print((temprature_sens_read() - 32) / 1.8);  // อ่านค่าอุณหภูมิและแสดงเป็น C โดยใช้สูตรคำนวณ C = (F-32)/1.8
  Serial.println(" C");
  delay(3000);
}
