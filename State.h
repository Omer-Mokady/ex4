//
// Created by gal on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_
#include <functional>

template <typename T>

class State{
 public:
  State(int cost, int x, int y);
 private:
//  pair<T,T> state;
  State<T> cameFrom;
  int cost;
};
template <typename T>
State<T>::State(int cost, int x, int y) {
  this->cameFrom = nullptr;
  this->cost = cost;
//  this->state =
}
#endif //EX4__STATE_H_