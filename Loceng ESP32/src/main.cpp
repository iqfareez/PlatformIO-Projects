#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "YES4";
const char *password = "haha2021a";

const int BUTTON = 5;
int buttonState = LOW;
HTTPClient http;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  http.begin("https://api.telegram.org/bot2098150036:AAFKH9JNTefiljqUX59oS47S487jin2VQWc/sendMessage?chat_id=320195187&text=Someone+at+your+front+door+🚪");

  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.macAddress());

  Serial.println("Connected to the WiFi network");
}

bool isChange(int state)
{
  if (state != buttonState)
  {
    buttonState = state;
    return true;
  }
  return false;
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (isChange(digitalRead(BUTTON)))
  {
    if (buttonState == LOW)
    {
      // onButtonDown
      Serial.println("DOWN");

      digitalWrite(LED_BUILTIN, HIGH);
      int httpCode = http.GET();

      Serial.println(httpCode);
      digitalWrite(LED_BUILTIN, LOW);
      http.end(); //Free the resources
    }
  }
}
