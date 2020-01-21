//
// Created by gal on 21/01/2020.
//

#ifndef EX4__ASTARALGO_H_
#define EX4__ASTARALGO_H_
#include <iostream>
#include <unordered_set>
#include <list>
#include <set>
#include "Searcher.h"
#include "Searchable.h"
#include "State.h"
template<typename T>
class AstarAlgo : public Searcher<T> {
 public:
  virtual ~AstarAlgo() {};
  State<T> *Search(Searchable<T> *s);
  int getNodesNumber();
 private:
  set<State<T>> *_open = new set<State<T>>();
  set<State<T>> *_closed = new set<State<T>>();
};
#endif //EX4__ASTARALGO_H_
