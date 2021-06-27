#include <Arduino.h>

const int LED1 = 7;
const int LED2 = 8;

int OTHER_PIN[] = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13};
int arrSize;

void setup()
{
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  arrSize = sizeof(OTHER_PIN) / sizeof(OTHER_PIN[0]);

  for (int i = 0; i < arrSize; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void delayInMinutes(int minutes)
{
  for (int i = 0; i < arrSize; i++)
  {
    digitalWrite(OTHER_PIN[i], HIGH);

    delay((minutes * 60000) / arrSize);
  }

  // after done delay, reset all loading indicator
  for (int i = 0; i < arrSize; i++)
  {
    digitalWrite(OTHER_PIN[i], LOW);
  }
}



void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, HIGH);
  delayInMinutes(10);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delayInMinutes(10);

}
