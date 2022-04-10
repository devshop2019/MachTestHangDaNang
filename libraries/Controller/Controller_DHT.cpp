#include "Controller_DHT.h"
#include "MachTest_SP_IO.h"
#include "debugkxn.h"

Dht_Data::Dht_Data()
{
    this->nameDevice = "DHT";
    this->timeInterval = 2000;
    this->valueDevice = "No device";
}

bool Dht_Data::getData()
{
    if (dht)
    {
        debug_DHT_ln(F("Start Read DHT"));
        float h, t;
        h = dht->readHumidity();
        t = dht->readTemperature();
        debug_DHT_ln(F("Done Read DHT"));
        // if (isnan(h) || isnan(t))
        //     return true;

        String tempString = String(t) + "    " + String(h);
        this->valueDevice = tempString;
        debug_DHT_ln(tempString);
    }

    return true;
}

bool Dht_Data::reInit(uint8_t _type)
{
    deInit();
    dht = new (DHT)(DHTPIN, _type);
    dht->begin();
    return 1;
}

bool Dht_Data::init()
{
    deInit();
    dht = new (DHT)(DHTPIN, DHT11);
    this->nameDevice = "DHT11";
    dht->begin();

    delay(200);
    float t = dht->readTemperature();
    if (t < 5)
    {
        delay(200);
        deInit();
        dht = new (DHT)(DHTPIN, DHT22);
        this->nameDevice = "DHT2x";
    }
    this->isRun = true;
    return true;
}

bool Dht_Data::deInit()
{
    if (dht)
    {
        delete dht;
        dht = 0;
    }
    pinMode(DHTPIN, INPUT);
    this->valueDevice = "No device";
    this->nameDevice = "DHT";
    this->isRun = false;
    return true;
}

Dht_Data Dht_Device;
