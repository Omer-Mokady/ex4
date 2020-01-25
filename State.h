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
 public:
  int f;
  // evaluate value from algorithm
  int numEvaluate = 0;
  /**
   * a getter to the f value in A Star.
   * @return this f value as const for the QueueComparator.h use.
   */
  int getConstF() const {
    return this->f;
  }
  /**
   * a getter to the f value in A Star.
   * @return this f value.
   */
  int getF() {
    return this->f;
  }
  /**
   * a setter for the f value field.
   * @param val the value we want our state to hold.
   */
  void setF(int val) {
    this->f = val;
  }
  /**
   * check if State objects are equal.
   * @param state1  certain state
   * @return boolean answer
   */
  bool equals(State<T> state1);
  /**
   * Constructor
   * @param cost value of certain state
   * @param state currentState (location. index)
   */
  State(int cost, T state);
  /**
   * Constructor
   */
  State();
  /**
   * Structor. make a copy
   * @param other other state
   */
  State(State<T> *other);
  /**
   * get cost value
   * @return cost value
   */
  int getCost();
  /**
   * get current state value (location)
   * @return current state value (location)
   */
  T getCurState();
  /**
   * get the State object that we came from
   * @return State object that we came from
   */
  State<T> *getCameFrom();
  /**
   * Set the State object that we came from
   * @param prevState State object that we came from
   */
  void setCameFrom(State<T> *prevState);
  /**
   * set cost value
   * @param cost cost value
   */
  void setCost(int cost);
  /**
   * a lessThan override for states.
   * @param other the object we want to compare this with.
   * @return true if this > other, false otherwise.
   */
  bool operator<(const State<T> &other) const {
    if (pathCost != other.pathCost) {
      return (pathCost > other.pathCost);
    }
    return (cost > other.pathCost);
  }
  /**
   * an equal comparator override.
   * @param other the object we want to compare this with.
   * @return true if both have the same coordinates, false otherwise.
   */
  bool operator==(const State<T> &other) const;
  /**
   * set color value
   * @param color color value
   */
  void setColor(char color);
  /**
   * get sum of path cost
   * @return sum of path cost
   */
  int getPathCost();
  /**
   * set sum of path cost
   * @param cost sum of path cost
   */
  void setPathCost(int cost);
  /**
   * get color value
   * @return color value
   */
  char getColor();
  /**
   * get Heuristic value
   * @return Heuristic value
   */
  int getHeuristic();
  /**
   * set Heuristic value
   * @param newHeuristic Heuristic value
   */
  void setHeuristic(int newHeuristic);
 private:
  // current state (location)
  T curState;
  // the state where we came from
  State<T> *cameFrom;
  // cost value
  int cost;
  // path cost value
  int pathCost;
  // heuristic value
  int heuristic;
  // color value
  char color;
};

template<typename T>
State<T>::State(int cost1, T state) {
  this->cameFrom = nullptr;
  this->cost = cost1;
  this->pathCost = 0;
  this->curState = state;
  this->color = 'w';
  this->heuristic = 0;
  this->f = 0;
}

template<typename T>
State<T>::State(State<T> *other) {
  this->cameFrom = other->cameFrom;
  this->cost = other->getCost();
  this->pathCost = other->getPathCost();
  this->curState = other->getCurState();
  this->color = other->getColor();
  this->heuristic = other->getHeuristic();
  this->f = other->getF();
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
//  return (state1.getCurState() == this->curState);
  return (state1.getCurState().first == this->curState.first && state1.getCurState().second == this->curState.second);
}

template<typename T>
bool State<T>::operator==(const State<T> &other) const {
  return (pathCost == other.getPathCost());
}

template<typename T>
void State<T>::setColor(char color1) {
  this->color = color1;
}
template<typename T>
char State<T>::getColor() {
  return this->color;
}
template<typename T>
void State<T>::setCost(int cost1) {
  this->cost = cost1;
}
template<typename T>
int State<T>::getPathCost() {
  return this->pathCost;
}
template<typename T>
void State<T>::setPathCost(int cost1) {
  this->pathCost = cost1;
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
