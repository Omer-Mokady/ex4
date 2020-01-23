//
// Created by gal on 14/01/2020.
//

#ifndef EX4__STRINGREVERSER_H_
#define EX4__STRINGREVERSER_H_
#include "Solver.h"
#include <string>

using namespace std;

class StringReverser : public Solver<string, string>{

 public:
  ~StringReverser(){};
  string solve(string);
  Solver *getClone();
};

#endif //EX4__STRINGREVERSER_H_
