#ifndef XYPSU
#define XYPSU
#include <Arduino.h>
#include "Modbus_CID.h"
#include <SoftwareSerial.h>

class XY6015
{
public:
    Modbus modbus;
    int slaveAdress;
    int index;
    bool status;
    void begin(unsigned long baud, HardwareSerial serial);
    void begin(unsigned long baud, SoftwareSerial serial);
    void setVoltage(float v);
    void setCurrent(float a);
    void toggle();
    void read();

private:
    void createFrame(byte register, int value, String mode);
};

#endif
