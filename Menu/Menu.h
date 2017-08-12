#ifndef Menu_h
#define Menu_h

#include "Arduino.h"

class Menu {
public:
    Menu(String title, int step_value, int default_value, int value);
    ~Menu();
    void handle(int value);
private:
    String _title;
    int _step_value;
    int _default_value;
    int _value;
};

#endif
