//
// Created by omer on 17/01/2020.
//

#ifndef EX4__SEARCHABLE_H_
#define EX4__SEARCHABLE_H_
#include <vector>
#include "State.h"
#include <list>
using namespace std;

template<typename T>
class Searchable {
 public:
  // matrix size;.
  int matrixSize =0;
  /**
   * Destructor
   */
  virtual ~Searchable() {};
  /**
   * get initial state
   * @return initial state
   */
  virtual State<pair<int, int>> *getInitialState() = 0;
  /**
   * check if certain state is the goal state
   * @return boolean answer
   */
  virtual bool isGoalState(State<T>) = 0;
  /**
   * get other states with access for them
   * @return list with pointers to all the states that we have access for them from our certain state
   */
  virtual list<State<T> *> getAllPossibleStates(State<T>) = 0;
  /**
   * get the goal state
   * @return  goal state
   */
  virtual State<pair<int, int>> *getGoalState() = 0;
};

#endif //EX4__SEARCHABLE_H_
