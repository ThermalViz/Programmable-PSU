#ifndef MODBUS
#define MODBUS
#include <Arduino.h>
#include <SoftwareSerial.h>

class Modbus
{
public:
    int index;
    bool isHWSerial = true;
    HardwareSerial *HWSerial;
    SoftwareSerial *SWSerial;
    void begin(unsigned long baud, HardwareSerial &serial);
    void begin(unsigned long baud, SoftwareSerial &serial);
    void constructModbusRequest(byte *frame);
    void sendModbusRequest(byte *frame, byte length);
    void readModbusResponse(byte *frame, byte length);

private:
    uint16_t calculateCRC(byte *frame, byte length);
};

#endif