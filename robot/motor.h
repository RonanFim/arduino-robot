#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Arduino.h"
#include "constants.h"

/*
  bind  // set and initialize motor pins;
  speed // dc > 0 -> forward, dc < 0 -> backward, dc = 0 -> stop
*/

template <typename T>
T saturate(const T& value, const T& lower_bound, const T& upper_bound) {
  if (value > upper_bound) return upper_bound;
  else if (value < lower_bound) return lower_bound;
  return value;
}

class motor {
public:
  void bind(const uint8_t& fw, const uint8_t& bk); 
  void stop(); 
  void speed(const int16_t& dc); 

  // void bind(motor& m, const uint8_t& fw, const uint8_t& bk);
  // static void stop(motor& m);
  // static void speed(motor& m, const int16_t& dc);

private:
  uint8_t __fw_pin;
  uint8_t __bk_pin;
  bool __direction;
};  

inline
void motor::bind(const uint8_t& fw, const uint8_t& bk) {
  __fw_pin = fw;
  __bk_pin = bk;
  pinMode(__fw_pin, OUTPUT);
  pinMode(__bk_pin, OUTPUT);
}

inline
void motor::stop() {
  digitalWrite(__bk_pin, 0);
  digitalWrite(__fw_pin, 0);
}

inline
void motor::speed(const int16_t& dc) {
  Serial.println(__bk_pin);
  Serial.println(__fw_pin);
  if (dc > 0) {
    __direction = forward;
    digitalWrite(__bk_pin, 0);
    analogWrite(__fw_pin, saturate(dc, 0, 255)); 
  }
  else if (dc < 0) {
    __direction = backward;
    digitalWrite(__fw_pin, 0);
    analogWrite(__bk_pin, saturate(abs(dc), 0, 255));
  }
  else {
    stop();
  }
}

// Static 

// inline
// void bind(motor& m, const uint8_t& fw, const uint8_t& bk) {
//   m.bind(fw,bk);
// }

// inline
// void motor::stop(motor& m) { 
//   m.stop(); 
// }

// inline
// void motor::speed(motor& m, const int16_t& dc) { 
//   m.speed(dc); 
// }

#endif // motor
