#include "button.h"

//#define debug(x)  Serial.println(x) // hiện debug
#define debug(x)                    // tắt debug

button::button(byte button_pin)
{
  this->button_pin = button_pin;
  this->begin();
}

void button::begin()
{
  pinMode(this->button_pin, INPUT);
}

void button::loop()
{
  // --- Xem đây là 1Click / 1Click+đè / 2Click
  this->state_button = digitalRead(this->button_pin);   // Tín hiệu Nút Mode bây giờ
  if(this->state_button != this->last_button)           // Tín hiệu Nút Mode thay đổi
  {
    delay(20);                                          // Chống nhiễu do nút bấm
    this->state_button = digitalRead(this->button_pin); 
    if(this->state_button != this->last_button)
    {
      if(this->state_button)                            // Đang nhấn Nút Mode
      {
        if(this->count_button == 0)
        { this->current_Millis = millis();}
      }
      else                                              // Đang ko nhấn Nút Mode
      {this->count_button++;}
    }
  }
  this->last_button = this->state_button;               // Lưu tín hiệu Nút Mode

  // --- Sau 0.5s đã xác nhận kiểu bấm nút -> mới cho thay đổi chương trình
  if(millis() - this->current_Millis > 100)
  {
    if(this->count_button == 0 && digitalRead(this->button_pin))  // 1Click nút 'Mode' + đè nút
    {
      this->count_button = 255;                                   // Reset lại số Click của Nút 'Mode'
                                                                  // đặt là 255 .Vì lúc này ta vẫn giữ nút, nếu bỏ ra tự nó sẽ được cộng 1, tức 255+1=0
      //
      debug("1 click hold");
      // ---
      if(button_1ClickHold) button_1ClickHold();                  // Tức con trỏ hàm button_1ClickHold phải có giá trị địa chỉ khác 0 (tránh RESET), thì mới được dùng button_1ClickHold();
    }                                                             // button_1ClickHold(); tương đương với lệnh gọi hàm Mode_1_do_1ClickHold(), vì con trỏ này mang địa chỉ hàm đó
    if(this->count_button == 1)                                   // 1Click nút 'Mode'
    {
      this->count_button = 0;                                     // Reset lại số Click của Nút 'Mode'
      //
      debug("1 click");
      // ---
      if(button_1Click) button_1Click();
    }
    if(this->count_button == 2)                                   // 2Click nút 'Mode'
    {
      this->count_button = 0;                                     // Reset lại số Click của Nút 'Mode'
      //
      debug("2 click");
      // ---
      if(button_2Click) button_2Click();
    }
    if(this->count_button > 2)                                    // Dành cho trường hợp thao tác quá nhanh
    {
      this->count_button = 0;
      //
      debug("No click");
    }
    this->current_Millis = millis();
  }
}

