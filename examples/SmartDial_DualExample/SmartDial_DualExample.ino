/*
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://roguerobotics.com/
|| @url            http://wiring.org.co/
||
|| @description
|| | Rogue Robotics SmartDial Library Example.
|| |
|| | This is a basic example to show the use of multiple SmartDials.
|| |
|| #
||
|| @license Please see LICENSE.txt for this project.
||
*/

#include <Wire.h>
#include <SmartDial.h>

#define ADDRESS1 0x36
#define ADDRESS2 0x09

SmartDial dial1(ADDRESS1);
SmartDial dial2(ADDRESS2);


void setup()
{
  bool dialsFound = false;

  Serial.begin(9600);
  Serial.println(F("Dual SmartDials Test"));

  if (!dial1.identify())
  {
    Serial.print(F("SmartDial 1 not found at address: 0x"));
    Serial.println(ADDRESS1, HEX);
  }
  else
  {
    Serial.print(F("SmartDial 1 found at address: 0x"));
    Serial.print(ADDRESS1, HEX);
    Serial.print(F(" - Version: "));
    Serial.println(dial1.getVersion(), HEX);
    dialsFound = true;
  }

  if (!dial2.identify())
  {
    Serial.print(F("SmartDial 2 not found at address: 0x"));
    Serial.println(ADDRESS2, HEX);
    dialsFound = false;
  }
  else
  {
    Serial.print(F("SmartDial 2 found at address: 0x"));
    Serial.print(ADDRESS2, HEX);
    Serial.print(F(" - Version: "));
    Serial.println(dial2.getVersion(), HEX);
  }

  if (!dialsFound)
  {
    Serial.println(F("Halting"));
    for (;;);  // HALT
  }
}


void loop()
{
  Serial.print(dial1.getPosition());
  Serial.print(F(", "));
  Serial.println(dial2.getPosition());

  if (dial1.isButtonPressed())
    Serial.println(F("SmartDial 1 button pressed"));

  if (dial2.isButtonPressed())
    Serial.println(F("SmartDial 2 button pressed"));

  delay(150);
}

