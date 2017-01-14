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

#ifndef SMARTDIAL_h
#define SMARTDIAL_h

#define SmartDial_Version 100

#include <inttypes.h>

#define DEFAULTADDRESS 0x36

class SmartDial
{
  private:
    uint8_t deviceAddress;

  public:
    SmartDial(uint8_t address = DEFAULTADDRESS);
    int32_t getPosition();
    bool isButtonPressed();
    bool center();
    bool reset();
    void setBottomLimit(int32_t bottom);
    void setTopLimit(int32_t top);
    void setPosition(int32_t newPosition);
    // TODO:
    // Mode - Limit, Wrap
    //void setMode(uint8_t newMode);
    //uint8_t getMode();

    uint8_t getStates();
    uint8_t getVersion();

    void setAddress(uint8_t newAddress);
    uint8_t getAddress() const
    {
      return deviceAddress;
    }
    bool changeDeviceAddress(uint8_t newAddress);

    bool identify();  // Is this a SmartDial?
};

#endif

