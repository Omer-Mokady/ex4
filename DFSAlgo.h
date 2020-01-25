//
// Created by omer on 20/01/2020.
//

#ifndef EX4__DFSALGO_H_
#define EX4__DFSALGO_H_
#include "Searcher.h"
#include <stack>

template<typename T>
class DFSAlgo : public Searcher<T> {
 private:

 public:
  virtual State<T> *Search(Searchable<T> *);

};
template<typename T>
State<T> *DFSAlgo<T>::Search(Searchable<T> *problem) {
  int counterEvaluate = 0;
  typename list<State<T> *>::iterator itList;
  stack<State<T>> stackStates;
  // first element
  State<T> *firstV = problem->getInitialState();
  stackStates.push(*(problem->getInitialState()));
  firstV->setColor('b');
  while (!stackStates.empty()) {
    State<T> v = stackStates.top();
    stackStates.pop();
    counterEvaluate++;
    // check if we found the goal
    if (problem->isGoalState(v)) {
      State<T> *final = new State<T>(&v);
      final->numEvaluate = counterEvaluate;
      return final;
      // if we didn't find the goal
    } else {
      list<State<T> *> adjList = problem->getAllPossibleStates(v);
      itList = adjList.begin();
      // check all neighbors
      while (itList != adjList.end()) {
        // check if the adj was visited brfore
        if ((*(itList))->getColor() != 'b') {
          State<T> *adjV = (*(itList));
          adjV->setColor('b');
          adjV = new State<T>(*(itList));
          adjV->setCameFrom(&v);
          adjV->setPathCost(adjV->getCost()+v.getPathCost());
          stackStates.push(*adjV);
        }
        advance(itList, 1);
      } // end of while loop for adj
    }
  } // end of while loop for taking v from the stack
  return nullptr;
}

#endif //EX4__DFSALGO_H_
