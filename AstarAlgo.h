//
// Created by gal on 21/01/2020.
//

#ifndef EX4__ASTARALGO_H_
#define EX4__ASTARALGO_H_
#include <iostream>
#include <unordered_set>
#include <list>
#include <set>
#include "Searcher.h"
#include "Searchable.h"
#include "State.h"
template<typename T>
class AstarAlgo : public Searcher<T> {
 public:
  virtual ~AstarAlgo() {};
  State<T> *Search(Searchable<T> *s);
  int getNodesNumber();
 private:
  bool hasChanged = false; //use to track finding a node in one of our sets.
  int calculateHeuristic(State<T> first, State<T> goal);
  int counter = 0;
  set<State<T>, greater<>> *_open = new set<State<T>, greater<>>();
  set<State<T>> *_closed = new set<State<T>>();
};
template<typename T>
State<T> *AstarAlgo<T>::Search(Searchable<T> *s) {
  State<T> goalState = new State<T>(s->getGoalState());
  _open->insert(*(s->getInitialState()));
  while (_open->size() > 0) {
    State<T> q = *(_open->begin());
    counter++;
    _open->erase(q);
    if (s->isGoalState(q)) {
      State<T> *ret = new State<T>(&q);
      return ret;
    }
    auto successors = s->getAllPossibleStates(q);
    typename list<State<pair<int, int>> *>::iterator it = successors.begin();
    for (it; it != successors.end(); advance(it, 1)) {
      State<T> temp = new State<T>(*it);
      temp.setCameFrom(&q);
      temp.setPathCost(q.getPathCost() + (*it)->getCost()); //this is the g
      temp.setHeuristic(calculateHeuristic(temp, goalState)); // this is the h
      if (s->isGoalState(*it)) {
        State<T> *ret = new State<T>(&temp);
        return ret;
      }
      for (typename set<State<T>>::iterator it = _open->begin(); it != _open->end(); advance(it, 1)) {
        if (temp.equals(*it)) {
          if (calculateHeuristic(temp, goalState) < calculateHeuristic((*it), goalState)) {
            _open->erase(it);
            counter++;
            _open->insert(temp);
            hasChanged = true;
          }
        }
      }
      for (typename set<State<T>>::iterator it = _closed->begin(); it != _closed->end(); advance(it, 1)) {
        if (temp.equals(*it)) {
          if (calculateHeuristic(temp, goalState) < calculateHeuristic((*it), goalState)) {
            _closed->erase(it);
            _open->insert(temp);
            hasChanged = true;
          }
        }
      }
      if (!hasChanged) {
        hasChanged = false;
        _open->insert(temp);
      }
    }
    _closed->insert(q);
  }
}
template<typename T>
int AstarAlgo<T>::calculateHeuristic(State<T> curr, State<T> goal) {
  return abs(curr.getCurState().first - goal.getCurState().first)
      + abs(curr.getCurState().second - goal.getCurState().second);
}
template<typename T>
int AstarAlgo<T>::getNodesNumber() {
  return this->counter;
}

#endif //EX4__ASTARALGO_H_
