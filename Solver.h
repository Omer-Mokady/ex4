//
// Created by gal on 14/01/2020.
//

#ifndef EX4__SOLVER_H_
#define EX4__SOLVER_H_
template<typename P, typename S>
class Solver {
 public:

  virtual ~Solver() {};
  virtual S solve(P) = 0;
  virtual Solver *getClone() =0;
};
#endif //EX4__SOLVER_H_
