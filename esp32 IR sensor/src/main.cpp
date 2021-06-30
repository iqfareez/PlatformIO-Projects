#include <Arduino.h>

int value;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(23, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  value = digitalRead(23);

  if (value == 1)
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}