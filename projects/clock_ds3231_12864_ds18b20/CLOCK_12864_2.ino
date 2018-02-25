#include <DS3231.h>
#include <U8glib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

DS3231 rtc(SDA, SCL);
char *daysShort[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

U8GLIB_ST7920_128X64_4X u8g(13, 11, 10);

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int minute = 0;

void setup(void) {
  rtc.begin();
  u8g.setRot180();
  u8g.setFont(u8g_font_profont29);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
//  rtc.setDOW(WEDNESDAY);
//  rtc.setTime(6, 40, 0);
//  rtc.setDate(20, 7, 2016);
  sensors.begin();
}

void paintClock() {
  Time t = rtc.getTime();
  u8g.setPrintPos(0, 2);
  u8g.print(daysShort[t.dow - 1]);

  u8g.setPrintPos(55, 2);
  u8g.print(twoDigit(t.date));
  u8g.setPrintPos(85, 2);
  u8g.print("-");
  u8g.setPrintPos(98, 2);
  u8g.print(twoDigit(t.mon));

  u8g.setPrintPos(55, 34);
  u8g.print(twoDigit(t.hour));
  if (t.sec % 2 == 0) {
    u8g.setPrintPos(85, 32);
    u8g.print(":");
  }
  u8g.setPrintPos(98, 34);
  u8g.print(twoDigit(t.min));

  if (minute != t.min) {
    sensors.requestTemperatures();
    minute = t.min;
  }
  u8g.setPrintPos(4, 34);
  u8g.print((int)sensors.getTempCByIndex(0));

  u8g.drawCircle(40, 40, 4);
}

String twoDigit(int digit) {
  String d = "";
  if (digit < 10) {
    d += "0";
    d += digit;
    return d;
  }
  d += digit;
  return d;
}

void loop(void) {
  u8g.firstPage();
  do {
    paintClock();
  } while ( u8g.nextPage() );
  delay(1000);
}


