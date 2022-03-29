#ifndef _DATA_H_ADAPTER_H_
#define _DATA_H_ADAPTER_H_

#include "arduino.h"

extern unsigned long Current_Millis;
class Data_Adapter
{
public:
  Data_Adapter(){};
  virtual ~Data_Adapter(){};

  unsigned long timeInterval = 1000;
  String nameDevice;
  String valueDevice;
  bool isRun = false;

  uint16_t hsCode;
  uint8_t i2cAddress;

  void Set_HS_Code(uint16_t hsCode__)
  {
    hsCode = hsCode__;
  }

  uint16_t Get_HS_Code()
  {
    return hsCode;
  }

  virtual bool getData() { return 0; };
  virtual bool init() { return 0; };
  virtual bool deInit() { return 0; };
};

#endif