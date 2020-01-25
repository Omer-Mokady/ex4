//
// Created by omer on 18/01/2020.
//

#ifndef EX4__SEARCHER_H_
#define EX4__SEARCHER_H_
#include <queue>
#include "Searchable.h"
#include <iostream>
#include "State.h"

using namespace std;

template<typename T>
class Searcher {
 public:
  /**
   * giving a Searchable object, the Search method that implemented in several classes will search for a solution
   * in the form of State<T> object, where T is the parameter both of the object and both of the Searchable objects.
   * Search will implement a searching algorithm such as DFS, BFS, BestFS, A*, etc.
   * @return a Solution to the given Searchable - the problem need to be solved.
   */
  virtual State<T> *Search(Searchable<T> *) = 0;
  /**
   * default destructor.
   */
  virtual ~Searcher() {};

};
#endif //EX4__SEARCHER_H_
