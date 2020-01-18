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

//template<typename T>
class MatrixProblem : public Searchable<pair<int,int>> {
 private:
  vector<vector<State<pair<int,int>>*>> matrix;
  string name;
 public:
//  ~MatrixProblem();
  string getName();
  virtual State<pair<int,int>> getInitialState();
  virtual bool isGoalState(State<pair<int,int>>);
  virtual vector<State<pair<int,int>>> getAllPossibleStates(State<pair<int,int>>);
  MatrixProblem(string str) {
    // get name
    this->name = str;
    vector<vector<State<pair<int,int>>*>> vect;
    int rowNum=0, colNum=0, i=0;
    while (i<str.length()) {
      colNum = 0;
      vector<State<pair<int, int>> *> row;
      while (str[i] != '\n') {
        pair<int, int> pairNum(rowNum, colNum);
        int value = str[i] - '0';
        State<pair<int, int>> *newState = new State<pair<int, int>>(value, pairNum);
        row.push_back(newState);
        i++;
        colNum++;
      }
      rowNum++;
      vect.push_back(row);
      i++;
    }
    this->matrix = vect;
  }
  // to remove to HANDLER class
  static string toString(string str)
  {
    size_t numName = hash<string>{}(str);
    return to_string(numName);
  }
};

#endif //EX4__MATRIXPROBLEM_H_
