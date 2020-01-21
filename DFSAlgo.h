//
// Created by omer on 20/01/2020.
//

#ifndef EX4__DFSALGO_H_
#define EX4__DFSALGO_H_
#include "Searcher.h"
#include <stack>
#include <unordered_map>


template<typename T>
class DFSAlgo : public Searcher<T> {
 private:

 public:
  virtual State<T>* Search(Searchable<T> *);

};
template<typename T>
State<T> *DFSAlgo<T>::Search(Searchable<T> * problem) {
  typename list<State<T>*>::iterator itList;
  stack<State<T>> stackStates;
  State<T> *firstV = problem->getInitialState();
//  stackStates.push(*(firstV));
//  firstV->setColor('b');

  stackStates.push(*(problem->getInitialState()));
  firstV->setColor('b');
  while(!stackStates.empty()) {
    State<T> v = stackStates.top();
    stackStates.pop();
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
        if((*(itList))->getColor()!='b') {
          State<T> *adjV = (*(itList));
          adjV->setColor('b');
          adjV = new State<T>(*(itList));
          cout << "check" << endl;
          adjV->setCameFrom(&v);
          stackStates.push(*adjV);
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

#endif //EX4__DFSALGO_H_
