//
// Created by omer on 18/01/2020.
//

#ifndef EX4__SEARCHER_H_
#define EX4__SEARCHER_H_
#include "Searchable.h"
using namespace std;
// am i need to put typename S for solution???????
template<typename T, typename S>
class Searcher {
 public:

//  virtual ~Searchable() {};
  virtual S Search(Searchable<T>*) = 0;

};
#endif //EX4__SEARCHER_H_
