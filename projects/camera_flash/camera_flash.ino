//#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

class Menu {
    String title;
    int value;
    int default_value;
    int min_value;
    int max_value;
    int step_value;

  public:
    Menu(String _title, int _value, int _default_value, int _min_value, int _max_value, int _step_value) {
      title = _title;
      value = _value;
      default_value = _default_value;
      min_value = _min_value;
      max_value = _max_value;
      step_value = _step_value;
    };
};

class Menus {
    byte pin_up;
    byte pin_down;
    byte pin_left;
    byte pin_right;
    int menu_length;
    Menu menus[];
  public:
    Menus(byte _pin_up, byte _pin_down, byte _pin_left, byte _pin_right) {
      pin_up = _pin_up;
      pin_down = _pin_down;
      pin_left = _pin_left;
      pin_right = _pin_right;
    };
    void setup() {
      menu_length = 4;
      menus[0] = Menu("Brightness", 150, 150, 100, 255, 5);
      menus[1] = Menu("Pre-delay", 0, 0, 0, 1000, 50);
      menus[2] = Menu("Duration", 250, 250, 125, 1000, 125);
      menus[3] = Menu("LCD brightness", 60, 60, 40, 70, 5);
    };
    void handle() {
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
    String input() {
      return String(digitalRead(pin_up) + digitalRead(pin_down) + digitalRead(pin_left) + digitalRead(pin_right));
    }
};

boolean configMode = false;

void setup() {
  lcd.begin();
  lcd.setContrast(60);

  show("DIY LED FLASH", 1, "BOOTING ...", 1);
  delay(1000);
}

void loop() {
  if (configMode) {
    show("", 1, "", 1);
    return;
  }
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

