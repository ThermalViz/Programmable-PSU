#ifndef XYPSU
#define XYPSU
#include <Arduino.h>
#include "Modbus_CID.h"
#include <SoftwareSerial.h>

class XY6015
{
public:
    Modbus modbus;
    HardwareSerial *HWSerial;
    int slaveAdress;
    int index;
    bool status;
    byte buffer[40];
    void begin(unsigned long baud, HardwareSerial *serial);
    void setVoltage(float v);
    void setCurrent(float a);
    void toggle();
    void read();
    void awaitResponse();

private:
    void createFrame(byte register, int value, String mode);
};

#endif
