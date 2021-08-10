#ifndef __PARSER_H__
#define __PARSER_H__

#include "Arduino.h"
#include "partitioned_array.h"
#include "guard.h"

void evaluate() __attribute__((weak)); 

#define Size_t uint16_t

template <Size_t S, Size_t P> 
class parser {
  partitioned_array<char, S, P> _argv;
  uint8_t _argc;

  guard _partition;
  guard _list;
  
public:

  parser();
  void parse(const char& c);

  const uint8_t& argc();
  const char* argv(const uint8_t& argc);
};

template <Size_t S, Size_t P> 
parser<S, P>::parser() : _argv(), _argc(0) {
  _partition.lock();
  _list.release();
}

template <Size_t S, Size_t P> 
void parser<S, P>::parse(const char& c) 
{
  switch(c) {
  case -1: 
    return;

  // Command begin
  case ' ':
  case ',':
  case '(':
    if (_list.is_locked()) break; // goto append

    if (!_partition.is_locked()) { 
      _argv.push_back(0);
      _argv.make_partition();
      _partition.lock();
    } 
    return;

  // Command end
  case '\n':
  case ')':
    if (_list.is_locked()) break; // goto append 

    if (!_partition.is_locked()) {
      _argv.push_back(0);
      _argv.make_partition();
    }
    
    _argc = _argv.partitions();
    if (_argc) evaluate();
    
    _argv.clear();
    _partition.lock();
    _list.release();
    return;

  // List begin/end
  case '\"':
    _list.revert();
    return;

  }
  _argv.push_back(c);
  _partition.release();
}

template <Size_t S, Size_t P> 
const char* parser<S, P>::argv(const uint8_t& argc) {
  return _argv.data(argc);
}

template <Size_t S, Size_t P> 
const uint8_t& parser<S, P>::argc() {
  return _argc;
}

#endif
