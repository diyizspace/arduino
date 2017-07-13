#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

const int backlightPin = 7;
boolean configMode = true;
int currentMenu = 0;
int const menuLength = 10;
int menus[menuLength];
String menuTitles[] = {"Brightness", "Delay", "Duration", "Menu3", "Menu4", "Menu5", "Menu6", "Menu7", "Menu8", "Menu9"};
float f = 0.00f;

void setup() {
  pinMode(backlightPin, OUTPUT);
  lcd.begin();
  for (int i = 0; i < menuLength; i = i + 1) {
    EEPROM.get(i, menus[i]);
  }
  lcd.setContrast(60);
  show("DIYIZ.COM", 1, "CAMERA FLASH", 1);
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
  int input = key();
  if (input == 17) {
    switchMode();
  }
  if (configMode) {
    if (input == 1) {
      if (currentMenu > 0) {
        currentMenu -= 1;
      }
    }
    if (input == 2) {
      if (currentMenu < 9) {
        currentMenu += 1;
      }
    }
    if ( input == 5) {
      menus[currentMenu] += 1;
    }
    if ( input == 9) {
      menus[currentMenu] -= 1;
    }
    show(String(menuTitles[currentMenu]), 1, String(menus[currentMenu]), 1);
    delay(100);
    return;
  }
  show("Mode:", 1, "Ready", 1);
}

int key() {
  int up = digitalRead(10);
  int down = digitalRead(16) * 2;
  int left = digitalRead(14) * 5;
  int right = digitalRead(15) * 9;
  return up + down + left + right;
}

void switchMode() {
  if (configMode) {
    configMode = false;
    for (int i = 0; i < menuLength; i = i + 1) {
      EEPROM.put(i, menus[i]);
    }
    show("Exiting ... ", 1, "config mode", 1);
    delay(2000);
    return;
  }
  show("Entering ... ", 1, "config mode", 1);
  delay(2000);
  configMode = true;
}

void reset() {
  String msg = "...";
  for (int i = 0; i < 10; i++) {
    msg += ".";
    show("Restart", 1, msg, 1);
    delay(250);
  }
  asm volatile ( "jmp 0");
}
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

