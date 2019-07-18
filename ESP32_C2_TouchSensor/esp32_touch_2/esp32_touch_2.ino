// esp32 chapter2 exm.2
// built in touch sensor monitor

int LED = 2;          // LED บนบอร์ดพ่วงอยู่กับ GPIO2
int touchValue = 0;   // ตัวแปลเพื่อเก็บค่าที่อ่านได้จาก touch sensor

void setup(){
  // intitialize serial monitor
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  digitalWrite(LED, LOW);
}

void loop(){
  touchValue = touchRead(T0);    // อ่านค่า touch0 เก็บไว้ในตัวแปร touchValue 
  Serial.println(touchValue);
  if(touchValue < 20){           // ค่า touchValue น้อยกว่า 30 แสดงว่ามีการสัมผัส ให้ LED ติด
    digitalWrite(LED, HIGH);    
  }
  else{                          // กรณีอื่นๆ ให้ LED ดับ
    digitalWrite(LED, LOW);
  }
  delay(5);
}
