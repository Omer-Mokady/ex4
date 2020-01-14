//
// Created by gal on 14/01/2020.
//

#ifndef EX4__SOLVER_H_
#define EX4__SOLVER_H_
template<typename Problem, typename Solution>
class Solver {
 public:
  virtual ~Solver() {};
  virtual Solution solve(Problem) = 0;
};
#endif //EX4__SOLVER_H_
