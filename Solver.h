//
// Created by gal on 14/01/2020.
//

#ifndef EX4__SOLVER_H_
#define EX4__SOLVER_H_
template<typename P, typename S>
class Solver {
 public:
  /**
   * Destructor
   */
  virtual ~Solver() {};
  /**
   * solve a problem object and return solve object
   * @return solve object
   */
  virtual S solve(P) = 0;
  /**
   * make a copy of the Solver
   * @return copy of the Solver
   */
  virtual Solver *getClone() =0;
};
#endif //EX4__SOLVER_H_
