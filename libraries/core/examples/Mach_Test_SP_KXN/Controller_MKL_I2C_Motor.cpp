#include "Controller_MKL_I2C_Motor.h"

Controller_MKL_I2C_Motor::Controller_MKL_I2C_Motor()
{
    this->i2cAddress = 0x40;
    this->nameDevice = "MKL I2C Driver";
    this->timeInterval = 1;
    Set_HS_Code(1518); // https://hshop.vn/products/mach-dieu-khien-dong-co-mkl-m10-i2c-motor-control-module
}

Controller_MKL_I2C_Motor::~Controller_MKL_I2C_Motor()
{
}

bool Controller_MKL_I2C_Motor::getData()
{
    if (millis() - lastTimeUpdate >= timeUpdate)
    {
        lastTimeUpdate = millis();

        if (speedDCMotor == 0)
        {
            dirDCMotor = !dirDCMotor;
        }

        speedDCMotor = speedDCMotor + 1;
        angleRCValue = angleRCValue + 1;

        if (angleRCValue > 180)
        {
            angleRCValue = 0;
        }

        // Serial.print("speedDCMotor: " + String(speedDCMotor) + "\t");
        // Serial.print("angleRCValue: " + String(angleRCValue) + "\r\n");
    }

    myDriver.writeS2(180 - angleRCValue);
    myDriver.writeS1(angleRCValue);

    myDriver.MA(dirDCMotor, speedDCMotor);
    myDriver.MB(dirDCMotor, speedDCMotor);
    delay(1);

    return 0;
}

bool Controller_MKL_I2C_Motor::init()
{
    myDriver.begin();
    return 0;
}

Controller_MKL_I2C_Motor MKL_I2C_Motor_Device;
Controller_MKL_I2C_Motor MKL_I2C_Motor_Device2;
Controller_MKL_I2C_Motor MKL_I2C_Motor_Device3;