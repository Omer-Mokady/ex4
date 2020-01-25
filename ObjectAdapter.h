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
#include "AstarNew.h"
using namespace std;
template<typename P, typename S>
class ObjectAdapter : public Solver<P, S> {
 private:
  // BestForSearch algorithm
  Searcher<pair<int, int>> *bFBest = new BestFirstSearch<pair<int, int>>();
  // DFS algorithm
  Searcher<pair<int, int>> *dfsAlgo = new DFSAlgo<pair<int, int>>();
  // BFS algorithm
  Searcher<pair<int, int>> *bfsAlgo = new BFSAlgo<pair<int, int>>();
  // A-Star algorithm
  Searcher<pair<int, int>> *aStar = new AstarNew<pair<int, int>>();

 public:
  /**
   * Constructor
   */
  ObjectAdapter();
  /**
   * Destructor
   */
  ~ObjectAdapter() {};
  S solve(P);
  Solver<P, S> *getClone();

};
template<typename P, typename S>
S ObjectAdapter<P, S>::solve(P problem) {
  State<pair<int, int>> *finalSolution = nullptr;
  State<pair<int, int>> *starSolution = (this->aStar->Search(problem));
  if (starSolution != nullptr) {
    // return value of algo aStar
    finalSolution = starSolution;
  } else {
    State<pair<int, int>> *bestSolution = (this->bFBest->Search(problem));
    if(bestSolution != nullptr) {
      // return value of algo BEST
      finalSolution = bestSolution;
    } else {
      State<pair<int, int>> *dfsSolution = this->dfsAlgo->Search(problem);
      State<pair<int,int>>* bfsSolution = this->bfsAlgo->Search(problem);
      if(bfsSolution == nullptr) {
        // "BFS null. return value of algo DFS
        finalSolution = dfsSolution;
      } else if(dfsSolution == nullptr) {
        // DFS null. return value of algo BFS
        finalSolution = bfsSolution;
      } else {
        if(dfsSolution->getPathCost() < bfsSolution->getPathCost()) {
          // DFS path is better than BFS. return value of algo DFS
          finalSolution = dfsSolution;
        } else {
          // BFS path is better than DFS. return value of algo BFS
          finalSolution = bfsSolution;
        }
      }
    }
  }
  return finalSolution;
}
template<typename P, typename S>
ObjectAdapter<P, S>::ObjectAdapter() {

}
template<typename P, typename S>
Solver<P, S> *ObjectAdapter<P, S>::getClone() {
  return new ObjectAdapter<P, S>();
}

#endif //EX4__OBJECTADAPTER_H_
