#ifndef XYPSU
#define XYPSU
#include <Arduino.h>
#include "Modbus_CID.h"

class XY6015
{
public:
    Modbus modbus;
    int slaveAdress;
    int index;
    bool status;

    void begin(unsigned long baud, int index);
    void setVoltage(float v);
    void setCurrent(float a);
    void toggle();
    void read();

private:
    void createFrame(byte register, int value, String mode);
};

#endif
