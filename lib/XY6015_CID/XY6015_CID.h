#ifndef XYPSU
#define XYPSU
#include <Arduino.h>
#include "Modbus_CID.h"
#include <SoftwareSerial.h>
#include "Wire_Master.h"

// WireMaster comm;

class XY6015
{
public:
    Modbus modbus;
    HardwareSerial *HWSerial;
    int slaveAdress;
    int index;
    bool status;
    byte buffer[20];
    void begin(unsigned long baud, HardwareSerial *serial);
    void setVoltage(float v);
    void setCurrent(float a);
    void toggle(bool state);
    void read();
    String awaitResponse();
    bool compareArray(byte array1[20], byte array2[20]);

private:
    void createFrame(byte register, int value, String mode);
};

#endif
