#include <Arduino.h>
#include <SoftwareSerial.h>
#include "XY6015_CID.h"
#include "Wire_Master.h"

#define button 26

bool isPressed = false;
bool isOn = false;
String recieveString = "";

XY6015 psu1;
XY6015 psu2;
XY6015 psu3;

void setVoltage(int index, float voltage);
void setCurrent(int index, float current);
void read(int index);
void toggle(int index, bool state);

SoftwareSerial Serial4(11, 10);
SoftwareSerial Serial5(13, 12);
SoftwareSerial Serial6(63, 62);

String PSU1_READ = "";
String PSU2_READ = "";
String PSU3_READ = "";
int x = 0;
WireMaster comm;

bool newData = false;

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

    String raw = Serial.readStringUntil('\n');

    char received[raw.length() + 1];

    raw.toCharArray(received, sizeof(received));

    String outputType = raw.substring(1, 5); // select the first 4 characters of command
    int index = raw.substring(0, 1).toInt();

    if (raw == "WHOU") Serial.println("SUPP");
    if (index < 4)
    {
      if (outputType == "SETV")
      {
        float voltage = raw.substring(5, raw.length()).toFloat();
        setVoltage(index, voltage);
      }
      else if (outputType == "SETA")
      {
        float curr = raw.substring(5, raw.length()).toFloat();
        setCurrent(index, curr);
      }
      else if (outputType == "READ")
      {
        read(index);
      }
      else if (outputType == "TOGG")
      {
        int state = raw.substring(5, 6).toInt();
        toggle(index, state);
      }
    }
    else
    {
      Serial.println(raw);
      comm.transmit(received);
    }
  }

  String recieve = comm.receive();

  // PSU1_READ = psu1.awaitResponse();
  // PSU2_READ = psu2.awaitResponse();
  // PSU3_READ = psu3.awaitResponse();
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
void toggle(int index, bool state)
{
  if (index == 1)
    psu1.toggle(state);
  if (index == 2)
    psu2.toggle(state);
  if (index == 3)
    psu3.toggle(state);
}
