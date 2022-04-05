#include <Scheduler.h>
#include "Sieu_Am.h"
#include "debugkxn.h"
#include "Manager_Content.h"
#include "Btn_Process.h"
#include "view_LCD_Text.h"

#include "Sieu_Am.h"
#include "Controller_DHT.h"
#include "Controller_MKL_I2C_Motor.h"
#include "Controller_MKL_RTC.h"

void AddManagerContent_Device()
{
  manager_Content.my_Devices_List.add(&Manager_I2C_Device);
  manager_Content.my_Devices_List.add(&Dht_Device);
  manager_Content.my_Devices_List.add(&sieuAm_Device);
}

void Add_I2C_Device()
{
  Manager_I2C_Device.myI2C_Devices_List.clear();

  MKL_I2C_Motor_Device2.Set_HS_Code(200);
  MKL_I2C_Motor_Device3.Set_HS_Code(300);
  MKL_I2C_Motor_Device3.i2cAddress = 0x27;

  Manager_I2C_Device.myI2C_Devices_List.add(&MKL_I2C_Motor_Device2);

  Manager_I2C_Device.myI2C_Devices_List.add(&MKL_I2C_Motor_Device);

  Manager_I2C_Device.myI2C_Devices_List.add(&MKL_I2C_Motor_Device3);

  Manager_I2C_Device.myI2C_Devices_List.add(&RTC_Device);
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
  // initContentManager();
  manager_Content.init();
  // contentManager_TimeInterval = 0;
  manager_Content.timeInterval = 250;
}
void Start_do_2_Click()
{
  debugln("2 Click: Re Start!");
  // deInitContentManager();
  manager_Content.deInit();
  manager_Content.timeInterval = 250;
  // contentManager_TimeInterval = 0;
}

// Hàm cho nút nhấn Up
void Up_do_0_Click()
{
  // deInitContentManager();
  // Choseen_Menu++;
  manager_Content.deInit();
  manager_Content.Choseen_Menu++;
  manager_Content.timeInterval = 250;
  // Test_Choseen_Menu2();
  debug("0 Click: Menu");
  debugln(manager_Content.Choseen_Menu);
  // contentManager_TimeInterval = 0;
}
void Up_do_1_Click()
{
  // deInitContentManager();
  manager_Content.deInit();
  manager_Content.Choseen_Menu++;
  manager_Content.timeInterval = 250;
  // Choseen_Menu++;
  // Test_Choseen_Menu2();
  debug("1 Click: Menu");
  debugln(manager_Content.Choseen_Menu);
  // contentManager_TimeInterval = 0;
}

// Hàm cho nút nhấn Down
void Down_do_0_Click()
{
  // deInitContentManager();
  // Choseen_Menu--;
  // Test_Choseen_Menu2();
  debug("1 Click: Menu");
  debugln(manager_Content.Choseen_Menu);
  // contentManager_TimeInterval = 0;

  manager_Content.deInit();
  manager_Content.Choseen_Menu--;
  manager_Content.timeInterval = 250;
}
void Down_do_1_Click()
{
  // deInitContentManager();
  // Choseen_Menu--;
  // Test_Choseen_Menu2();
  debug("1 Click: Menu");
  debugln(manager_Content.Choseen_Menu);
  // contentManager_TimeInterval = 0;

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
