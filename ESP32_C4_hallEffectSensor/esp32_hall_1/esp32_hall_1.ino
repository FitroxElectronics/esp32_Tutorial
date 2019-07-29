int hall = 0;

void setup() {
  // เริ่ม Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // อ่านค่า Hall Effect
  hall = hallRead();
  // แสดงผลทาง Serial Monitor
  Serial.println(hall); 
  delay(1000);
}
