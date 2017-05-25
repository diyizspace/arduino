int photoCellPin = A6;
int cameraFlashSignalPin = A7;
int flashTrigerPin = 10;

void setup() {
  pinMode(flashTrigerPin, OUTPUT);
}

void loop() {
  int cameraFlashSignalValue = analogRead(cameraFlashSignalPin);
  if(cameraFlashSignalValue > 600) {
    analogWrite(flashTrigerPin, 240);
    delay(500);
  }
  delay(5);
}
