// esp32 chapter2 exm.3
// built in touch sensor

void setup() {
  // intitialize serial monitor
  Serial.begin(115200);
  
  // Touch Interrupt ที่ขา T0
  // เรียกใช้ฟังก์ชั่นชื่อ getTouch
  // ให้เกิด Interrupt เมื่อ FALLING (เปลี่ยนสถานะจาก HIGH เป็น LOW)
  touchAttachInterrupt(T0, getTouch, FALLING);
}

void loop() {
  Serial.println(touchRead(T0));    // อ่านค่าจาก touch0 แล้วแสดงออกทาง Serial Monitor
  delay(500);
}

// ฟังก์ชั่น getTouch ที่จะเรียกใช้งาน
void getTouch(){
  Serial.println("Hey...You touch me !!!");    // แสดงค่าว่ามีการสัมผัส
}
