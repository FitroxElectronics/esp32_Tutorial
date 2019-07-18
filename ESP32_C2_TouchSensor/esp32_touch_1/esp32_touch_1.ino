// esp32 chapter2 exm.1
// built in touch sensor monitor

void setup()
{
  // intitialize serial monitor
  Serial.begin(115200);
  delay(1000);
}
void loop()
{
  Serial.println(touchRead(T0));    // read touch0 status
  delay(10);
}
