//
// Created by omer on 21/01/2020.
//

#ifndef EX4__BFSALGO_H_
#define EX4__BFSALGO_H_
#include "Searcher.h"

template<typename T>
class BFSAlgo : public Searcher<T> {
 private:

 public:
  virtual State<T>* Search(Searchable<T> *);
};
template<typename T>
State<T> *BFSAlgo<T>::Search(Searchable<T> *problem) {
  int counterEvaluate = 0;
  typename list<State<T>*>::iterator itList;
  queue<State<T>> qStates;
  // first element
  State<T> *firstV = problem->getInitialState();
  qStates.push(*(problem->getInitialState()));
  firstV->setColor('B');
  while(!qStates.empty()) {
    State<T> v = qStates.front();
    qStates.pop();
    counterEvaluate++;
    // check if we found the goal
    if(problem->isGoalState(v)) {
      State<T> *final = new State<T>(&v);
      final->numEvaluate = counterEvaluate;
      return final;
      // if we didn't find the goal
    } else {
      list<State<T>*> adjList = problem->getAllPossibleStates(v);
      itList = adjList.begin();
      // check all neighbors
      while(itList!=adjList.end()) {
        // check if the adj was visited brfore
        if((*(itList))->getColor()!='B') {
          State<T> *adjV = (*(itList));
          adjV->setColor('B');
          adjV = new State<T>(*(itList));
          adjV->setCameFrom(&v);
          adjV->setPathCost(adjV->getCost()+v.getPathCost());
          qStates.push(*adjV);
        }
        advance(itList, 1);
      } // end of while loop for adj
    }
  } // end of while loop for taking v from the stack
  // if we didn't find our goal
  return nullptr;
}

#endif //EX4__BFSALGO_H_
