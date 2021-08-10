#ifndef __TIMER_H__
#define __TIMER_H__

#include "Arduino.h"

typedef uint32_t time_t; 
typedef time_t (*tfptr_t)();

template <tfptr_t time_f>
class basic_timer {
  time_t _reference;  

public:
  inline void start() { _reference = time_f(); }
  inline time_t stop() { return  time_f() - _reference; }

  inline bool ready(const time_t& interval) {
    if (stop() > interval) {
      start();
      return 1;
    } 
    return 0;
  }
}; 

template <tfptr_t time_f>
class loop_timer : public basic_timer<time_f> {

  time_t _interval;

public:
  loop_timer(const time_t& inter = -1) : _interval(inter) {}

  inline void interval(const time_t& inter) { _interval = inter; }
  inline bool ready() { return basic_timer<time_f>::ready(_interval); }

  inline static bool is_ready(loop_timer<time_f>& timer) { return timer.ready(); }
};

typedef basic_timer<millis> timer;
typedef basic_timer<millis> timer_ms;
typedef basic_timer<micros> timer_us;
typedef loop_timer<millis> lptimer;
typedef loop_timer<millis> lptimer_ms;
typedef loop_timer<micros> lptimer_us;


#endif