//
// Created by gal on 23/01/2020.
//

#ifndef EX4__QUEUECOMPARATOR_H_
#define EX4__QUEUECOMPARATOR_H_
#include "State.h"

/**
 * a comparator between two objects from type State<T> by their f value.
 * use us for controlling the flow of the A Star search algorithm.
 * @tparam T the parameter of state.
 */
template<typename T>
struct Comparator {
  bool operator()(const State<T> &first, const State<T> &second) const {
    return first.getConstF() < second.getConstF();
  }
};
#endif //EX4__QUEUECOMPARATOR_H_
