<<<<<<< HEAD
int pinFaster = 0;
int pinSlower = 1;
int pinStart = 2;
int pinBldcClock = 3;

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
=======
// pin setup
int PIN_START = 2;
int PIN_CLOCK = 3;
int PIN_LEFT = 4;
int PIN_RIGHT = 5;
int PIN_UP = 6;
int PIN_DOWN = 7;
int PIN_TEMPERATURE = A6;
int pwm = 200;

void setup() {
  //change timer2 frequency to 980.39Hz
  TCCR2B = (TCCR2B & 0b11111000) | 0x03;
  pinMode(PIN_START, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  pinMode(PIN_UP, INPUT);
  pinMode(PIN_DOWN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int old_pwm = pwm;
  int input = getInput();
  calculatePwm(input);
  if (pwm != old_pwm) {
    analogWrite(PIN_START, HIGH);
    delay(10);
    digitalWrite(PIN_START, LOW);
    delay(10);
    analogWrite(PIN_START, HIGH);
    delay(10);
    digitalWrite(PIN_START, LOW);
  }
  Serial.println(pwm);
  analogWrite(PIN_CLOCK, pwm);
}

int calculatePwm(int input) {
  if (input == 5) {
    pwm = pwm + 10;
  }
  if (input == 9) {
    pwm = pwm - 10;
  }
  if (pwm > 255) {
    pwm = 255;
>>>>>>> update
  }

<<<<<<< HEAD
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

=======
int getInput() {
  int left = digitalRead(PIN_LEFT);
  int right = digitalRead(PIN_RIGHT) * 2;
  int up = digitalRead(PIN_UP) * 5;
  int down = digitalRead(PIN_DOWN) * 9;
  return up + down + left + right;
}
>>>>>>> update
