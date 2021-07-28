#include <Arduino.h>
#include <WiFi.h>
#include "time.h"

#define COLUMS 16
#define ROWS 2

const char *ssid = "YES4";
const char *password = "haha2021a";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset = 28800; //seconds
const int daylightOffset = 0; //seconds

String getCurrentTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return "Failed to obtain time";
  }
  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  //print like "const char*"
  Serial.println(timeStringBuff);

  //Optional: Construct String object
  return String(timeStringBuff);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // while (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS) != 1) //colums - 20, rows - 4, pixels - 5x8, SDA - D2, SCL - D1
  // {
  //   Serial.println(F("PCF8574 is not connected or lcd pins declaration is wrong. Only pins numbers: 4,5,6,16,11,12,13,14 are legal."));
  //   delay(5000);
  // }

  // lcd.print(F("PCF8574 is OK...")); //(F()) saves string to flash & keeps dynamic memory free
  // delay(2000);

  // lcd.clear();

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  digitalWrite(LED_BUILTIN, HIGH);

  //init and get the time
  configTime(gmtOffset, daylightOffset, ntpServer);
  getCurrentTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  delay(1000);
  Serial.println(getCurrentTime());
}