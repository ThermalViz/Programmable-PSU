#include "Modbus_CID.h"
#include <SoftwareSerial.h>

void Modbus::begin(unsigned long baud, int index)
{
    SoftwareSerial Serial4(11, 10);
    SoftwareSerial Serial5(13, 12);
    SoftwareSerial Serial6(63, 62);

    switch (index)
    {
    case 1:
        Serial1.begin(baud);
        break;
    case 2:
        Serial2.begin(baud);
        break;
    case 3:
        Serial3.begin(baud);
        break;
    case 4:
        Serial4.begin(baud);
        break;
    case 5:
        Serial5.begin(baud);
        break;
    case 6:
        Serial6.begin(baud);
        break;
    default:
        break;
    }
}

void Modbus::constructModbusRequest(byte *frame)
{

    uint16_t crc = calculateCRC(frame, 6);
    frame[6] = crc & 0xFF;        // CRC low byte
    frame[7] = (crc >> 8) & 0xFF; // CRC high byte
}

void Modbus::sendModbusRequest(byte *frame, byte length)
{
    for (byte i = 0; i < length; i++)
    {
        Serial2.write(frame[i]);
    }
}

uint16_t Modbus::calculateCRC(byte *frame, byte length)
{
    uint16_t crc = 0xFFFF; // Initialize CRC to 0xFFFF
    for (byte i = 0; i < length; i++)
    {
        crc ^= frame[i];
        for (byte j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}