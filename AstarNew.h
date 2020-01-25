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
#include "QueueComparator.h"
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
  multiset<State<T>, Comparator<T>> *_open = new multiset<State<T>, Comparator<T>>();
  multiset<State<T>> *_closed = new multiset<State<T>>();
  bool isInOpenSet(State<T> state, multiset<State<T>, Comparator<T>> *Q);
  bool isInClosedSet(State<T> state, multiset<State<T>> *C);
  int calculateHeuristic(State<T> curr, State<T> goal);
};
/**
 * described in Searcher.h.
 * @tparam T the parameter of the State and the Searchable objects.
 */
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
    for (; it != successors.end(); advance(it, 1)) {// for every adjacent to q.
      inOpen = false;
      inClosed = false;
      State<T> successor = new State<T>(*it);
      int optionalPathCost = successor.getCost() + q.getPathCost();
      if (isInClosedSet(successor, _closed)) { // check if in closed list.
        inClosed = true;
      }
      if (isInOpenSet(successor, _open)) { // check if in open list.
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

/**
 * search and find if a given state is in our _open multiset.
 * @tparam T the state object parameter.
 * @param state the object we want to find in the set.
 * @param Q the multiset we want to look in for the state.
 * @return true if we found it, false otherwise.
 */
template<typename T>
bool AstarNew<T>::isInOpenSet(State<T> state, multiset<State<T>, Comparator<T>> *Q) {
  multiset<State<T>, Comparator<T>> *copy = Q;
  typename multiset<State<T>>::iterator it = copy->begin();
  for (; it != copy->end(); advance(it, 1)) {
    if (state.equals(*it)) {
      return true;
    }
  }
  return false;
}
/**
 * search and find if a given state is in our _closed multiset.
 * @tparam T the state object parameter.
 * @param s the object we want to find in the set.
 * @param closed the multiset we want to look in for state s.
 * @return true if we found it, false otherwise.
 */
template<typename T>
bool AstarNew<T>::isInClosedSet(State<T> state, multiset<State<T>> *C) {
  multiset<State<T>> *copy = C;
  typename multiset<State<T>>::iterator it = copy->begin();
  for (; it != copy->end(); advance(it, 1)) {
    if (state.equals(*it)) {
      return true;
    }
  }
  return false;
}
/**
 * in this algorithm the heuristic function is a cartesian function, based on the distance between a location to the
 * goal state of the given problem.
 * @tparam T the parameter of the States.
 * @param curr the current place - we want his heuristic value.
 * @param goal the goal place.
 * @return the distance on a cartesian greed between the current state to goal state.
 */
template<typename T>
int AstarNew<T>::calculateHeuristic(State<T> curr, State<T> goal) {
  return abs(curr.getCurState().first - goal.getCurState().first)
      + abs(curr.getCurState().second - goal.getCurState().second);
}
/**
 * returning the number of nodes we work on them during the search.
 * @tparam T the parameter of the Searcher.
 * @return the number of nodes we work on them during the search.
 */
template<typename T>
int AstarNew<T>::getNodesNumber() {
  return this->counter;
}

#endif //EX4__ASTARNEW_H_
