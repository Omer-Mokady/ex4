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
  State<T> *Search(Searchable<T> *s);
  int getNodesNumber();
 private:
  int counter = 0;
  bool isInQueue(State<T> s, set<State<T>> *tracker);
//  bool isInQueue(State<T> *s, set<State<T> *> *tracker);
  bool isInClosedSet(State<T> s, set<State<T>> *closed);
//  bool isInClosedSet(State<T> *s, set<State<T> *> *closed);
  void relocateInQueue(State<T> s, int newCost, priority_queue<State<T>> *q);
//  void relocateInQueue(State<T> *s, int newCost, priority_queue<State<T> *> *q);
  priority_queue<State<T>> *_open = new priority_queue<State<T>>;
//  priority_queue<State<T>> *_open = new priority_queue<State<T>>;
  set<State<T>> *_queueTracker = new set<State<T>>();
//  set<State<T> *> *_queueTracker = new set<State<T> *>();
};

template<typename T>
State<T> *BestFirstSearch<T>::Search(Searchable<T> *s) {
  _open->push(*(s->getInitialState()));
//  _open->push((s->getInitialState()));
  _queueTracker->insert(*(s->getInitialState())); //tracker set - use us to find element in the queue in O(1).
//  _queueTracker->insert((s->getInitialState())); //tracker set - use us to find element in the queue in O(1).
  set<State<T>> *closed = new set<State<T>>();
//  set<State<T> *> *closed = new set<State<T> *>();
  while (_open->size() > 0) {
    State<T> n = _open->top();
//    State<T> *n = _open->top();
    _open->pop();
    counter++;
    _queueTracker->erase(n);
    closed->insert(n);
    if (s->isGoalState(n)) {
      State<T> *ret = new State<T>(&n);
      return ret;
//      return n;
    }
    auto successors = s->getAllPossibleStates(n);
//    auto successors = s->getAllPossibleStates(*n);
    typename list<State<pair<int, int>> *>::iterator it = successors.begin();
    for (it; it != successors.end(); advance(it, 1)) {
//      State<T> *stateDebugger = (*it);
      if (!isInClosedSet(*(*it), closed) && !isInQueue(*(*it), _queueTracker)) { //not in queue and not in closed set.
//      if (!isInClosedSet((*it), closed) && !isInQueue((*it), _queueTracker)) { //not in queue and not in closed set.
        State<T> temp = new State<T>(*it);
        temp.setCameFrom(&n);
//        (*it)->setCameFrom(&n); //update that the successor prev is n.
        temp.setPathCost(n.getPathCost() + (*it)->getCost());
//        (*it)->setPathCost(n.getPathCost() + (*it)->getCost()); //update that the successor path cost is his + so far.
        _open->push(temp);
//        _open->push(*(*it)); //push the successor into the open list.
        _queueTracker->insert(temp);
//        _queueTracker->insert(*(*it)); //push the successor into the tracker set.
      } else {

//        State<T> *stateDebugger2 = (*it);
        State<T> temp2 = new State<T>(*it);
        int currCost = (*it)->getPathCost();
        int optionalCost = (*it)->getCost() + n.getPathCost();
        if (optionalCost < currCost) {
          if (!isInQueue(*(*it), _queueTracker)) {
            temp2.setCameFrom(&n);
//            (*it)->setCameFrom(&n);
            temp2.setPathCost(optionalCost);
//            (*it)->setPathCost(optionalCost);
            _open->push(temp2);
//            _open->push(*(*it));
            _queueTracker->insert(temp2);
//            _queueTracker->insert(*(*it));
          } else {
            relocateInQueue(temp2, optionalCost, _open);
//            relocateInQueue((*(*it)), optionalCost, _open);
          }
        }
      }
    }
  }
}

//
template<typename T>
bool BestFirstSearch<T>::isInQueue(State<T> s, set<State<T>> *tracker) {
  set<State<T>> *copy = tracker;
  typename set<State<T>>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (s.equals(*(it))) {
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
bool BestFirstSearch<T>::isInClosedSet(State<T> s, set<State<T>> *closed) {
  set<State<T>> *copy = closed;
  typename set<State<T>>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (s.equals(*(it))) {
      return true;
    }
  }
  return false;
}

template<typename T>
void BestFirstSearch<T>::relocateInQueue(State<T> s, int newCost, priority_queue<State<T>> *q) {
  priority_queue<State<T>> placeHolder;
  State<T> temp = q->top();
  q->pop();
  if (temp.equals(s)) {
    temp.setCost(newCost);
    q->push(temp);
  } else {
    while (!temp.equals(s)) {
      placeHolder.push(temp);
      temp = q->top();
      q->pop();
    }
    temp.setCost(newCost);
    while (placeHolder.size() > 0) {
      q->push(placeHolder.top());
      placeHolder.pop();
    }
    q->push(temp);
  }

}
template<typename T>
int BestFirstSearch<T>::getNodesNumber() {
  return this->counter;
}

#endif //EX4__BESTFIRSTSEARCH_H_r