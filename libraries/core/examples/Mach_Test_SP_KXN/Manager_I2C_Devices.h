#ifndef _Manager_I2C_Device_H_
#define _Manager_I2C_Device_H_

#include "Wire.h"

#include "dataAdapter.h"

extern int GetI2C_Address();
extern void Stop_DeviceI2C();

class Manager_I2C_Data : public Data_Adapter
{
public:
    Manager_I2C_Data();
    bool getData();
    bool init();
    bool deInit();

    int GetI2C_Address();
    void ScanDeviceI2C_WithAddress(uint8_t address__);
    void RunDeviceI2C_WithIndex(uint8_t index__);
    // void Select_DeviceI2C();
    // void Next_DeviceI2C();
    void ManagerI2C_Device_InitButton();
};

extern Manager_I2C_Data Manager_I2C_Device;
#endif