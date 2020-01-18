//
// Created by gal on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_
#include <functional>

template <typename T>
class State{
  //end
 public:
  bool equals(State<T> state1);
  State(int cost, T state);
  int getCost();
  T getCurState();
  State<T>* getCameFrom();
  void setCameFrom(State<T>* prevState);
 private:
  T curState;
  State<T>* cameFrom;
  int cost;
};
template <typename T>
State<T>::State(int cost1, T state) {
  this->cameFrom = nullptr;
  this->cost = cost1;
  this->curState = state;
//  this->state =
}
template<typename T>
int State<T>::getCost() {
  return this->cost;
}
template<typename T>
T State<T>::getCurState() {
  return this->curState;
}
template<typename T>
State<T>* State<T>::getCameFrom() {
  return this->cameFrom;
}
template<typename T>
void State<T>::setCameFrom(State<T> * prevState) {
  this->cameFrom = prevState;
}
template<typename T>
bool State<T>::equals(State<T> state1) {
  return (state1.getCurState() == this->curState);
}

#endif //EX4__STATE_H_
