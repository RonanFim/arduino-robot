#ifndef __ARRAY_H__
#define __ARRAY_H__

#include "Arduino.h"

#define Size_t uint16_t

template<class T, Size_t S>
class array {
  T _data[S];
  Size_t _size;

public:
  array();
  array(T* first, T* last);
  void clear(); 
  
  void push_back(const T& a);
  void pop_back(Size_t count);
  
  const Size_t& size() const; 
  T& operator[](const Size_t& pos); 
  const T& operator[](const Size_t& pos) const; 
  T* end();
  T* begin();
};

template<class T, Size_t S>
inline
array<T,S>::array() {
  clear();
}

template<class T, Size_t S>
inline
array<T,S>::array(T* first, T* last) {
  clear();
  for(; first != last; ++first) {
    push_back(*first);
  } 
}

template<class T, Size_t S>
inline
void array<T,S>::clear() {
  _size = 0;
}

template<class T, Size_t S>
inline
void array<T,S>::push_back(const T& a) {
  if (_size < S) {
    _data[_size] = a;
    ++_size;
  }
}

template<class T, Size_t S>
inline
void array<T,S>::pop_back(Size_t count) {
  while (count--) {
    if (_size) --_size;
  }
}

template<class T, Size_t S>
inline
const Size_t& array<T,S>::size() const {
  return _size;
}

template<class T, Size_t S>
inline
T* array<T,S>::end() {
  return &_data[_size];
}

template<class T, Size_t S>
inline
T* array<T,S>::begin() {
  return _data;
}

template<class T, Size_t S>
inline
T& array<T,S>::operator[](const Size_t& pos) {
  if (pos < _size) return _data[pos];
  return _data[_size-1];
}

template<class T, Size_t S>
inline
const T& array<T,S>::operator[](const Size_t& pos) const {
  if (pos < _size) return _data[pos];
  return _data[_size-1];
}

#endif