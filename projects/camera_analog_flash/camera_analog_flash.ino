const byte PIN_SIGNAL = A2;
const byte PIN_DURATION = A3;
const byte PIN_TRIGER = 0;

void setup() {
  pinMode(PIN_SIGNAL, INPUT);
  pinMode(PIN_DURATION, INPUT);
  pinMode(PIN_TRIGER, OUTPUT);
}

void loop() {
  int signal = analogRead(PIN_SIGNAL);
  if (signal == 0) {
    analogWrite(PIN_TRIGER, 255);
    int duration = map(analogRead(PIN_DURATION), 0, 1023, 50, 1500);
    delay(duration);
    analogWrite(PIN_TRIGER, 0);
  }
}
