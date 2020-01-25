//
// Created by omer on 17/01/2020.
//

#include "MatrixProblem.h"


list<State<pair<int, int>> *> MatrixProblem::getAllPossibleStates(State<pair<int, int>> state) {
  int row = 0, col = 0, colSize = 0;
  list<State<pair<int, int>> *> statesList;
  row = state.getCurState().first;
  col = state.getCurState().second;
  int rowSize = this->matrix.size();
  // get upper state
  if (row > 0) {
    if (this->matrix[row - 1][col]->getCost() != -1) {
      statesList.push_front((this->matrix[row - 1][col]));
    }
  }
  // get right state
  if (!matrix.empty()) {
    colSize = this->matrix[0].size();
    if (col < colSize - 1) {
      if (this->matrix[row][col + 1]->getCost() != -1) {
        statesList.push_front((this->matrix[row][col + 1]));
      }
    }
  }
  // get left state
  if (col > 0) {
    if (this->matrix[row][col - 1]->getCost() != -1) {
      statesList.push_front((this->matrix[row][col - 1]));
    }
  }
  // get lower state
  if (row < rowSize - 1) {
    if ((this->matrix[row + 1][col])->getCost() != -1) {
      statesList.push_front((this->matrix[row + 1][col]));
    }
  }
  return statesList;
}
State<pair<int, int>> *MatrixProblem::getInitialState() {
  return (this->initialState);
}

State<pair<int, int>> *MatrixProblem::getGoalState() {
  return &(*(this->goalState));
}

string MatrixProblem::getName() {
  return this->name;
}
bool MatrixProblem::isGoalState(State<pair<int, int>> state) {
  return (state.equals(*(this->goalState)));
}



//*/