#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int ledPin4 = 5;
const int ledPin5 = 6;
const int ledPin6 = 7;
const int ledPin7 = 8;
const int ledPin8 = 9;
const int ledPin9 = 10;
const int ledPin10 = 11;
const int ledPin11 = 12;
const int ledPin12 = 13;

void TaskBlink1(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin1, HIGH);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    digitalWrite(ledPin1, LOW);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void TaskBlink2(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin2, HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    digitalWrite(ledPin2, LOW);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void TaskBlink3(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin3, HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(ledPin3, LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void TaskBlink4(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin4, HIGH);
    vTaskDelay(400 / portTICK_PERIOD_MS);
    digitalWrite(ledPin4, LOW);
    vTaskDelay(400 / portTICK_PERIOD_MS);
  }
}

void TaskBlink5(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin5, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(ledPin5, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void TaskBlink6(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin6, HIGH);
    vTaskDelay(600 / portTICK_PERIOD_MS);
    digitalWrite(ledPin6, LOW);
    vTaskDelay(600 / portTICK_PERIOD_MS);
  }
}

void TaskBlink7(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin7, HIGH);
    vTaskDelay(700 / portTICK_PERIOD_MS);
    digitalWrite(ledPin7, LOW);
    vTaskDelay(700 / portTICK_PERIOD_MS);
  }
}

void TaskBlink8(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin8, HIGH);
    vTaskDelay(800 / portTICK_PERIOD_MS);
    digitalWrite(ledPin8, LOW);
    vTaskDelay(800 / portTICK_PERIOD_MS);
  }
}

void TaskBlink9(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin9, HIGH);
    vTaskDelay(900 / portTICK_PERIOD_MS);
    digitalWrite(ledPin9, LOW);
    vTaskDelay(900 / portTICK_PERIOD_MS);
  }
}

void TaskBlink10(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin10, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(ledPin10, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void TaskBlink11(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin11, HIGH);
    vTaskDelay(1100 / portTICK_PERIOD_MS);
    digitalWrite(ledPin11, LOW);
    vTaskDelay(1100 / portTICK_PERIOD_MS);
  }
}

void TaskBlink12(void *parameters)
{
  for (;;)
  {
    digitalWrite(ledPin12, HIGH);
    vTaskDelay(1200 / portTICK_PERIOD_MS);
    digitalWrite(ledPin12, LOW);
    vTaskDelay(1200 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  // put your setup code here, to run once:
  int startPin = 2;
  int lastPin = 13;

  for (int i = startPin; i <= lastPin; i++)
  {
    pinMode(i, OUTPUT);
  }

  xTaskCreate(TaskBlink1, "Blink LED 1 for every 100 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink2, "Blink LED 2 for every 200 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink3, "Blink LED 3 for every 300 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink4, "Blink LED 4 for every 400 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink5, "Blink LED 5 for every 500 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink6, "Blink LED 6 for every 600 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink7, "Blink LED 7 for every 700 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink8, "Blink LED 8 for every 800 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink9, "Blink LED 9 for every 900 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink10, "Blink LED 10 for every 1000 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink11, "Blink LED 11 for every 1100 ms", 28, NULL, 1, NULL);
  xTaskCreate(TaskBlink12, "Blink LED 12 for every 1200 ms", 28, NULL, 1, NULL);

  // NOTE TO SELF: Use lower heap size if creating many tasks
  // I don't know the ideal heap size, if anyone know pls lmk

  // for this case, i found that 27 is the minimum hepa size
  // required for it to works correctly.
  // so I set to 28 "just to be safe"

  // also if anyone know the best implementatiom, pls lmk as well
}

void loop()
{
  // Empty. Things are done in Tasks.
}