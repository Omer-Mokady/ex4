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
//  unordered_map<string, int> simToIndexTable;
//  stack<State<pair<int,int>>> stackStates;
//  stackStates.push(*(problem->getInitialState()));
//  while(!stackStates.empty()) {
//    State<pair<int,int>> v = stackStates.top();
//    stackStates.pop();
//    if(problem->isGoalState(v)) {
//      State<pair<int,int>> *final = &v;
//      return final;
//    } else {
//      list<State<pair<int, int>> *> adjList = problem->getAllPossibleStates();
//      list<State<pair<int, int>> *>::iterator it;
////      while(it != cacheList.end()) {
////        func(itList->second);
////
////
////
////
////        advance(it,1);
////
////    }
//  }
//





  return nullptr;
}

#endif //EX4__DFSALGO_H_
