#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

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

    void descrease() {
      int new_value = value - step_value;
      if (new_value <= min_value) {
        value = min_value;
      } else {
        value = new_value;
      }
    }
    void increase() {
      int new_value = value + step_value;
      if (new_value >= max_value) {
        value = max_value;
      } else {
        value = new_value;
      }
    }

    String get_title() {
      return title;
    }

    void set_value(int _value) {
      value = _value;
    }

    int get_value() {
      return value;
    }

    String get_value_as_string() {
      return String(value);
    }
};

class Menus {
    int current_index = 0;
    int menu_length = 5;
    Menu menus[5] = {
      Menu("Pre-delay", 0, 0, 0, 1000, 50),
      Menu("Flash level", 150, 150, 100, 255, 10),
      Menu("Duration", 250, 250, 100, 1000, 50),
      Menu("Photo censored", 0, 0, 0, 1, 1),
      Menu("Lcd back light", 0, 0, 0, 1, 1)
    };

  public:
    void setup() {
      for (int i = 1; i <= menu_length; i++) {
        int value = EEPROM.read(i);
        if (value > 0) {
          menus[i].set_value(value);
        }
      }
    }

    void save() {
      for (int i = 1; i <= menu_length; i++) {
        EEPROM.write(i, menus[i].get_value());
        delay(10);
      }
    }

    void handle(int input) {
      if (input == 8) {
        previous_menu();
      } else if (input == 4) {
        next_menu();
      } else if (input == 2) {
        menus[current_index].descrease();
      } else if (input == 1) {
        menus[current_index].increase();
      }
    }

    Menu get_menu(int position) {
      return menus[position]  ;
    }

    Menu get_current_menu() {
      return get_menu(current_index);
    }

    int get_current_index() {
      return current_index;
    }

    void previous_menu() {
      current_index -= 1;
      if (current_index < 0) {
        current_index = menu_length - 1;
      }
    }

    void next_menu() {
      current_index += 1;
      if (current_index >= menu_length) {
        current_index = 0;
      }
    }
};
Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

Menus menus;

const byte PIN_FLASH = 10;
const byte PIN_FLASH_TRIGER = 16;
const byte PIN_UP = 15;
const byte PIN_DOWN = 14;
const byte PIN_LEFT = 8;
const byte PIN_RIGHT = 7;
const byte PIN_LCD_BACK_LED = 9;
const byte PIN_PHOTO_SENSOR = 18;

void setup() {
  lcd.begin();
  lcd.setContrast(50);
  show("diyiz.space", "led flashlight", "starting...", "");
  menus.setup();
  delay(500);
}

void loop() {
  if (digitalRead(PIN_FLASH_TRIGER) == LOW) {
    show("Flash fired...", menus.get_menu(0).get_value_as_string(), menus.get_menu(1).get_value_as_string(), menus.get_menu(2).get_value_as_string());
    delay(menus.get_menu(0).get_value());
    analogWrite(PIN_FLASH, menus.get_menu(1).get_value());
    delay(menus.get_menu(2).get_value());
    analogWrite(PIN_FLASH, LOW);
    doMenu(-1);
    return;
  }
  doMenu(8 * digitalRead(PIN_UP) + 4 * digitalRead(PIN_DOWN) + 2 * digitalRead(PIN_LEFT) + digitalRead(PIN_RIGHT));
  delay(1);
}

void doMenu(byte input) {
  menus.handle(input);
  Menu m = menus.get_current_menu();
  show(m.get_title(), m.get_value_as_string(), "", "");
  delay(200);
}

void show(String line1, String line2, String line3, String line4) {
  lcd.clearDisplay();
  lcd.setTextColor(BLACK);
  lcd.setTextSize(1);
  lcd.setCursor(0, 0);
  lcd.println(line1);
  lcd.println(line2);
  lcd.println(line3);
  lcd.println(line4);
  lcd.display();
}

