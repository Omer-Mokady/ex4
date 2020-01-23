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
  Searcher<pair<int, int>> *bFBest = new BestFirstSearch<pair<int, int>>();
  Searcher<pair<int, int>> *dfsAlgo = new DFSAlgo<pair<int, int>>();
  Searcher<pair<int, int>> *bfsAlgo = new BFSAlgo<pair<int, int>>();
  Searcher<pair<int, int>> *aStar = new AstarNew<pair<int, int>>();
//  Searcher<pair<int, int>> *aStar = new AstarAlgo<pair<int, int>>();
//  BestFirstSearch<pair<int, int>> *bFBest = new BestFirstSearch<pair<int, int>>();

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


//  cout << "evaluate for bestForSearch: " << bestSolution->numEvaluate << endl;

//  State<pair<int, int>> *astarSolution = (this->aStar->Search(problem));
  State<pair<int, int>> *starSolution = (this->aStar->Search(problem));
  if (starSolution != nullptr) {
    finalSolution = starSolution;
    cout << "return value of algo aStar" << endl;
  } else {
    State<pair<int, int>> *bestSolution = (this->bFBest->Search(problem));
    if(bestSolution != nullptr) {
      cout << "return value of algo BEST" << endl;
      finalSolution = bestSolution;
    } else {
      cout << "best is null" << endl;
      State<pair<int, int>> *dfsSolution = this->dfsAlgo->Search(problem);
      State<pair<int,int>>* bfsSolution = this->bfsAlgo->Search(problem);
      if(bfsSolution == nullptr) {
        cout << "BFS null. return value of algo DFS" << endl;
        finalSolution = dfsSolution;
      } else if(dfsSolution == nullptr) {
        cout << "DFS null. return value of algo BFS" << endl;
        finalSolution = bfsSolution;
      } else {
        if(dfsSolution->getPathCost() < bfsSolution->getPathCost()) {
          cout << "evaluate for dfs: " << dfsSolution->getPathCost() << endl;
          cout << "evaluate for bfs: " << bfsSolution->getPathCost() << endl;
          cout << "DFS path is better than BFS. return value of algo DFS" << endl;
          finalSolution = dfsSolution;
        } else {
          cout << "evaluate for dfs: " << dfsSolution->getPathCost() << endl;
          cout << "evaluate for bfs: " << bfsSolution->getPathCost() << endl;
          cout << "BFS path is better than DFS. return value of algo BFS" << endl;
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
