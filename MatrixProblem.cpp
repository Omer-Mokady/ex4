//
// Created by omer on 17/01/2020.
//

#include "MatrixProblem.h"



vector<State<pair<int, int>>> MatrixProblem::getAllPossibleStates(State<pair<int, int>>) {
  return vector<State<pair<int, int>>>();
}
bool MatrixProblem::isGoalState(State<pair<int, int>>) {
  return false;
}
State<pair<int, int>> MatrixProblem::getInitialState() {
  return State<pair<int, int>>(0, std::pair<int,int>(0,0));
}
string MatrixProblem::getName() {
  return this->name;
}


//*/