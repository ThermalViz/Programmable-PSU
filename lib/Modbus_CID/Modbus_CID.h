#ifndef MODBUS
#define MODBUS
#include <Arduino.h>

class Modbus
{
public:
    void begin(unsigned long baud, int index);
    void constructModbusRequest(byte *frame);
    void sendModbusRequest(byte *frame, byte length);
    void readModbusResponse(byte *frame, byte length);
private:
    uint16_t calculateCRC(byte *frame, byte length);
};

#endif