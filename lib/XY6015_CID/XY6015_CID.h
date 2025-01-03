#ifndef XYPSU
#define XYPSU
#include <Arduino.h>
#include "Modbus_CID.h"

class XY6015
{
    public:
        Modbus modbus;
        int slaveAdress;

        void begin(unsigned long baud, byte address);
        void setVoltage(float v);
        void setCurrent(float a);
        void toggle(bool status);
    private:
        void createFrame(byte register, int value);
};

#endif
