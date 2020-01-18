//
// Created by omer on 17/01/2020.
//

#include "MatrixProblem.h"

list<State<pair<int, int>> > MatrixProblem::getAllPossibleStates(State<pair<int, int>> state) {
  int row=0,col=0, rowSize=0;
  list<State<pair<int, int>>> statesList;
  row = state.getCurState().first;
  col = state.getCurState().second;
  int colSize = this->matrix.size();
  cout << "colSize is: " << colSize << endl;
  // get upper state
  if(row > 0){
    statesList.push_front(*(this->matrix[row-1][col]));
  }
  // get lower state
  if(!matrix.empty()) {
    rowSize = this->matrix[0].size();
    cout << "rowSize is: " << rowSize << endl;
    if(row < rowSize-1) {
      statesList.push_front(*(this->matrix[row+1][col]));
    }
  }
  // get left state
  if(col > 0){
    statesList.push_front(*(this->matrix[row][col-1]));
  }
  // get right state
  if(col < colSize - 1){
    statesList.push_front(*(this->matrix[row][col+1]));
  }
  return statesList;
}
State<pair<int, int>> MatrixProblem::getInitialState() {
  return *(this->initialState);
}
string MatrixProblem::getName() {
  return this->name;
}
bool MatrixProblem::isGoalState(State<pair<int, int>>  state) {
return (state.equals(*(this->goalState)));
}


//*/