int pinFaster = 0;
int pinSlower = 1;
int pinBldcClock = 2;
int pinStart = 3;

int t = 100;
int f = 1800;
int s = 0;
int e = 30000;
void setup() {
  pinMode(pinBldcClock, OUTPUT);
  pinMode(pinStart, OUTPUT);
}

void loop() {
  if (s < e && s % 1000 == 0) {
    digitalWrite(pinStart, HIGH);
  }

  digitalWrite(pinBldcClock, HIGH);
  delayMicroseconds(t);

  if (s < e && s % 500 == 0) {
    digitalWrite(pinStart, LOW);
    s++;
  }

  digitalWrite(pinBldcClock, LOW);
  delayMicroseconds(f - t);

  if (digitalRead(pinFaster)) {
    f = f + 100;
    if (f > 2200) {
      f = 2200;
    }
    s = 0;
    delay(1000);
  }

  if (digitalRead(pinSlower)) {
    f = f - 100;
    if (f < 900) {
      f = 800;
    }
    s = 0;
    delay(1000);
  }
}

