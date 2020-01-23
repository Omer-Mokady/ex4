//
// Created by gal on 23/01/2020.
//

#ifndef EX4__ASTARNEW_H_
#define EX4__ASTARNEW_H_
#include "Searcher.h"
#include "Searchable.h"
#include <string.h>
#include <string>
#include <functional>
#include <iostream>
#include "State.h"
#include <set>
#include <unordered_set>
#include <iterator>
#include <list>
#include "QueueComperator.h"
template<typename T>
class AstarNew : public Searcher<T> {
 public:
  virtual ~AstarNew() {};
  State<T> *Search(Searchable<T> *s);
  int getNodesNumber();
 private:
  //fields
  int counter = 0;
  bool inOpen = false;
  bool inClosed = false;
  multiset<State<T>, Comperator<T>> *_open = new multiset<State<T>, Comperator<T>>();
//  priority_queue<State<T>> *_open = new priority_queue<State<T>>;
//  multiset<State<T>> *_queueTracker = new multiset<State<T>>();
  multiset<State<T>> *_closed = new multiset<State<T>>();

  bool isInOpenQueue(State<T> state, multiset<State<T>, Comperator<T>> *Q);
  bool isInClosedSet(State<T> state, multiset<State<T>> *C);
  int calculateHeuristic(State<T> first, State<T> goal);
};
//////////////////start of Search///////////////////////
template<typename T>
State<T> *AstarNew<T>::Search(Searchable<T> *s) {
  s->getInitialState()->setPathCost(0);
  s->getInitialState()->setHeuristic(calculateHeuristic(*(s->getInitialState()), *(s->getGoalState())));
  s->getInitialState()->setF(s->getInitialState()->getHeuristic() + s->getInitialState()->getPathCost());
  _open->insert(*(s->getInitialState()));
  while (_open->size() > 0) {
    State<T> q = *(_open->begin());
    _open->erase(_open->begin());
    counter++;
    if (q.equals(*(s->getGoalState()))) {
      State<T> *ret = new State<T>(&q);
      return ret;
    }
    _closed->insert(q);
    auto successors = s->getAllPossibleStates(q);
    typename list<State<pair<int, int>> *>::iterator it = successors.begin();
    for (it; it != successors.end(); advance(it, 1)) {// for every adjacent to q.
      inOpen = false;
      inClosed = false;
      State<T> successor = new State<T>(*it);
      int optionalPathCost = successor.getCost() + q.getPathCost();
      if (isInClosedSet(successor, _closed)) { // check if in closed list.
        inClosed = true;
      }
      if (isInOpenQueue(successor, _open)) { // check if in open list.
        inOpen = true;
      }
      if (!inOpen && !inClosed) { // not in both of the list.
        successor.setCameFrom(&q);
        successor.setPathCost(optionalPathCost);
        successor.setHeuristic(calculateHeuristic(successor, *(s->getGoalState())));
        successor.setF(successor.getPathCost() + successor.getHeuristic());
        _open->insert(successor);
      } else {
        inClosed = false;
        if (optionalPathCost < successor.getPathCost()) {
          successor.setCameFrom(&q);
          successor.setPathCost(optionalPathCost);
          successor.setHeuristic(calculateHeuristic(successor, *(s->getGoalState())));
          successor.setF(successor.getPathCost() + successor.getHeuristic());
          if (inOpen) {
            inOpen = false;
            _open->erase(*(*it));
            _open->insert(successor);
          } else {
            _open->insert(successor);
          }
        }
      }
      if (s->isGoalState(successor)) {
        State<T> *ret = new State<T>(&successor);
        ret->numEvaluate = this->getNodesNumber();
        return ret;
      }
    } //end of successors for loop.
  } // end of while loop.
  return nullptr;
}
//////////////////end of Search///////////////////////

template<typename T>
bool AstarNew<T>::isInOpenQueue(State<T> state, multiset<State<T>, Comperator<T>> *Q) {
  multiset<State<T>, Comperator<T>> *copy = Q;
  typename multiset<State<T>>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (state.equals(*it)) {
      return true;
    }
  }
  return false;
}
template<typename T>
bool AstarNew<T>::isInClosedSet(State<T> state, multiset<State<T>> *C) {
  multiset<State<T>> *copy = C;
  typename multiset<State<T>>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (state.equals(*it)) {
      return true;
    }
  }
  return false;
}
template<typename T>
int AstarNew<T>::calculateHeuristic(State<T> curr, State<T> goal) {
  return abs(curr.getCurState().first - goal.getCurState().first)
      + abs(curr.getCurState().second - goal.getCurState().second);
}
template<typename T>
int AstarNew<T>::getNodesNumber() {
  return this->counter;
}

#endif //EX4__ASTARNEW_H_
