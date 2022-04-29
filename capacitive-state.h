#ifndef CAPACITIVE_STATE_H
#define CAPACITIVE_STATE_H
#include <Arduino.h>
#endif

#include <CapacitiveSensor.h>

bool lightsOn = false;

CapacitiveSensor cs_2_4 = CapacitiveSensor(2, 4);
// Set sensor sensitivity
const int sensitivity = 3000;
const int threshhold = 100;
int oldTime;
int timeThreshhold = 300;

int getTimePassed()
{
  long time = millis();
  long timePassed = time - oldTime;
  oldTime = time;
  Serial.println(timePassed);
  return timePassed;
}

void toggleState()
{
  long sensor = cs_2_4.capacitiveSensor(sensitivity);
  Serial.println(sensor);
  if (sensor > threshhold)
  {
    int timePassed = getTimePassed();
    if (timePassed > timeThreshhold)
    {
      lightsOn = !lightsOn;
      oldTime = millis();
    }
  }
}
