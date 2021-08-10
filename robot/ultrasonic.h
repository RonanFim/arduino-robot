#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

#include "Arduino.h"
#include "guard.h"

struct ultrasonic {

  ultrasonic(const int8_t& e, const int8_t& t); 
  
  const float& distance();

private:
  volatile uint32_t __echo_time;
  float __distance;

  void echo_in();  
  void trig(); 
  void calculate(); 

  const uint8_t echo_pin;
  const uint8_t trig_pin;

  //guard __trig;
  //guard __echo;
  guard __calc;
};

ultrasonic::ultrasonic(const int8_t& e, const int8_t& t) 
  : echo_pin(e), trig_pin(t) {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

inline
void ultrasonic::echo_in() {
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(11);
    digitalWrite(trig_pin, LOW);
    __distance = pulseIn(echo_pin, HIGH) * 0.01715;   
}

inline 
void ultrasonic::trig() { 
 // if (__trig.is_locked()) return;
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(11);
  digitalWrite(trig_pin, LOW);
 // __trig.lock();
}

inline
void ultrasonic::calculate() {
  echo_in();
  if (__calc.is_locked()) return;
  __distance = __echo_time * 0.01715; 
  
  //__trig.release();
  __calc.lock();
}

inline
const float& ultrasonic::distance() { 
  calculate();
  trig();
  return __distance; 
}

#endif
