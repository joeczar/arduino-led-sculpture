#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H
#include <Arduino.h>
#endif

#include "capacitive-state.h"

const int leds[] = {3, 5, 6, 9, 10, 11};
long level;
long randDelay;
const int analogPin = A0;

// smooth LED fade
int lastVals[] = {0, 0, 0, 0, 0, 0};

void turnOff()
{
  for (int i = 0; i < 6; i++)
  {
    analogWrite(leds[i], 0);
  }
}

void fadeIn(int pin, int startVal, int endVal, int delayTime)
{
  for (int i = startVal; i < endVal; i++)
  {

    analogWrite(pin, i);
    delay(delayTime);
  }
}
void fadeOut(int pin, int startVal, int endVal, int delayTime)
{
  for (int i = startVal; i >= endVal; i--)
  {

    analogWrite(pin, i);
    delay(delayTime);
  }
}
void fadeInAll(int min, int max, int delayTime)
{
  for (int i = min; i < max; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      analogWrite(leds[j], i);
    }
    delay(delayTime);
  }
}
void fadeOutAll(int max, int min, int delayTime)
{
  for (int i = max; i > min; i--)
  {
    for (int j = 0; j < 6; j++)
    {
      analogWrite(leds[j], i);
    }
    delay(delayTime);
  }
}

void fadeInOutAll(int min, int max, int delayTime)
{
  fadeInAll(min, max, delayTime);
  fadeOutAll(max, min, delayTime);
  turnOff();
  delay(delayTime);
}

int randomLevel(int pin, int minLed, int maxLed)
{
  level = random(minLed, maxLed);
  return level;
}
void flicker()
{
  for (int i = 0; i < 6; i++)
  {
    int level = randomLevel(leds[i], 0, 255);
    if (level > lastVals[i])
    {
      fadeIn(leds[i], lastVals[i], level, random(0, 2));
      lastVals[i] = level;
    }
    else
    {
      fadeOut(leds[i], lastVals[i], level, random(0, 2));
      lastVals[i] = level;
    }
  }
}
