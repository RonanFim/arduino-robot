#ifndef __PARTARRAY_H__
#define __PARTARRAY_H__

#include "array.h"

#define Size_t uint16_t

template <typename T, Size_t S, Size_t P> 
class partitioned_array {
  array<T, S> _data;
  array<T*, P> _partitions;

public:
  partitioned_array() { clear(); }
  void clear(); 

  void push_back(const T& a);
  void pop_back(Size_t count);
  void make_partition();

  const Size_t& size() const; 
  const Size_t& partitions() const; 
  Size_t size(const Size_t& partition); 
  
  const T* data(const Size_t& partition);
};

template<typename T, Size_t S, Size_t P> 
void partitioned_array<T,S,P>::clear() { 
  _data.clear(); 
  _partitions.clear();
}

template<typename T, Size_t S, Size_t P> 
inline
void partitioned_array<T,S,P>::push_back(const T& a) {
  _data.push_back(a);
}

template<typename T, Size_t S, Size_t P> 
inline
void partitioned_array<T,S,P>::pop_back(Size_t count) {
  _data.pop_back(count);
}

template<typename T, Size_t S, Size_t P> 
inline
void partitioned_array<T,S,P>::make_partition() {
  _partitions.push_back(_data.end());
}

template<typename T, Size_t S, Size_t P> 
inline
const Size_t& partitioned_array<T,S,P>::size() const {
  return _data.size();
}

template<typename T, Size_t S, Size_t P> 
inline
Size_t partitioned_array<T,S,P>::size(const Size_t& p) {
  if (p == 0) return (Size_t) (_partitions[0] - _data.begin());
  if (p < _partitions.size()) return (Size_t) (_partitions[p] - _partitions[p-1]);
  return 0;
}

template<typename T, Size_t S, Size_t P> 
inline
const Size_t& partitioned_array<T,S,P>::partitions() const {
  return _partitions.size();
}

template<typename T, Size_t S, Size_t P> 
inline
const T* partitioned_array<T,S,P>::data(const Size_t& p) {
  if (p == 0) return _data.begin();
  if (p < _partitions.size()) return _partitions[p-1];
  return _data.begin();
}

#endif