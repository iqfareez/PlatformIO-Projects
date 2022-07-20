#include <Arduino.h>

void setup()
{
  pinMode(2, INPUT_PULLUP);
}

void loop()
{
  // pieze buzzer tone
  if (digitalRead(2) == LOW)
    tone(8, 1700);
  else
    noTone(8);
}