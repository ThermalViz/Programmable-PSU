#include "XY6015_CID.h"

void XY6015::begin(unsigned long baud, HardwareSerial *serial)
{
    // comm.begin();
    modbus.begin(baud, serial);
    HWSerial = serial;
    slaveAdress = 1;
    status = false;
}

void XY6015::setVoltage(float v)
{
    int voltage = v * 100;
    createFrame(0x0000, voltage, "SET");
}

void XY6015::setCurrent(float a)
{
    int current = a * 100;

    createFrame(0x0001, current, "SET");
}

void XY6015::read()
{
    // 14 set for value for 14 registers to read
    createFrame(0x00, 0x0014, "READ");
}

void XY6015::toggle(bool state)
{

    createFrame(0x0012, state, "SET");

    Serial.println("TOGGLED: " + String(state));
}

String XY6015::awaitResponse()
{
    String output;
    // byte temp[20];

    // for (int i = 0; i < 20; i++)
    // {
    //     temp[0] = buffer[i];
    // }

    if (HWSerial->available() > 0)
    {
        HWSerial->readBytes(buffer, 20);
    }

    for (byte data : buffer)
    {

        output += data + " ";
        Serial.print(data, HEX);
        Serial.print(" ");
    }

    Serial.println();
    return output;
}

void XY6015::createFrame(byte add, int val, String mode)
{
    byte requestFrame[8];
    byte frameMode = 0;

    if (mode == "SET")
    {
        frameMode = 0x06;
    }
    else if (mode == "READ")
    {
        frameMode = 0x03;
    }

    if (frameMode != 0)
    {
        requestFrame[0] = slaveAdress; // Slave Address
        requestFrame[1] = frameMode;   // Function Code
        requestFrame[2] = add >> 8;    // Start Address High
        requestFrame[3] = add & 0xFF;  // Start Address Low
        requestFrame[4] = val >> 8;    // Register Count High
        requestFrame[5] = val & 0xFF;  // Register Count Low

        modbus.constructModbusRequest(requestFrame); // Create calculated CRC and append to frame

        modbus.sendModbusRequest(requestFrame, 8); // Send Request

        for (int i = 0; i < 8; i++)
        {
            Serial.print(String(requestFrame[i], HEX) + " ");
        }
        Serial.println();
    }
    else
    {
        Serial.println("Invalid Frame Mode");
    }
}

bool XY6015::compareArray(byte array1[20], byte array2[20])
{
    for (int i = 0; i < 20; i++)
    {
        if (array1[i] != array2[i])
            return false;
    }

    return true;
}