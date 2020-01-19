//
// Created by omer on 18/01/2020.
//

#ifndef EX4__OBJECTADAPTER_H_
#define EX4__OBJECTADAPTER_H_
#include "Solver.h"
#include "Searcher.h"
#include <iostream>

using namespace std;
template<typename P, typename S>
class ObjectAdapter : public Solver<P,S> {
  private:
  //    Searcher<pair<int,int>,S>* algo1;
  public:
  ObjectAdapter();
  ~ObjectAdapter(){};
  S solve(P);
};
template<typename P, typename S>
S ObjectAdapter<P, S>::solve(P problem) {
    cout << "function solve works on ObjectAdapter" << endl;
  //temp - to replace the return value
  return "123";
}
template<typename P, typename S>
ObjectAdapter<P, S>::ObjectAdapter() {

}

#endif //EX4__OBJECTADAPTER_H_
