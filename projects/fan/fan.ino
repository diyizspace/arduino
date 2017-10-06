void setup() {
  TCCR2B = (TCCR2B & 0b11111000) | 0x03;
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop() {
  analogWrite(3, 100);
  analogWrite(5, 250);
  analogWrite(11, 200);
}
