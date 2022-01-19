#include <Wire.h>
#include "SH1106Wire.h"
#include <WiFi.h>

const char *ssid = "YES4";
const char *password = "haha2021a";

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 60 * 60;
const int daylightOffset_sec = 3600;

SH1106Wire display(0x3c, SDA, SCL);
bool is24h = true;

tm getLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }

  return timeinfo;
}

void changeTimeFormat()
{
  is24h = !is24h;
}

void setup()
{
  Serial.begin(115200);

  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  display.init();

  display.flipScreenVertically();

  // set touch interrupt at pin T8
  touchAttachInterrupt(T8, changeTimeFormat, 20);
}

void loop()
{
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  tm now = getLocalTime();

  char timeStringBuff[50]; //50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A", &now);
  String day = String(timeStringBuff); // Wednesday

  strftime(timeStringBuff, sizeof(timeStringBuff), "%d %B %Y", &now);
  String date = String(timeStringBuff); // 19 January 2022

  String time;
  if (is24h)
  {
    strftime(timeStringBuff, sizeof(timeStringBuff), "%H:%M:%S", &now);
    time = String(timeStringBuff); //16:39:27
  }
  else
  {
    strftime(timeStringBuff, sizeof(timeStringBuff), "%I:%M:%S%p", &now);
    time = String(timeStringBuff); // 04:39:38PM
  }

  // display all the date and time
  display.setFont(ArialMT_Plain_24);
  display.drawString(1, 8, time);
  display.setFont(ArialMT_Plain_16);
  display.drawString(1, 30, date);
  display.setFont(ArialMT_Plain_10);
  display.drawString(1, 45, day);

  display.display();
  delay(100);
}