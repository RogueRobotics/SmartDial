/*
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://roguerobotics.com/
|| @url            http://wiring.org.co/
||
|| @description
|| | Rogue Robotics SmartDial Library Example.
|| |
|| | This is a basic example to show the functionality of a SmartDial.
|| |
|| #
||
|| @license Please see LICENSE.txt for this project.
||
*/

#include <Wire.h>
#include <SmartDial.h>

#define ADDRESS1 0x36

SmartDial dial1(ADDRESS1);


void setup()
{
  Serial.begin(9600);
  Serial.println(F("SmartDial Test"));

  if (!dial1.identify())
  {
    Serial.print(F("SmartDial not found at address: 0x"));
    Serial.println(ADDRESS1, HEX);
    Serial.println(F("Halting"));
    for (;;);  // HALT
  }
  else
  {
    Serial.print(F("SmartDial found at address: 0x"));
    Serial.print(ADDRESS1, HEX);
    Serial.print(F(" - Version: "));
    Serial.println(dial1.getVersion(), HEX);
  }
}


void loop()
{
  Serial.println(dial1.getPosition());

  if (dial1.isButtonPressed())
    Serial.println(F("SmartDial button pressed"));

  delay(150);
}

