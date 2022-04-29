// #include "capacitive-state.h"
#include "led-functions.h"

void setup()
{
  Serial.begin(9600);
  //  initialize readings to 0
}
void loop()
{

  toggleState();
  int val = analogRead(analogPin);
  // Serial.println(val);
  // smoothInput()
  if (lightsOn)
  {
    // flicker();

    fadeInOutAll(0, 255, 10);
    delay(300);
  }
  else
  {
    turnOff();
    // fadeOutAll(255, 0, 10);
  }
}
