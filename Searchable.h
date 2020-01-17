//
// Created by omer on 17/01/2020.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
#include <vector>
#include "State.h"
using namespace std;

template<typename T>
class Searchable {
 public:

  virtual ~Searchable() {};
  virtual State<T> getInitialState() = 0;
  virtual bool isGoalState(State<T>) = 0;
  virtual vector<State<T>> getAllPossibleStates(State<T>) = 0;
};

#endif //EX4__SEARCHABLE_H_
