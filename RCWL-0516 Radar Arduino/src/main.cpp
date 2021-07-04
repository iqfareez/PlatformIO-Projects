#include <Arduino.h>
#define SENSOR_PIN 2
#define BUZZER_PIN 8

void setup()
{
  // put your setup code here, to run once:
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

// I read your post and I wanted to try it for education purposes.
// At first I thought my RCWL-0516 sensor didn't work properly because
// I had to almost touch it to get a response. I read some comparable
// comments about the sensor. Was it damaged by static electricity or
// by soldering? I even ordered a new sensor and it gave the same results.
// However, I had always put it on a breadboard. Connecting it via 3 wires
// of 25 cm long and putting it further away from the breadboard made a
// world of difference. Could it be that the metal mesh in the breadboard
// (or the Arduino itself) will somehow 'jam the radar'? In my current setup
// it's really sensitive and it has a wide scope. So if it shows poor
// sensitivity, I suggest you try it 😃
// comment from https://create.arduino.cc/projecthub/remnis/coolest-motion-detection-sensor-ever-d2d688

void loop()
{
  // put your main code here, to run repeatedly:
  int val = digitalRead(SENSOR_PIN);
  digitalWrite(LED_BUILTIN, val);
  if (val == HIGH)
  {
    tone(BUZZER_PIN, 80);
  }
  else
  {
    noTone(BUZZER_PIN);
  }
}