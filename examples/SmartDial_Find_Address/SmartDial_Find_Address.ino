/*
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://roguerobotics.com/
|| @url            http://wiring.org.co/
||
|| @description
|| | Rogue Robotics SmartDial Library Example.
|| |
|| | This example cycles through all of the available addresses for the
|| | SmartDial, and optionally sets the first found SmartDial to a new address.
|| |
|| #
||
|| @license Please see LICENSE.txt for this project.
||
*/

#include <Wire.h>
#include <SmartDial.h>

#define ADDRESSMIN 0x08
#define ADDRESSMAX 0x77

#define NEWADDRESS 0x09

SmartDial sd(ADDRESSMIN);


void setup()
{ 
  Serial.begin(9600);  // start serial for output
  Serial.println(F("Searching for SmartDials..."));

  for (uint8_t addr = ADDRESSMIN; addr <= ADDRESSMAX; addr++)
  {
    Serial.print(F("Trying: 0x"));
    Serial.println(addr, HEX);
    sd.setAddress(addr);
    delay(10);

    if (sd.getVersion() != 0)
    {
      Serial.print(F("Found SmartDial at address: 0x"));
      Serial.println(addr, HEX);

      if (NEWADDRESS >= ADDRESSMIN && addr != NEWADDRESS)
      {
        sd.changeDeviceAddress(NEWADDRESS);
        delay(10);

        if (sd.getVersion() != 0)
        {
          Serial.print(F("Set SmartDial to address: 0x"));
          Serial.println(NEWADDRESS, HEX);
        }
        else
        {
          Serial.print(F("Failed setting new address."));
        }
      }
      for (;;);
    }
  }
}


void loop()
{
}

