#include <Scheduler.h>
#include "Sieu_Am.h"
#include "debugkxn.h"
// #include "ContentManager.h"
#include "Manager_Content.h"
#include "Btn_Process.h"
#include "view_LCD_Text.h"

// ---------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  // Scheduler.start(buttonInit, buttonLoop, 50);
  buttonInit();
  debug("Start!");
  View_LCD_Text_Init();
  manager_Content.begin();
}
void loop()
{
  buttonLoop();

  // Test_Choseen_Menu2();
  // Test_SP2();
  manager_Content.getData();
  runSerialLife();
  // delay(10);
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
