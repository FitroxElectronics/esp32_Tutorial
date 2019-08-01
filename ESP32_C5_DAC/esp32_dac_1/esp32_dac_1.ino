// esp32 chapter5 exm.1
// built in DAC

// กำหนด Pin ที่จะใช้ ใช้ GPIO25 ตั้งชื่อว่า DAC1
#define DAC1 25

// กำหนดตัวแปร
int dacOut = 0;
int dacAmount = 5;

void setup() {
  // เริ่ม Serial monitor
  Serial.begin(115200);
}

void loop() {
  // แสดงค่า dacOut ทาง Serial monitor
  Serial.println(dacOut);
  
  // DAC มีค่าเท่ากับค่า dacOut ส่งค่าออกที่ขา DAC1 (GPIO25)
  dacWrite(DAC1, dacOut);

  // เพิ่มค่าของ dacOut
  dacOut = dacOut + dacAmount;
  // ตรวจสอบค่าให้อยู่ระหว่าง 0-255
  if(dacOut <=0 || dacOut >= 255){
    dacAmount = -dacAmount;
  }
  // หน่วงเวลาสักครู่เพื่อให้เห็นการเปลี่ยนแปลงชัดเจน
    delay(50);
}
