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


  typename list<State<T>*>::iterator itList;
  queue<State<T>> qStates;
  State<T> *firstV = problem->getInitialState();
//  stackStates.push(*(firstV));
//  firstV->setColor('b');
  qStates.push(*(problem->getInitialState()));
//  stackStates.push(*(problem->getInitialState()));
  firstV->setColor('B');
  while(!qStates.empty()) {
    State<T> v = qStates.front();
    qStates.pop();
    // check if we found the goal
    if(problem->isGoalState(v)) {
      State<T> *final = new State<T>(&v);
      return final;
      // if we didn't find the goal
    } else {
      list<State<T>*> adjList = problem->getAllPossibleStates(v);
      itList = adjList.begin();
      // check all neighbors
      while(itList!=adjList.end()) {
        // check if the adj was visited brfore
//        char a = (*(itList))->getColor();
        if((*(itList))->getColor()!='B') {
          State<T> *adjV = (*(itList));
          adjV->setColor('B');
          adjV = new State<T>(*(itList));
          cout << "check" << endl;
          adjV->setCameFrom(&v);
          qStates.push(*adjV);
          cout << "check color" << endl;
        }
        advance(itList, 1);
      } // end of while loop for adj
    }
    cout << "inside while that waiting for empty stack" << endl;

  } // end of while loop for taking v from the stack
  cout << "error: didn't find the goal" << endl;
  return nullptr;
}

#endif //EX4__BFSALGO_H_
