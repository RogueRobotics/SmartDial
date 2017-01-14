/*
||
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://roguerobotics.com/
|| @url            http://wattage.io/
|| @contributor    Adriaan Swanepoel
||
|| @description
|| | This library communicates with the Rogue Robotics SmartDial using I2C.
|| | The Rogue Robotics SmartDial is a rotary encoder dial, for use in Wiring
|| | Framework based projects (such as Arduino sketches).
|| |
|| #
||
|| @license Please see LICENSE.txt for this project.
||
*/

#include "SmartDial.h"

// Data Registers
#define SUMMARYREG     0x0A
#define POSITIONREG    0x0B
#define STATESREG      0x0C

#define VERSIONREG     0xFD
#define IDENTREG       0xFE

#define SMARTDIAL_ID   0x01

#define SWITCHSTATE    0b00000001
#define ATBOTTOMLIMIT  0b00000010
#define ATTOPLIMIT     0b00000100
#define LIMITSSET      0b00001000


// Command Registers
#define RESETREG       0x01
#define CENTERREG      0x02
#define SETBOTTOMREG   0x03
#define SETTOPREG      0x04
#define SETPOSITIONREG 0x05
#define SETADDRESSREG  0x06

#define RETRYCOUNT     3


#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>


union QuadrupleByte
{
  int32_t value;
  unsigned char bytes[4];
};


SmartDial::SmartDial(uint8_t address)
{
  deviceAddress = address;
  Wire.begin(); 
}


int32_t SmartDial::getPosition()
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(POSITIONREG);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, (uint8_t)4);
  int retry = 0;
  while((Wire.available() < 4) && (retry < RETRYCOUNT))
    retry++;
  
  if (Wire.available() >= 4)
  {
    QuadrupleByte pos;

    pos.bytes[0] = Wire.read();
    pos.bytes[1] = Wire.read();
    pos.bytes[2] = Wire.read();
    pos.bytes[3] = Wire.read();
    
  
    return pos.value; 
  }
  else
    return 0;
}


uint8_t SmartDial::getStates()
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(STATESREG);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, (uint8_t)1);
  int retry = 0;
  while((Wire.available() < 1) && (retry < RETRYCOUNT))
    retry++;
  
  if (Wire.available() == 1)
    return Wire.read();
  else
    return 0;
}


uint8_t SmartDial::getVersion()
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(VERSIONREG);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, (uint8_t)1);
  int retry = 0;
  while((Wire.available() < 1) && (retry < RETRYCOUNT))
    retry++;
  
  if (Wire.available() == 1)
    return Wire.read();
  else
    return 0;
}


bool SmartDial::isButtonPressed()
{
  if (getStates() & SWITCHSTATE)
    return true;
  else
    return false;
}


bool SmartDial::center()
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(CENTERREG);
  Wire.endTransmission();
  return true;
}


bool SmartDial::reset()
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(RESETREG);
  Wire.endTransmission();
  return true;
}


void SmartDial::setBottomLimit(int32_t bottom)
{
  QuadrupleByte quadByte;

  quadByte.value = bottom;

  Wire.beginTransmission(deviceAddress);
  Wire.write(SETBOTTOMREG);
  Wire.write(quadByte.bytes[0]);
  Wire.write(quadByte.bytes[1]);
  Wire.write(quadByte.bytes[2]);
  Wire.write(quadByte.bytes[3]);
  Wire.endTransmission();
}


void SmartDial::setTopLimit(int32_t top)
{
  QuadrupleByte quadByte;

  quadByte.value = top;

  Wire.beginTransmission(deviceAddress);
  Wire.write(SETTOPREG);
  Wire.write(quadByte.bytes[0]);
  Wire.write(quadByte.bytes[1]);
  Wire.write(quadByte.bytes[2]);
  Wire.write(quadByte.bytes[3]);
  Wire.endTransmission();
}


void SmartDial::setPosition(int32_t newPosition)
{
  QuadrupleByte quadByte;

  quadByte.value = newPosition;

  Wire.beginTransmission(deviceAddress);
  Wire.write(SETPOSITIONREG);
  Wire.write(quadByte.bytes[0]);
  Wire.write(quadByte.bytes[1]);
  Wire.write(quadByte.bytes[2]);
  Wire.write(quadByte.bytes[3]);
  Wire.endTransmission();
}


void SmartDial::setAddress(uint8_t newAddress)
{
  deviceAddress = newAddress;
}


bool SmartDial::changeDeviceAddress(uint8_t newAddress)
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(SETADDRESSREG);
  Wire.write(newAddress);
  Wire.endTransmission();

  deviceAddress = newAddress;

  delay(10);

  return true;
}


bool SmartDial::identify()
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(IDENTREG);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress, (uint8_t)1);
  int retry = 0;
  while((Wire.available() < 1) && (retry < RETRYCOUNT))
    retry++;

  if (Wire.available() == 1)
    return (Wire.read() == SMARTDIAL_ID);
  else
    return false;
}

