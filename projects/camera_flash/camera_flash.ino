//#include <EEPROM.h>
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

    void handle(String input) {
      if (input == "0010") {
        int new_value = value - step_value;
        if (new_value <= min_value) {
          value = min_value;
        } else {
          value = new_value;
        }
      } else if (input == "0001") {
        int new_value = value + step_value;
        if (new_value >= max_value) {
          value = max_value;
        } else {
          value = new_value;
        }
      }
    };


    String get_title() {
      return title;
    };

    int get_value() {
      return value;
    };

    String get_value_as_string() {
      return String(value);
    }
};

class Menus {
    enum Mode {CONFIG = 0, READY = 1} mode;
    byte pin_up;
    byte pin_down;
    byte pin_left;
    byte pin_right;
    int current_menu = 0;
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
      if (get_input() == "1111") {
        mode = READY;
      } else {
        mode = CONFIG;
      }
      menu_length = 4;
      menus[0] = Menu("Brightness", 150, 150, 100, 255, 5);
      menus[1] = Menu("Pre-delay", 0, 0, 0, 1000, 50);
      menus[2] = Menu("Duration", 250, 250, 125, 1000, 125);
      menus[3] = Menu("LCD brightness", 60, 60, 40, 70, 5);
    };

    Menu get_current_menu () {
      return menus[current_menu]  ;
    };
    void handle() {
      String input = get_input();
      if (input == "1000") {
        if (current_menu > 0) {
          current_menu -= 1;
        }
      } else if (input == "0100") {
        if (current_menu < menu_length - 1) {
          current_menu += 1;
        }
      } else {
        menus[current_menu].handle(input);
      }
      delay(50);
    };

    String get_input() {
      return String(digitalRead(pin_up) + digitalRead(pin_down) + digitalRead(pin_left) + digitalRead(pin_right));
    };

    boolean is_config_mode() {
      return mode == CONFIG;
    };
};
Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

Menus menus = Menus(10, 16, 15, 14);


void setup() {
  lcd.begin();
  lcd.setContrast(60);
  show("DIYIZ FLASH", 1, "BOOTING ...", 1);
  Serial.begin(9600);
  Serial.println("Start...");
  menus.setup();
  delay(1000);
}

void loop() {
  if (menus.is_config_mode()) {
    menus.handle();
    Menu m = menus.get_current_menu();
    show(m.get_title(), 1, m.get_value_as_string(), 1);
  } else {
    show("Stand by", 1, "...", 1);
    Serial.println("standby");
    delay(1000);
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

