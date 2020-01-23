//
// Created by gal on 23/01/2020.
//

#ifndef EX4__QUEUECOMPERATOR_H_
#define EX4__QUEUECOMPERATOR_H_
#include "State.h"
template<typename T>
struct Comperator {
  bool operator()(const State<T> &first, const State<T> &second) const {
    return first.getConstF() < second.getConstF();
  }
};
#endif //EX4__QUEUECOMPERATOR_H_
