#include <Arduino.h>
const int  BUZZER_PIN=8;
const int LED_PIN = 3;
// the setup function runs once when you press reset or power the board
void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  tone(BUZZER_PIN, 988);           // wait for a second
  delay(29);          
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  noTone(BUZZER_PIN);
  delay(130);                     // wait for a second
  digitalWrite(LED_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
  tone(BUZZER_PIN, 300);           // wait for a second
  delay(66);          
  digitalWrite(LED_PIN, LOW);  // turn the LED off by making the voltage LOW
  noTone(BUZZER_PIN);
  delay(431);                     // wait for a second
}