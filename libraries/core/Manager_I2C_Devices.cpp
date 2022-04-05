#include "Manager_I2C_Devices.h"
#include "view_LCD_Text.h"
#include "Btn_Process.h"
#include "debugkxn.h"
#include <LinkedList.h>

Manager_I2C_Data::Manager_I2C_Data()
{
    this->nameDevice = "Manager_I2C";
    this->timeInterval = 100;
    this->valueDevice = "No device";
    this->isRun = false;
}

bool Manager_I2C_Data::getData()
{
    // Step 1: Scan I2C Address list
    // Step 2: Show available I2C Device
    // Step 3: Init 2 Button (Next and Start)
    // Step 4: Select and run I2C Device
    // Step 5: Re Init 2 Button to default
    Manager_I2C_Device.myI2C_Devices_List.clear();
    Add_I2C_Device();
    uint8_t tempGetI2cAddress = GetI2C_Address();
    ManagerI2C_Device_InitButton();
    Next_DeviceI2C();

    while (this->isRun)
    {
        buttonLoop();
        RunDeviceI2C_WithIndex(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex));
        // RunDeviceI2C_WithIndex(indexI2CList.get(currentI2C_DeviceIndex));
    }

    buttonInit();

    this->valueDevice = "0x" + String(tempGetI2cAddress, HEX);

    return true;
}

bool Manager_I2C_Data::init()
{
    // deInit();
    return 1;
}

bool Manager_I2C_Data::deInit()
{
    this->nameDevice = "Manager_I2C";
    this->timeInterval = 200;
    this->valueDevice = "No device";
    this->isRun = false;
    Stop_DeviceI2C();
    return 1;
}

int Manager_I2C_Data::GetI2C_Address()
{
    int nDevices = 0, address_Detect = 1;
    // indexI2CList.clear();
    Manager_I2C_Device.indexI2CList.clear();
    Serial.println("Scanning...");

    for (int address = 1; address < 127; ++address)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println("  !");

            ++nDevices;
            address_Detect = address;
            ScanDeviceI2C_WithAddress(address_Detect);
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            address_Detect = address;
            ScanDeviceI2C_WithAddress(address_Detect);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("done\n");
    }

    return address_Detect;
}

void Manager_I2C_Data::ScanDeviceI2C_WithAddress(uint8_t address__)
{
    // for (int cf = 0; cf < myI2C_Devices_List.size(); cf++)
    for (int cf = 0; cf < Manager_I2C_Device.myI2C_Devices_List.size(); cf++)
    {
        // uint8_t tempAddress = myI2C_Devices_List.get(cf)->i2cAddress;
        // uint16_t tempHsCode = myI2C_Devices_List.get(cf)->Get_HS_Code();

        uint8_t tempAddress = Manager_I2C_Device.myI2C_Devices_List.get(cf)->i2cAddress;
        uint16_t tempHsCode = Manager_I2C_Device.myI2C_Devices_List.get(cf)->Get_HS_Code();

        if (address__ == tempAddress)
        {
            debug_manager_I2C_deviceln("tempHsCode: " + String(tempHsCode));
            debug_manager_I2C_deviceln("tempAddress: " + String(tempAddress));

            // myI2C_Devices_List.get(cf)->Set_HS_Code(100);
            // tempHsCode = myI2C_Devices_List.get(cf)->Get_HS_Code();
            debug_manager_I2C_deviceln("Index: " + String(cf));

            // indexI2CList.add(cf);
            Manager_I2C_Device.indexI2CList.add(cf);
        }
    }
}

void Manager_I2C_Data::RunDeviceI2C_WithIndex(uint8_t index__)
{
    if (Manager_I2C_Device.myI2C_Devices_List.get(index__)->isRun == false)
        return;

    Manager_I2C_Device.myI2C_Devices_List.get(index__)->init();

    while (Manager_I2C_Device.myI2C_Devices_List.get(index__)->isRun)
    {
        // debug_manager_I2C_deviceln(F("run myI2C_Devices_List.get(cf).getData();"));
        if (millis() - Current_Millis >= Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->timeInterval)
        {
            Current_Millis = millis();
            Manager_I2C_Device.myI2C_Devices_List.get(index__)->getData();
            ShowLCD(Manager_I2C_Device.myI2C_Devices_List.get(index__)->nameDevice, Manager_I2C_Device.myI2C_Devices_List.get(index__)->valueDevice);
        }
        buttonLoop();
    }

    Manager_I2C_Device.myI2C_Devices_List.get(index__)->isRun = false;
    Manager_I2C_Device.myI2C_Devices_List.get(index__)->deInit();
}

void Start_DeviceI2C()
{
    uint8_t temI2cIndex = Manager_I2C_Device.currentI2C_DeviceIndex;

    Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(temI2cIndex))->deInit();
    Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(temI2cIndex))->init();
    Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(temI2cIndex))->isRun = true;
    debug_manager_I2C_deviceln(F("Start_DeviceI2C"));
}

void Stop_DeviceI2C()
{
    uint8_t temI2cIndex = Manager_I2C_Device.currentI2C_DeviceIndex;
    debug_manager_I2C_deviceln(F("Stop_DeviceI2C"));
    debug_manager_I2C_deviceln(temI2cIndex);
    Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(temI2cIndex))->isRun = false;
    Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(temI2cIndex))->deInit();
}

void Next_DeviceI2C()
{
    if (Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->isRun)
    {
        Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->deInit();
        Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->isRun = false;
    }

    Manager_I2C_Device.currentI2C_DeviceIndex++;
    if (Manager_I2C_Device.currentI2C_DeviceIndex >= Manager_I2C_Device.indexI2CList.size())
        Manager_I2C_Device.currentI2C_DeviceIndex = 0;

    String tempName = Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->nameDevice;
    uint8_t tempValue = Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->i2cAddress;
    ShowLCD(tempName, "0x" + String(tempValue, HEX));

    debug_manager_I2C_deviceln(F("Next I2C Click "));
    debug_manager_I2C_deviceln(Manager_I2C_Device.currentI2C_DeviceIndex);
    debug_manager_I2C_deviceln(Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->hsCode);
    debug_manager_I2C_deviceln(Manager_I2C_Device.myI2C_Devices_List.get(Manager_I2C_Device.indexI2CList.get(Manager_I2C_Device.currentI2C_DeviceIndex))->i2cAddress);
    debug_manager_I2C_deviceln(tempName);
}

void Manager_I2C_Data::ManagerI2C_Device_InitButton()
{
    btn_next.attachClick(&Next_DeviceI2C);
    btn_start.attachClick(&Stop_DeviceI2C);
    btn_start.attachDoubleClick(&Start_DeviceI2C);
}
Manager_I2C_Data Manager_I2C_Device;
