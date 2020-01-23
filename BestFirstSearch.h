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
  bool isInQueue(State<T> s, multiset<State<T>> *tracker);
  bool isInClosedSet(State<T> s, multiset<State<T>> *closed);
  void relocateInQueue(State<T> s, int newCost, priority_queue<State<T>> *q);
  priority_queue<State<T>> *_open = new priority_queue<State<T>>;
  multiset<State<T>> *_queueTracker = new multiset<State<T>>();
};

template<typename T>
State<T> *BestFirstSearch<T>::Search(Searchable<T> *s) {
  _open->push(*(s->getInitialState()));
  _queueTracker->insert(*(s->getInitialState())); //tracker set - use us to find element in the queue in O(1).
  multiset<State<T>> *closed = new multiset<State<T>>(); // set of closed State<T>.
  while (_open->size() > 0) {
    State<T> n = _open->top(); //the top of the priority queue.
    _open->pop();
    counter++;
    _queueTracker->erase(n);
    closed->insert(n);
    if (s->isGoalState(n)) {
      State<T> *ret = new State<T>(&n);
      cout << "found solution in BestFS" << endl;
      return ret;
    }
    auto successors = s->getAllPossibleStates(n); // creating list of adjacent cells in matrix.
    typename list<State<pair<int, int>> *>::iterator it = successors.begin();
    for (it; it != successors.end(); advance(it, 1)) {
      if (!isInClosedSet(*(*it), closed) && !isInQueue(*(*it), _queueTracker)) { //not in queue and not in closed set.
        State<T> temp = new State<T>(*it);
        temp.setCameFrom(&n); //setting the previous as n.
        temp.setPathCost(n.getPathCost() + (*it)->getCost());
        _open->push(temp);
        _queueTracker->insert(temp);
        // else - we need to check if the path from n is a batter way to get to the successor than what we have now.
      } else {
        State<T> temp2 = new State<T>(*it);
        int currCost = (*it)->getPathCost(); //current path cost.
        int optionalCost = (*it)->getCost() + n.getPathCost(); // the cost if we were arrived to this cell from n.
        if (optionalCost < currCost) {
          if (!isInQueue(*(*it), _queueTracker)) {
            temp2.setCameFrom(&n);
            temp2.setPathCost(optionalCost);
            _open->push(temp2);
            _queueTracker->insert(temp2);
          } else {
            relocateInQueue(temp2, optionalCost, _open); //
          }
        }
      }
    }
  }
}

//
template<typename T>
bool BestFirstSearch<T>::isInQueue(State<T> s, multiset<State<T>> *tracker) {
  multiset<State<T>> *copy = tracker;
  typename multiset<State<T>>::iterator it = copy->begin();
  for (it; it != copy->end(); advance(it, 1)) {
    if (s.equals(*(it))) {
//      cout << "found it!" << endl;
      return true;
    }
  }
//  if (tracker->find(s) != tracker->end()) {
//    return true;
//  }
  return false;
}

template<typename T>
bool BestFirstSearch<T>::isInClosedSet(State<T> s, multiset<State<T>> *closed) {
  multiset<State<T>> *copy = closed;
  typename multiset<State<T>>::iterator it = copy->begin();
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