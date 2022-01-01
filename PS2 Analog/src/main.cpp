#include <Arduino.h>

const int VRX_PIN = A1;
const int VRY_PIN = A0;
const int SW_PIN = 10;

const int X_LED = 2;
const int Y_LED = 3;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT);
  pinMode(X_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:

  int xVal = analogRead(VRX_PIN);
  int yVal = analogRead(VRY_PIN);
  Serial.print("X value: ");
  Serial.print(xVal);
  Serial.print(" Y value: ");
  Serial.println(yVal);

  if ((xVal == 1023) || (xVal == 0))
    digitalWrite(X_LED, HIGH);
  else
    digitalWrite(X_LED, LOW);
  if ((yVal == 1023) || (yVal == 0))
    digitalWrite(Y_LED, HIGH);
  else
    digitalWrite(Y_LED, LOW);

  //TODO: Implement SW PIN
}