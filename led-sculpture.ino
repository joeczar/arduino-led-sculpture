#include <CapacitiveSensor.h>

CapacitiveSensor cs_2_4 = CapacitiveSensor(2, 4);
// Set sensor sensitivity
const int sensitivity = 3000;
const int threshhold = 100;
int oldTime;
int timeThreshhold = 300;

const int leds[] = {3, 5, 6, 9, 10, 11};
long level;
long randDelay;
const int analogPin = A0;

bool lightsOn = false;

// smooth LED fade
int lastVals[] = {0, 0, 0, 0, 0, 0};

// smoothing input setup
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void setup()
{
  Serial.begin(9600);
  //  initialize readings to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    readings[thisReading] = 0;
  }
}
void loop()
{

  toggleState();
  int val = analogRead(analogPin);
  // Serial.println(val);
  // smoothInput()
  if (lightsOn)
  {
    flicker(leds);
  }
  else
  {
    turnOff();
  }

  // smoothInput();
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
int getTimePassed()
{
  long time = millis();
  long timePassed = time - oldTime;
  oldTime = time;
  Serial.println(timePassed);
  return timePassed;
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
int randomLevel(int pin, int minLed, int maxLed)
{
  level = random(minLed, maxLed);
  return level;
}
void flicker(const int leds[])
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
void turnOff()
{
  for (int i = 0; i < 6; i++)
  {
    analogWrite(leds[i], 0);
  }
}
void smoothInput()
{
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(analogPin);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings)
  {
    readIndex = 0;
  }

  average = total / numReadings;
  Serial.print(average);
  delay(1);
}