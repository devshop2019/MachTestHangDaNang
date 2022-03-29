#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "arduino.h"

class button
{
  public:
  //
  byte button_pin;          // Cài đặt chân nút bấm
  //
  bool state_button = LOW, last_button = LOW;
  byte count_button = 0;
  unsigned long current_Millis = millis();
  //
  button(byte button_pin);  // Hàm cài đặt chân nút bấm
  //
  void begin();
  void loop();
  //
  void (*button_1ClickHold)();
  void (*button_1Click)();
  void (*button_2Click)();
};

#endif

