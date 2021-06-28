/*
 * Countdown timer, 3 hours because IIUM's exam duration.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

const int BUTTON_PIN = 2;
const int BUZZER_PIN = 8;
const int LED_PIN_RED = 7;
const int LED_PIN_GREEN = 11;

int count = 180; // Default is 180 sec = 3 hours
int initialCount;
int progressBarCount;

enum state
{
  standby,
  start,
  finished,
};
state status;

void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  // Serial.begin(9600);
  status = standby; // system in standby mode when turned on
  initialCount = count;
}

void loop()
{
  switch (status)
  {
  case standby:
    lcd.setCursor(0, 0);
    lcd.print((String)count + "min=" + ((float)count / 60) + "hrs");
    lcd.setCursor(0, 1);
    lcd.print("START: BTN2");
    if (digitalRead(2) == LOW)
    {
      lcd.clear();
      analogWrite(LED_PIN_GREEN, 22);
      status = start;
    }
    break;
  case start:
    lcd.setCursor(0, 0);
    lcd.print((String)count + " minutes left");
    lcd.setCursor(0, 1);
    // show percentage on 2nd line
    // lcd.print((String)(((float)count / (float)initialCount) * 100) + "% left");
    progressBarCount = ((float)count / (float)initialCount) * 16;
    // show progress bar on 2nd line
    for (int i = 0; i < progressBarCount; i++)
    {
      lcd.print("=");
    }
    count--;
    // delay for 1 minutes
    delay(60000);
    lcd.clear();
    if (count == 0)
    {
      analogWrite(LED_PIN_GREEN, 0);
      lcd.clear();
      status = finished;
    }
    break;
  case finished:
    tone(BUZZER_PIN, 550);
    digitalWrite(LED_PIN_RED, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Times up!");
    delay(2000);
    noTone(BUZZER_PIN);

    // Blink the LCD backlight indefinitely (until RESET)
    while (true)
    {
      lcd.noBacklight();
      delay(450);
      lcd.backlight();
      delay(480);
    }

    break;

  default:
    break;
  }
}