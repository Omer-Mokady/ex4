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
#include "BFSAlgo.h"
#include "AstarAlgo.h"

using namespace std;
template<typename P, typename S>
class ObjectAdapter : public Solver<P,S> {
  private:
      Searcher<pair<int,int>>* bFBest = new BestFirstSearch<pair<int,int>>();
      Searcher<pair<int,int>>* dfsAlgo = new DFSAlgo<pair<int,int>>();
      Searcher<pair<int,int>>* bfsAlgo = new BFSAlgo<pair<int,int>>();
      Searcher<pair<int,int>>* aStar = new AstarAlgo<pair<int,int>>();


 public:
  ObjectAdapter();
  ~ObjectAdapter(){};
  S solve(P);
  Solver<P,S> *getClone();

};
template<typename P, typename S>
S ObjectAdapter<P, S>::solve(P problem) {
  State<pair<int,int>>* finalSolution;
  State<pair<int,int>>* dfsSolution = this->dfsAlgo->Search(problem);
  State<pair<int,int>>* bfsSolution = this->bfsAlgo->Search(problem);
  State<pair<int,int>>* bestSolution = (this->bFBest->Search(problem));
  State<pair<int,int>>* astarSolution = (this->bFBest->Search(problem));





  finalSolution = astarSolution;






    cout << "function solve works on ObjectAdapter" << endl;

  return finalSolution;
}
template<typename P, typename S>
ObjectAdapter<P, S>::ObjectAdapter() {

}
template<typename P, typename S>
Solver<P,S> *ObjectAdapter<P, S>::getClone() {
  return new ObjectAdapter<P,S>();
}

#endif //EX4__OBJECTADAPTER_H_
