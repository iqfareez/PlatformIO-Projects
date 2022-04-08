#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <esp_wifi.h>

long int buttonMillis = 0;
bool isBacklightOn = true;

int previousHour = 39;

const int button_pin = 18;
const int buzzer_pin = 2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ntpServer = "my.pool.ntp.org";
const long gmtOffset_sec = 8 * 60 * 60;
const int daylightOffset_sec = 0;

void IRAM_ATTR myButton()
{
  Serial.println("Button triggered");
  isBacklightOn = true;
  buttonMillis = millis();
}

tm getLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }

  return timeinfo;
}

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Serial.begin(115200);

  pinMode(button_pin, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);
  attachInterrupt(button_pin, myButton, FALLING);

  lcd.print("Starting...");

  // uint8_t newMACAddress[] = {00, 10, 0xFA, 0x6E, 0x38, 0x4A};
  // esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);

  WiFi.begin("YES4", "haha2021a");
  // WiFi.begin("YES4", "haha2021a");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  // init and get the time
  Serial.println("Configuring time");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getLocalTime();

  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  tm now = getLocalTime();

  if (isBacklightOn)
  {
    lcd.backlight();

    if (millis() > buttonMillis + 6100)
    {
      isBacklightOn = false;
      lcd.noBacklight();
    }
  }

  char timeStringBuff[50]; // 50 chars should be enough
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A", &now);
  String day = String(timeStringBuff); // Wednesday

  strftime(timeStringBuff, sizeof(timeStringBuff), "%d %B %Y", &now);
  String date = String(timeStringBuff); // 19 January 2022

  strftime(timeStringBuff, sizeof(timeStringBuff), "%I:%M:%S %p", &now);
  String time = String(timeStringBuff); // 04:39:38PM

  strftime(timeStringBuff, sizeof(timeStringBuff), "%I", &now);
  int hour = String(timeStringBuff).toInt();

  if (hour != previousHour)
  {
    digitalWrite(buzzer_pin, HIGH);
    previousHour = hour;
  }
  else
  {
    digitalWrite(buzzer_pin, LOW);
  }

  lcd.setCursor(0, 0);
  lcd.print(time);

  lcd.setCursor(0, 1);
  lcd.print(date);

  delay(100);
}