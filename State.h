//
// Created by gal on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_
#include <functional>
#include <string>
#include <string.h>
using namespace std;
template<typename T>
class State {
  //end
 public:
  bool equals(State<T> state1);
  State(int cost, T state);
  State();
  State(State<T> *other);
  int getCost();
  T getCurState();
  State<T> *getCameFrom();
  void setCameFrom(State<T> *prevState);
  void setCost(int cost);

//  //added by gal on 18.1
  bool operator<(const State<T> &other) const {
    if (pathCost != other.pathCost) {
      return (pathCost > other.pathCost);
    }
    return (cost > other.pathCost);
  }

  bool operator==(const State<T> &other) const;
  void setColor(string color);
  int getPathCost();
  void setPathCost(int cost);
  string getColor();
  int getHeuristic();
  void setHeuristic(int newHeuristic);
 private:

  T curState;
  State<T> *cameFrom;
  int cost;
  int pathCost;
  int heuristic;
  string _color;
};
template<typename T>
State<T>::State(int cost1, T state) {
  this->cameFrom = nullptr;
  this->cost = cost1;
  this->pathCost = 0;
  this->curState = state;
  this->_color = "white";
  this->heuristic = 0;
}

template<typename T>
State<T>::State(State<T> *other) {
  this->cameFrom = other->cameFrom;
  this->cost = other->getCost();
  this->pathCost = other->getPathCost();
  this->curState = other->getCurState();
  this->_color = other->getColor();
  this->heuristic = other->getHeuristic();
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
State<T> *State<T>::getCameFrom() {
  return this->cameFrom;
}
template<typename T>

void State<T>::setCameFrom(State<T> *prevState) {
  State<T> *temp = new State<T>(prevState);
  this->cameFrom = temp;
}
template<typename T>
bool State<T>::equals(State<T> state1) {
  return (state1.getCurState() == this->curState);
}

template<typename T>
bool State<T>::operator==(const State<T> &other) const {
  return (pathCost == other.getPathCost());
}
template<typename T>
void State<T>::setColor(string color) {
  _color = color;
}
template<typename T>
string State<T>::getColor() {
  return _color;
}
template<typename T>
void State<T>::setCost(int cost) {
  this->cost = cost;
}
template<typename T>
int State<T>::getPathCost() {
  return this->pathCost;
}
template<typename T>
void State<T>::setPathCost(int cost) {
  this->pathCost = cost;
}
template<typename T>
State<T>::State() {

}
template<typename T>
int State<T>::getHeuristic() {
  return this->heuristic;
}
template<typename T>
void State<T>::setHeuristic(int newHeuristic) {
  this->heuristic = newHeuristic;
}

#endif //EX4__STATE_H_
