#include <Arduino.h>
#include <SoftwareSerial.h>
#include "XY6015_CID.h"
#include "Wire_Master.h"

#define button 26

bool isPressed = false;
bool isOn = false;

XY6015 psu1;
XY6015 psu2;
XY6015 psu3;

void setVoltage(int index, float voltage);
void setCurrent(int index, float current);
void read(int index);
void toggle(int index);

SoftwareSerial Serial4(11, 10);
SoftwareSerial Serial5(13, 12);
SoftwareSerial Serial6(63, 62);

WireMaster comm;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  comm.begin();
  psu1.begin(115200, &Serial2);
  psu2.begin(115200, &Serial3);
  psu3.begin(115200, &Serial1);
  Serial.println("Initializing programmable psu...");
}

void loop()
{

  if (Serial.available())
  {
    String received = Serial.readStringUntil('\n');
    String outputType = received.substring(1, 5); // select the first 4 characters of command
    int index = received.substring(0, 1).toInt();

    if (index < 4)
    {
      if (outputType == "SETV")
      {
        float voltage = received.substring(5, received.length()).toFloat();
        setVoltage(index, voltage);
      }
      else if (outputType == "SETA")
      {
        float curr = received.substring(5, received.length()).toFloat();
        setCurrent(index, curr);
      }
      else if (outputType == "READ")
      {
        read(index);
      }
      else if (outputType == "TOGG")
      {
        toggle(index);
      }
    }
    else
    {
      comm.transmit(received);
    }
  }

  psu1.awaitResponse();
  psu2.awaitResponse();
  psu3.awaitResponse();
}

void setVoltage(int index, float voltage)
{
  if (index == 1)
    psu1.setVoltage(voltage);
  if (index == 2)
    psu2.setVoltage(voltage);
  if (index == 3)
    psu3.setVoltage(voltage);
}
void setCurrent(int index, float current)
{
  if (index == 1)
    psu1.setCurrent(current);
  if (index == 2)
    psu2.setCurrent(current);
  if (index == 3)
    psu3.setCurrent(current);
}
void read(int index)
{
  if (index == 1)
    psu1.read();
  if (index == 2)
    psu2.read();
  if (index == 3)
    psu3.read();
}
void toggle(int index)
{
  if (index == 1)
    psu1.toggle();
  if (index == 2)
    psu2.toggle();
  if (index == 3)
    psu3.toggle();
}
