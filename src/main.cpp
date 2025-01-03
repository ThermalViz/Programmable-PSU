#include <Arduino.h>
#include "XY6015_CID.h"

#define button 26

bool isPressed = false;
bool isOn = false;


XY6015 psu;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  psu.begin(115200, 0x01);
}

void loop()
{

  if (Serial.available())
  {
    String received = Serial.readStringUntil('\n');
    String outputType = received.substring(0, 4); // select the first 4 characters of command

    if (outputType == "SETV")
    {
      float voltage = received.substring(4, received.length()).toFloat();
      psu.setVoltage(voltage);
    }
    else if (outputType == "TOGG")
    {
      Serial.println("TOGG: " + String(isPressed));
      ((isPressed) ? psu.toggle(false) : psu.toggle(true));
      isPressed = !isPressed;
    }
  }

  // if (digitalRead(button) && !isPressed)
  // {

  //   psu.toggle(true);

  //   Serial.println("Pressed");
  // }
  // else if (!digitalRead(button) && isPressed)
  // {
  //   isPressed = !isPressed;
  // }
}
