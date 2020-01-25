//
// Created by omer on 17/01/2020.
//

#ifndef EX4__MATRIXPROBLEM_H_
#define EX4__MATRIXPROBLEM_H_
#include "Searchable.h"
#include "State.h"
#include <limits>
#include <climits>
#include <string>
#include <functional>
#include <iostream>
#include <list>

//template<typename T>
class MatrixProblem : public Searchable<pair<int, int>> {
 private:

  string name;
 public:
  // originial matrix
  vector<vector<State<pair<int, int>> *>> matrix;
  // initial state
  State<pair<int, int>> *initialState;
  // goal state
  State<pair<int, int>> *goalState;
  /**
   * get string name of the searchable
   * @return string name of the searchable
   */
  string getName();
  virtual State<pair<int, int>> *getInitialState();
  virtual State<pair<int, int>> *getGoalState();
  virtual bool isGoalState(State<pair<int, int>>);
  virtual list<State<pair<int, int>> *> getAllPossibleStates(State<pair<int, int>>);
  /**
   * Constructor
   * @param str the matrix string
   * @param initial initial point in string
   * @param goal goal point in string
   */
  MatrixProblem(string str, string initial, string goal) {
    // get name
    this->name = str;
    vector<vector<State<pair<int, int>> *>> vect;
    int rowNum = 0, colNum = 0, firstIndex = 0, value = 0;
    // added new!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    unsigned int i=0;
    string tempStr;
    // create matrix field
    State<pair<int, int>> *newState;
    // read all the matrix data
    i = 0;
    while (i < str.length()) {
      colNum = 0;
      vector<State<pair<int, int>> *> row;
      // read a row
      while (str[i] != '\n') {
        pair<int, int> pairNum(rowNum, colNum);
        // separe values
        if (str[i] == ',') {
          tempStr = str.substr(firstIndex, i - firstIndex);
          value = stoi(tempStr);
          firstIndex = i + 1;
          newState = new State<pair<int, int>>(value, pairNum);
          row.push_back(newState);
          colNum++;
        }
        i++;
      }
      // insert last number
      tempStr = str.substr(firstIndex, i - firstIndex);
      value = stoi(tempStr);
      firstIndex = i + 1;
      pair<int, int> pairNum(rowNum, colNum);
      newState = new State<pair<int, int>>(value, pairNum);
      row.push_back(newState);
      rowNum++;
      vect.push_back(row);
      i++;
    }
    this->matrix = vect;
    // get initialState
    firstIndex = 0;
    for (i = 0; i < initial.length(); i++) {
      if (initial[i] == ',') {
        tempStr = initial.substr(firstIndex, i - firstIndex);
        rowNum = stoi(tempStr);
        firstIndex = i + 1;
      } else if (initial[i] == '\n') {
        tempStr = initial.substr(firstIndex, i - firstIndex);
        colNum = stoi(tempStr);
      }
    }
    this->initialState = matrix[rowNum][colNum];
    // get goalState
    firstIndex = 0;
    for (i = 0; i < goal.length(); i++) {
      if (goal[i] == ',') {
        tempStr = goal.substr(firstIndex, i - firstIndex);
        rowNum = stoi(tempStr);
        firstIndex = i + 1;
      } else if (goal[i] == '\n') {
        tempStr = goal.substr(firstIndex, i - firstIndex);
        colNum = stoi(tempStr);
      }
    }
    this->goalState = matrix[rowNum][colNum];
    int colSize = 0;
    int rowSize = this->matrix.size();
    if (!matrix.empty()) {
      colSize = this->matrix[0].size();
    }
    this->matrixSize = colSize*rowSize;
  }

  /**
   * converse from matrix string into unique number string
   * @param str  matrix string
   * @return string of unique numbers
   */
  static string toString(string str) {
    size_t numName = hash<string>{}(str);
    return to_string(numName);
  }
};

#endif //EX4__MATRIXPROBLEM_H_
