#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

const int backlightPin = 7;
boolean configMode = true;
int buttonValue;
int lastButtonValue = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int currentMenu = 0;
int const menuLength = 4;
int menus[menuLength];
String menuTitles[] = {"Flash level", "Delay", "Use photocell", "LCD brightness"};
int menuStep[] = {10, 10, 1, 5};
int defaults[] = {200, 250, 0, 60};


float f = 0.00f;

int photoCellPin = A2;
int cameraFlashSignalPin = A0;
int flashTrigerPin = 8;


void setup() {
  pinMode(flashTrigerPin, OUTPUT);
  pinMode(backlightPin, OUTPUT);
  lcd.begin();
  for (int i = 1; i <= menuLength; i = i + 1) {
    EEPROM.put(i, defaults[i]);
  }
  for (int i = 1; i <= menuLength; i = i + 1) {
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
    doConfig(input);
  } else {
    doFlash();
  }
}
void doFlash() {
  if (analogRead(cameraFlashSignalPin) > 600) {
    show("Flashing triggered", 1, "...", 1);
    analogWrite(flashTrigerPin, menus[0]);
    delay(menus[1]);
    show("Standby", 1, "...", 1);
  }
}
void doConfig(int input) {
  if (input != lastButtonValue) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    return;
  }
  lastButtonValue = input;
  if (input == 1) {
    if (currentMenu > 0) {
      currentMenu -= 1;
    }
  }
  if (input == 2) {
    if (currentMenu < menuLength) {
      currentMenu += 1;
    }
  }
  if ( input == 5) {
    menus[currentMenu] += menuStep[currentMenu];
  }
  if ( input == 9) {
    menus[currentMenu] -= menuStep[currentMenu];
  }
  show(String(menuTitles[currentMenu]), 1, String(menus[currentMenu]), 1);
  delay(50);
}

int key() {
  int up = digitalRead(10);
  int down = digitalRead(16) * 2;
  int left = digitalRead(15) * 5;
  int right = digitalRead(14) * 9;
  return up + down + left + right;
}

void switchMode() {
  if (configMode) {
    configMode = false;
    for (int i = 1; i <= menuLength; i = i + 1) {
      EEPROM.put(i, menus[i]);
    }
    show("Exiting ... ", 1, "config mode", 1);
    delay(1000);
    return;
  }
  show("Entering ... ", 1, "config mode", 1);
  delay(1000);
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
