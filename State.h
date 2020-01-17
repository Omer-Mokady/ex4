//
// Created by gal on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_
#include <functional>

template <typename T>
class State{
 public:
  State(int cost, T state);
 private:
  T curState;
  State<T> cameFrom;
  int cost;
};
template <typename T>
State<T>::State(int cost1, T state) {
  this->cameFrom = nullptr;
  this->cost = cost1;
  this->curState = state;
//  this->state =
}
#endif //EX4__STATE_H_
