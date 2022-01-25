#include <Arduino.h>

#include <IRremote.h> // >v3.0.0

#define PIN_SEND 7
#define PIN_RECV 9

void setup()
{
  Serial.begin(9600);
  IrSender.begin(PIN_SEND, ENABLE_LED_FEEDBACK); // Initializes IR sender
  IrReceiver.begin(PIN_RECV);                    // Initializes the IR receiver object
}

void loop()
{
  IrSender.sendNEC(0x0102, 0x34, true, 0); // the address 0x0102 with the command 0x34 is sent
  delay(1000);                             // wait for one second

  if (IrReceiver.decode())
  {
    Serial.println("Received something...");
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    Serial.println();
    IrReceiver.resume(); // Important, enables to receive the next IR signal
  }
}