#include "debugkxn.h"
#include "Manager_Content.h"
#include "Manager_I2C_Devices.h"
#include "Btn_Process.h"
#include "view_LCD_Text.h"

// #include "Controller_Sieu_Am.h"
// #include "Controller_DHT.h"
// #include "Controller_Test_Snippet.h"

// // Include I2C Device
#include "Controller_MKL_I2C_Motor.h"
// #include "Controller_MKL_RTC.h"
// #include "Controller_Test_I2C_Snippet.h"

void AddManagerContent_Device()
{
  manager_Content.my_Devices_List.add(&Manager_I2C_Device);
  // manager_Content.my_Devices_List.add(&Dht_Device);
  // manager_Content.my_Devices_List.add(&sieuAm_Device);
}

void Add_I2C_Device()
{
  Manager_I2C_Device.myI2C_Devices_List.add(&MKL_I2C_Motor_Device);
  // Manager_I2C_Device.myI2C_Devices_List.add(&RTC_Device);
  // Manager_I2C_Device.myI2C_Devices_List.add(&device_Controller_Test_I2C_Snippet);
}

// ---------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  buttonInit();
  debug("Start!");
  View_LCD_Text_Init();
  manager_Content.begin();
}
void loop()
{
  buttonLoop();

  manager_Content.getData();
  runSerialLife();
}
// ---------------------------------------------------------------------------------------

// Hàm cho nút nhấn Start
void Start_do_1_Click()
{
  debugln("1 Click: Do it!");
  manager_Content.init();
  manager_Content.timeInterval = 250;
}
void Start_do_2_Click()
{
  debugln("2 Click: Re Start!");
  manager_Content.deInit();
  manager_Content.timeInterval = 250;
}

// Hàm cho nút nhấn Up
void Up_do_0_Click()
{

  manager_Content.deInit();
  manager_Content.Choseen_Menu++;
  manager_Content.timeInterval = 250;

  debug("0 Click: Menu");
  debugln(manager_Content.Choseen_Menu);
}
void Up_do_1_Click()
{
  manager_Content.deInit();
  manager_Content.Choseen_Menu++;
  manager_Content.timeInterval = 250;

  debug("1 Click: Menu");
  debugln(manager_Content.Choseen_Menu);
}

// Hàm cho nút nhấn Down
void Down_do_0_Click()
{
  debug("1 Click: Menu");
  debugln(manager_Content.Choseen_Menu);

  manager_Content.deInit();
  manager_Content.Choseen_Menu--;
  manager_Content.timeInterval = 250;
}
void Down_do_1_Click()
{
  debug("1 Click: Menu");
  debugln(manager_Content.Choseen_Menu);

  manager_Content.deInit();
  manager_Content.Choseen_Menu--;
  manager_Content.timeInterval = 250;
}

unsigned long timeSeriallife = millis();

void runSerialLife()
{
  if (millis() - timeSeriallife >= 1000)
  {
    timeSeriallife = millis();
    Serial.println("I live!");
  }
}
