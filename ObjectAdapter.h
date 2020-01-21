//
// Created by omer on 18/01/2020.
//

#ifndef EX4__OBJECTADAPTER_H_
#define EX4__OBJECTADAPTER_H_
#include "Solver.h"
#include "Searcher.h"
#include <iostream>
#include "BestFirstSearch.h"
#include "DFSAlgo.h"

using namespace std;
template<typename P, typename S>
class ObjectAdapter : public Solver<P,S> {
  private:
      Searcher<pair<int,int>>* BFBest = new BestFirstSearch<pair<int,int>>();
      Searcher<pair<int,int>>* dsfAlgo = new DFSAlgo<pair<int,int>>();

 public:
  ObjectAdapter();
  ~ObjectAdapter(){};
  S solve(P);
};
template<typename P, typename S>
S ObjectAdapter<P, S>::solve(P problem) {
  cout << "in OA, going to DFS" << endl;
//  this->dsfAlgo->Search(problem);
  State<pair<int,int>>* tempSolution = (this->BFBest->Search(problem));
//  State<pair<int,int>> tempSolution = (this->BFBest->Search(problem));
//  State<pair<int,int>>* finalSolution = &tempSolution;




//  State<pair<int,int>>* finalSolution = &tempSolution;
//  State<pair<int,int>>
    cout << "function solve works on ObjectAdapter" << endl;
//    return finalSolution;
  //temp - to replace the return value
//  return (this->BFBest->Search(problem));
//good
  return tempSolution;
}
template<typename P, typename S>
ObjectAdapter<P, S>::ObjectAdapter() {

}

#endif //EX4__OBJECTADAPTER_H_
