#include "Menu.h" //include the declaration for this class

const byte LED_PIN = 13; //use the LED @ Arduino pin 13

Menu::Menu(String title, int step_value, int default_value, int value) {
    _title = title;
    _step_value = step_value;
    _default_value = default_value;
    _value = value;
}

Menu::~Menu() {}

String Menu::handle(int value) {
    _value += value;
}
