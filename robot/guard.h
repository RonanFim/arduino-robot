#ifndef __GUARD_H__
#define __GUARD_H__

struct guard {

  guard() : __lock(0) {}
  
  inline bool is_locked() { return __lock; }
  inline bool is_released() { return !__lock; }
  
  inline void lock() { __lock = 1; }
  inline void release() { __lock = 0; }
  inline void revert() { __lock = !__lock; }

private:
  bool __lock;
};

#endif
