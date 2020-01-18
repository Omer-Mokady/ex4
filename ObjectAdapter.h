//
// Created by omer on 18/01/2020.
//

#ifndef EX4__OBJECTADAPTER_H_
#define EX4__OBJECTADAPTER_H_
#include "Solver.h"
#include "Searcher.h"
using namespace std;
template<typename P, typename S>
class ObjectAdapter {
  private:
  //    Searcher<pair<int,int>,S>* algo1;
  public:
  ~ObjectAdapter(){};
  S solve(P);
};

#endif //EX4__OBJECTADAPTER_H_
