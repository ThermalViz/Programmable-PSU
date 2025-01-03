#include "XY6015_CID.h"

void XY6015::begin(unsigned long baud, byte address)
{
    modbus.begin(baud);
    slaveAdress = address;
}

void XY6015::setVoltage(float v)
{
    int voltage = v * 100;

    createFrame(0x0000, voltage);
}

void XY6015::setCurrent(float a)
{
    int voltage = a * 100;

    createFrame(0x0001, voltage);
}

void XY6015::toggle(bool status)
{
    createFrame(0x0012, ((status) ? 0x0001 : 0x0000));

    Serial.println("TOGGLED: " + String(status));
}

void XY6015::createFrame(byte add, int val)
{
    byte requestFrame[8];

    requestFrame[0] = slaveAdress; // Slave Address
    requestFrame[1] = 0x06; // Function Code
    requestFrame[2] = add >> 8; // Start Address High
    requestFrame[3] = add & 0xFF; // Start Address Low
    requestFrame[4] = val >> 8; // Register Count High
    requestFrame[5] = val & 0xFF; // Register Count Low

    modbus.constructModbusRequest(requestFrame); // Create calculated CRC and append to frame

    modbus.sendModbusRequest(requestFrame, 8); // Send Request

    Serial.println(String(requestFrame[4]) + " | " + String(requestFrame[5]));
}