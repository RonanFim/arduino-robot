#ifndef __CONSTS_H__
#define __CONSTS_H__

// fw = foward
// bk = backward
// _p = pin
// r = right
// l = left




const uint8_t m_ultrasonic_echo_p = 8;
const uint8_t m_ultrasonic_trig_p = 7;




/*const uint8_t fw_rmotor_p = 10;
const uint8_t bk_rmotor_p = 9;
const uint8_t fw_lmotor_p = 6;
const uint8_t bk_lmotor_p = 5;*/

const uint8_t lenc_pcint_p = 51;
const uint8_t renc_pcint_p = 50;

const double pi = 3.1415926535897932384626433832795;
const double half_pi = 1.5707963267948966192313216916398;
const double two_pi = 6.283185307179586476925286766559;

const double deg_to_rad = 0.017453292519943295769236907684886;
const double rad_to_deg = 57.295779513082320876798154814105;

const bool forward = 1;
const bool backward = 0;

const uint8_t ticks_per_rev = 40;
const double radius = 3.25;
const double ticks_to_distance = two_pi * radius * ticks_per_rev;

#endif
