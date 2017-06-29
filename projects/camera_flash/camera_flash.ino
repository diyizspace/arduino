#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

const int backlightPin = 7;
boolean configMode = true;

void setup() {
  pinMode(backlightPin, OUTPUT);
  lcd.begin();
int contrast = 60;

  lcd.setContrast(contrast);
  
boolean backlight = true;
  if (backlight) {
    backlight = false;
    digitalWrite(backlightPin, 0);
  } else {
    backlight = true;
    digitalWrite(backlightPin, 200);
  }

  show("DIYIZ.COM", 2, "CAMERA FLASH", 2);
  delay(1000);
}

void show(String line1, int font1, String line2, int font2) {
  lcd.clearDisplay();
  lcd.setTextColor(BLACK);
  lcd.setTextSize(font1);
  lcd.setCursor(0, 0);
  lcd.println(line1);
  lcd.setTextSize(font2);
  lcd.println(line2);
  lcd.display();
}

void loop() {
  if (configMode) {
    int input = key();
    show("Change:", 2, String(input), 2);
    delay(200);
  } else {
    show("Mode:", 2, "Ready", 2);
  }
}

int key() {
  int up = digitalRead(10);
  int down = digitalRead(16) * 2;
  int left = digitalRead(14) * 5;
  int right = digitalRead(15) * 9;
  return up + down + left + right;
}

//int eeAddress = 0;
//EEPROM.put(eeAddress, f);
//EEPROM.get(eeAddress, f);


//int photoCellPin = A6;
//int cameraFlashSignalPin = A7;
//int flashTrigerPin = 10;
//
//void setup() {
//  pinMode(flashTrigerPin, OUTPUT);
//}
//
//void loop() {
//  int cameraFlashSignalValue = analogRead(cameraFlashSignalPin);
//  if(cameraFlashSignalValue > 600) {
//    analogWrite(flashTrigerPin, 240);
//    delay(500);
//  }
//  delay(5);
//}

