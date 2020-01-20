//
// Created by gal on 18/01/2020.
//

#ifndef EX4__BESTFIRSTSEARCH_H_
#define EX4__BESTFIRSTSEARCH_H_
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

template<typename T>
class BestFirstSearch : public Searcher<T> {
 public:
  virtual ~BestFirstSearch() {};
  State<T> Search(Searchable<T> *s);
 private:
  bool isInQueue(State<T> *s, set<State<T> *> *tracker);
  bool isInClosedSet(State<T> *s, set<State<T> *> *closed);
  void relocateInQueue(State<T> *s, int newCost, priority_queue<State<T> *> *q);
  priority_queue<State<T> *> *_open = new priority_queue<State<T> *>;
  set<State<T> *> *_queueTracker = new set<State<T> *>();
};

template<typename T>
/**
 * TO DO LIST:
 * create "return back trace" in State.h.
 */
State<T> BestFirstSearch<T>::Search(Searchable<T> *s) {
  _open->push((s->getInitialState()));
  _queueTracker->insert((s->getInitialState())); //tracker set - use us to find element in the queue in O(1).
  set<State<T> *> *closed = new set<State<T> *>();
  while (_open->size() > 0) {
    State<T> *n = _open->top();
    _open->pop();
    _queueTracker->erase(n);
    closed->insert(n);
    if (s->isGoalState(*n)) {
      return *n;
    }
    auto successors = s->getAllPossibleStates(*n);
    typename list<State<pair<int, int>> *>::iterator it = successors.begin();
    for (it; it != successors.end(); advance(it, 1)) {
//      State<T> *stateDebugger = (*it);
      if (!isInClosedSet((*it), closed) && !isInQueue((*it), _queueTracker)) { //not in queue and not in closed set.
        (*it)->setCameFrom(n); //update that the successor prev is n.
        (*it)->setPathCost(n->getPathCost() + (*it)->getCost()); //update that the successor path cost is his + so far.
        _open->push((*it)); //push the successor into the open list.
        _queueTracker->insert((*it)); //push the successor into the tracker set.
      } else {
        (*it)->setCameFrom(n);
//        State<T> *stateDebugger2 = (*it);
        int currCost = (*it)->getPathCost();
        int optionalCost = (*it)->getCost() + (*it)->getCameFrom()->getPathCost();
        if (optionalCost < currCost) {
          if (!isInQueue((*it), _queueTracker)) {
            (*it)->setPathCost(optionalCost);
            _open->push((*it));
            _queueTracker->insert((*it));
          } else {
            relocateInQueue(((*it)), optionalCost, _open);
          }
        }
      }
    }
  }
}

//
template<typename T>
bool BestFirstSearch<T>::isInQueue(State<T> *s, set<State<T> *> *tracker) {
  set<State<T> *> *copy = tracker;
  typename set<State<T> *>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (s->equals(*(*(it)))) {
      cout << "found it!" << endl;
      return true;
    }
  }
//  if (tracker->find(s) != tracker->end()) {
//    return true;
//  }
  return false;
}

template<typename T>
bool BestFirstSearch<T>::isInClosedSet(State<T> *s, set<State<T> *> *closed) {
  set<State<T> *> *copy = closed;
  typename set<State<T> *>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (s->equals(*(*(it)))) {
      cout << "found it!" << endl;
      return true;
    }
  }
//  if (closed->find(s) != closed->end()) { // testing this.
//    return true;
//  }
  return false;
}

template<typename T>
void BestFirstSearch<T>::relocateInQueue(State<T> *s, int newCost, priority_queue<State<T> *> *q) {
  priority_queue<State<T> *> placeHolder;
  State<T> *temp = q->top();
  q->pop();
  if (temp->equals(*s)) {
    temp->setCost(newCost);
    q->push(temp);
  } else {
    while (!temp->equals(*s)) {
      placeHolder.push(temp);
      temp = q->top();
      q->pop();
    }
    temp->setCost(newCost);
    while (placeHolder.size() > 0) {
      q->push(placeHolder.top());
      placeHolder.pop();
    }
    q->push(temp);
  }

}

#endif //EX4__BESTFIRSTSEARCH_H_r
