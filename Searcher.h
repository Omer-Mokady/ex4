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
//  virtual ~Searchable() {};
  virtual State<T>* Search(Searchable<T> *) = 0;
};
#endif //EX4__SEARCHER_H_
