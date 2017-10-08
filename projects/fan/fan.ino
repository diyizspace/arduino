// pin setup
int PIN_START = 2;
int PIN_CLOCK = 3;
int PIN_LEFT = 4;
int PIN_RIGHT = 5;
int PIN_UP = 6;
int PIN_DOWN = 7;
int PIN_TEMPERATURE = A6;
int pwm = 20;

void setup() {
  //change timer2 frequency to 980.39Hz
  TCCR2B = (TCCR2B & 0b11111000) | 0x04;
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
  }
  Serial.println(pwm);
  analogWrite(PIN_CLOCK, pwm);
  if (input > 0) {
    delay(150);
  } else {
    delay(10);
  }
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
  }
  if (pwm < 0) {
    pwm = 30;
  }
}

int getInput() {
  int left = digitalRead(PIN_LEFT);
  int right = digitalRead(PIN_RIGHT) * 2;
  int up = digitalRead(PIN_UP) * 5;
  int down = digitalRead(PIN_DOWN) * 9;
  return up + down + left + right;
}



//#define ONE_WIRE_BUS 8

//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);

//Init temperature DS18B20 sensor
//  sensors.begin();
//  sensors.requestTemperatures();
//  int temperature = (int)sensors.getTempCByIndex(0);
