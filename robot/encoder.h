#ifndef __ENCODER__H
#define __ENCODER__H

#include "Arduino.h"
#include "motor.h"

#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define FORWARD 1
#define BACKWARD 0
#define CENTER 1
#define SIDE 0


const uint8_t _ticks_per_rev = 40;
const double _radius = 3.25;
const double _dist_center = 7.65;
const double _dist_side = 15.3;


template <typename T>
T mod(const T& number)
{
    return (number < 0) ? (-1.0)*number : number;
}

class encoder
{
    const uint8_t _pin;
    int16_t _ticks;
    motor _m_master, _m_slave;

  public:
    encoder(const uint8_t& pin, const motor& m_master, const motor& m_slave);
    bool read();
    void go_straight(const double& dist, const int16_t& sp);
    void rotate(const double& ang, const int16_t& speed, const bool& mode);
    double angles(const bool& mode);
    double distance();
    void start_counter();
    void tick(const bool& direction);
};


encoder::encoder(const uint8_t& pin, const motor& m_master, const motor& m_slave)
    : _pin(pin), _m_master(m_master), _m_slave(m_slave)
{
    pinMode(_pin, INPUT);
}

inline
bool encoder::read()
{
    return digitalRead(_pin);
}

inline
void encoder::start_counter()
{
    _ticks = 0;
}

inline
void encoder::tick(const bool& direction)
{
    if (direction == FORWARD)
        _ticks++;
    else
        _ticks--;
}

inline
void encoder::go_straight(const double& dist, const int16_t& sp)
{
    _ticks = 0;

    uint16_t limit = mod(dist)*_ticks_per_rev/(TWO_PI*_radius);
    bool old = digitalRead(_pin);

    _m_master.speed(sp);//saturate(speed,-255,255)
    _m_slave.speed(sp);

    while(_ticks < limit)
    {
        if (digitalRead(_pin) != old)
        {digitalWrite(13,!digitalRead(13));
            _ticks++;
            old = !old;
        }
    }
    //_m_master.stop();
    //_m_slave.stop();
}

inline
void encoder::rotate(const double& ang, const int16_t& speed, const bool& mode)
{
    _ticks = 0;
    bool old = digitalRead(_pin);
    uint16_t limit;

    if(mode == CENTER)
    {
        limit = mod(ang)*DEG_TO_RAD*_dist_center*_ticks_per_rev/(TWO_PI*_radius);

        _m_master.speed(saturate(speed,-255,255));
        _m_slave.speed((-1)*saturate(speed,-255,255));
    }
    else
    {
        limit = mod(ang)*DEG_TO_RAD*_dist_side*_ticks_per_rev/(TWO_PI*_radius);

        _m_master.speed(saturate(speed,-255,255));
    }

    while(_ticks < limit)
    {
        if(digitalRead(_pin) != old)
        {
            _ticks++;
            old = !old;
        }
    }

    _m_master.stop();
    _m_slave.stop();
}
    
inline
double encoder::distance()
{
    return TWO_PI*_radius*_ticks/_ticks_per_rev;
}

inline
double encoder::angles(const bool& mode = CENTER)
{
    if(mode == CENTER)
        return RAD_TO_DEG*TWO_PI*_radius*_ticks/(_ticks_per_rev*_dist_center);
    else
        return RAD_TO_DEG*TWO_PI*_radius*_ticks/(_ticks_per_rev*_dist_side);
}

#endif