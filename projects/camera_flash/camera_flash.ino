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

    int get_value() {
      return value;
    }

    String get_value_as_string() {
      return String(value);
    }
};

class Menus {
    enum Mode {CONFIG = 0, READY = 1} mode;
    int pin_up;
    int pin_down;
    int pin_left;
    int pin_right;
    int current_menu_index = 0;
    int menu_length = 4;
    Menu menus[4] = {
      Menu("Brightness", 150, 150, 100, 255, 5),
      Menu("Pre-delay", 0, 0, 0, 1000, 50),
      Menu("Duration", 250, 250, 125, 1000, 125),
      Menu("LCD brightness", 60, 60, 40, 70, 5)
    };
  public:
    Menus(int _pin_up, int _pin_down, int _pin_left, int _pin_right) {
      pin_up = _pin_up;
      pin_down = _pin_down;
      pin_left = _pin_left;
      pin_right = _pin_right;
    }
    void setup() {
      if (get_input() == 15) {
        mode = READY;
      } else {
        mode = CONFIG;
      }
    }

    Menu get_menu(int position) {
      return menus[position]  ;
    }

    Menu get_current_menu() {
      return get_menu(current_menu_index);
    }

    int get_current_menu_index() {
      return current_menu_index;
    }

    void previous_menu() {
      current_menu_index -= 1;
      if (current_menu_index < 0) {
        current_menu_index = menu_length - 1;
      }
    }
    void next_menu() {
      current_menu_index += 1;
      if (current_menu_index >= menu_length) {
        current_menu_index = 0;
      }
    }


    int get_input() {
      return 8 * digitalRead(pin_up) + 4 * digitalRead(pin_down) + 2 * digitalRead(pin_left) + digitalRead(pin_right);
    }

    boolean is_config_mode() {
      return mode == CONFIG;
    }
};
Adafruit_PCD8544 lcd = Adafruit_PCD8544(2, 3, 4, 5, 6);

Menus menus(10, 16, 14, 15);

int lastButtonValue = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  lcd.begin();
  lcd.setContrast(60);
  show("DIYIZ.SPACE", 1, "BOOTING ...", 1);
  menus.setup();
  Serial.begin(9600);
  Serial.println("ready...");
  delay(500);
}

void loop() {
  if (menus.is_config_mode()) {
    handle_config();
  } else {
    Serial.println("stand by");
    delay(1000);
    show("Stand by", 1, "...", 1);
  }
}

void handle_config() {
  int input = menus.get_input();
  if (input == 0) {
    return 0;
  } else if (input == 8) {
    menus.previous_menu();
  } else if (input == 4) {
    menus.next_menu();
  } else if (input == 2) {
    Menu m = menus.get_current_menu();  
    m.descrease();
  } else if (input == 1) {
    Menu m = menus.get_current_menu();  
    m.increase();
  }
  Menu m = menus.get_current_menu();
  show(m.get_title(), 1, m.get_value_as_string(), 1);
  Serial.println(menus.get_current_menu_index() + "|" + m.get_value());
  delay(250);
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

