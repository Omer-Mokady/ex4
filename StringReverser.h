//
// Created by gal on 14/01/2020.
//

#ifndef EX4__STRINGREVERSER_H_
#define EX4__STRINGREVERSER_H_
#include "Solver.h"
#include <string>

using namespace std;
class StringReverser : public Solver<string, string> {

 public:
  /**
   * default destructor.
   */
  ~StringReverser() {};
  /**
   * gets a string and returning in backwards.
   * @param s the string in it's original form.
   * @return s in reversed.
   */
  string solve(string s);
  /**
   * cloning the Solver.
   * @return a new object of String Reverser.
   */
  Solver *getClone();
};

#endif //EX4__STRINGREVERSER_H_
