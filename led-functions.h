#ifndef LED_FUNCTIONS_H
#define LED_FUNCTIONS_H
#include <Arduino.h>
#endif

#include "capacitive-state.h"

const int leds[] = {3, 5, 6, 9, 10, 11};
const int numLeds = sizeof(leds) / sizeof(leds[0]);
long level;
long randDelay;
const int analogPin = A0;

// sindFade
int brightness = 0;

// smooth LED fade
int lastVals[] = {0, 0, 0, 0, 0, 0};

void turnOff()
{
  for (int i = 0; i < numLeds; i++)
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
    for (int j = 0; j < numLeds; j++)
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
    for (int j = 0; j < numLeds; j++)
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
  for (int i = 0; i < numLeds; i++)
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
// fade in and out with sine wave
void sineFadeOne(int led, int delayTime)
{
  for (int i = 0; i < 360; i++)
  {
    float angle = radians(i);
    brightness = (255 / 2) + (255 / 2) * sin(angle);
    analogWrite(led, brightness);
    delay(delayTime);
  }
}
void sineFadeAll(int delayTime)
{
  for (int i = 0; i < 360; i++)
  {
    float angle = radians(i);
    brightness = (255 / 2) + (255 / 2) * sin(angle);
    for (int j = 0; j < numLeds; j++)
    {
      analogWrite(leds[j], brightness);
    }
    delay(delayTime);
  }
}

void movingSine()
{
  float current = millis() / 1000.0;
  for (int i = 0; i < numLeds; i++)
  {
    float v = 0.0;
    v += sin(i + current);
    v = (v + 1.0) / 2.0;
    // v += sin(current);
    // v += sin(1.0 * (i * sin(current / 0.5) + numLeds * cos(current / 0.25) + current));

    float angle = radians(i + v * 180);
    // float piOne = sin(v * PI);
    // float sinAngle = sin(v * angle) * PI;
    // float piAngle = piOne * angle;
    // float cosPi = cos(v * PI);
    // float piTwo = sin(v * PI + 2.0 * PI / 3.0);

    analogWrite(leds[i], angle * 255);
  }
}