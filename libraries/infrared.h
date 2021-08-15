#ifndef __INFRARED_H__
#define __INFRARED_H__

#include "Arduino.h"

struct infrared {

	infrared(const uint8_t& ir_pin);
	bool read();
	bool isBlack();

  private:
  	uint8_t pin;
};

infrared::infrared(const uint8_t& ir_pin) : pin(ir_pin)
{

}

inline
bool infrared::read()
{
	return digitalRead(pin);
}

inline
bool infrared::isBlack()
{
	return !digitalRead(pin);
}

#endif __INFRARED_H__