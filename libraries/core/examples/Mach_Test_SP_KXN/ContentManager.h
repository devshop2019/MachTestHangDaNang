#ifndef _CONTENT_H_MANAGER_H__
#define _CONTENT_H_MANAGER_H__
#include "arduino.h"
#include <LiquidCrystal_I2C.h>
#include "Sieu_Am.h"
// #include "CB_Dht.h"
#include "Controller_DHT.h"
#include "Manager_I2C_Devices.h"
/*--------------------------------User define------------------------------*/
// enum{
//   SIEU_AM_DEVICE_ID=0,
//   DHT_DEVICE_ID,
//   LAST_ID_DEVICE_
// };
/*================================End user define==========================*/

extern int LAST_ID_DEVICE;

extern Data_Adapter *listDevice[];
extern unsigned long contentManager_TimeInterval;

extern int Choseen_Menu; // Cài đặt số Menu lựa chọn loại Module
extern unsigned long Current_Millis;
extern LiquidCrystal_I2C lcd;

extern void Test_SP2();
extern void Test_Choseen_Menu2();
extern void initContentManager();
extern void deInitContentManager();
#endif
