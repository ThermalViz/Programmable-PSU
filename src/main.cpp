#include <Arduino.h>
#include <SoftwareSerial.h>
#include "XY6015_CID.h"

#define button 26

bool isPressed = false;
bool isOn = false;

XY6015 psu1;
XY6015 psu2;
XY6015 psu3;
XY6015 psu4;
XY6015 psu5;
XY6015 psu6;

void setVoltage(int index, float voltage);
void setCurrent(int index, float current);
void read(int index);
void toggle(int index);

SoftwareSerial Serial4(11, 10);
SoftwareSerial Serial5(13, 12);
SoftwareSerial Serial6(63, 62);

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  psu1.begin(115200, Serial1);
  psu2.begin(115200, Serial2);
  psu3.begin(115200, Serial3);
  psu4.begin(115200, Serial4);
  psu5.begin(115200, Serial5);
  psu6.begin(115200, Serial6);
}

void loop()
{

  if (Serial.available())
  {
    String received = Serial.readStringUntil('\n');
    String outputType = received.substring(1, 5); // select the first 4 characters of command
    int index = received.substring(0, 1).toInt();

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
}

void setVoltage(int index, float voltage)
{
  if (index == 1)
    psu1.setVoltage(voltage);
  if (index == 2)
    psu2.setVoltage(voltage);
  if (index == 3)
    psu3.setVoltage(voltage);
  if (index == 4)
    psu4.setVoltage(voltage);
  if (index == 5)
    psu5.setVoltage(voltage);
  if (index == 6)
    psu6.setVoltage(voltage);
}
void setCurrent(int index, float current)
{
  if (index == 1)
    psu1.setCurrent(current);
  if (index == 2)
    psu2.setCurrent(current);
  if (index == 3)
    psu3.setCurrent(current);
  if (index == 4)
    psu4.setCurrent(current);
  if (index == 5)
    psu5.setCurrent(current);
  if (index == 6)
    psu6.setCurrent(current);
}
void read(int index)
{
  if (index == 1)
    psu1.read();
  if (index == 2)
    psu2.read();
  if (index == 3)
    psu3.read();
  if (index == 4)
    psu4.read();
  if (index == 5)
    psu5.read();
  if (index == 6)
    psu6.read();
}
void toggle(int index)
{
  if (index == 1)
    psu1.toggle();
  if (index == 2)
    psu2.toggle();
  if (index == 3)
    psu3.toggle();
  if (index == 4)
    psu4.toggle();
  if (index == 5)
    psu5.toggle();
  if (index == 6)
    psu6.toggle();
}
