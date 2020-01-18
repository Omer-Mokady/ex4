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
class MatrixProblem : public Searchable<pair<int,int>> {
 private:

  string name;
 public:
  vector<vector<State<pair<int,int>>*>> matrix;

  //  ~MatrixProblem();
  State<pair<int,int>>* initialState;
  State<pair<int,int>>* goalState;
  string getName();
  virtual State<pair<int,int>> getInitialState();
  virtual bool isGoalState(State<pair<int,int>>);
  virtual list<State<pair<int,int>>> getAllPossibleStates(State<pair<int,int>>);
  MatrixProblem(string str, string initial, string goal) {
    // get name
    this->name = str;
    vector<vector<State<pair<int,int>>*>> vect;
    int rowNum=0, colNum=0, i=0, firstIndex = 0, value=0;
    string tempStr;
    bool finish = false;





  // create matrix field

    // to delete spaces !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    State<pair<int, int>> *newState;
    // read all the matrix data
    i=0;
    while (i<str.length()) {
//      cout << 1 << endl;
      colNum = 0;
      vector<State<pair<int, int>> *> row;
      // read a row
      while (str[i] != '\n') {
//        cout << 2 << endl;
//        cout << str[i] << endl;
        pair<int, int> pairNum(rowNum, colNum);
        // separe values
        if(str[i] == ',') {
//          cout << 3 << endl;
          tempStr = str.substr(firstIndex, i-firstIndex);
//          cout << "tempStr is: " << tempStr << endl;
          value = stoi(tempStr);
//          cout << "value is: " << value << endl;

          firstIndex = i+1;
          newState = new State<pair<int, int>>(value, pairNum);
          row.push_back(newState);
          colNum++;
        }
        i++;
      }
      // insert last number
      tempStr = str.substr(firstIndex, i-firstIndex);
      value = stoi(tempStr);
      firstIndex = i+1;
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
    i=0;
    finish = false;
//            cout << "initial: " << initial << endl;
    for(i=0; i<initial.length();i++) {
      if(initial[i] == ',') {
        tempStr = initial.substr(firstIndex, i-firstIndex);
        rowNum = stoi(tempStr);
//        cout << "row is: " << rowNum << endl;
        firstIndex = i+1;
      } else if(initial[i] == '\n') {
        tempStr = initial.substr(firstIndex, i-firstIndex);
        colNum = stoi(tempStr);
//        cout << "col is: " << colNum << endl;
        finish = true;
      }
    }
//    if(!finish) {
//      cout << "string has no \ n in the end" << endl;
//
//      tempStr = str.substr(firstIndex, i-firstIndex);
//      colNum = stoi(tempStr);
//
//    }
    //make pair
    pair<int, int> pairNum(rowNum, colNum);
    // get value from initialize point
    vector<State<pair<int, int>> *> tempVector;
//    State<pair<int, int>> *tempState;
    tempVector = vect[rowNum];
    value = tempVector[colNum]->getCost();
    newState = new State<pair<int, int>>(value, pairNum);
    this->initialState = newState;



    // get goalState
    firstIndex = 0;
    i=0;
    finish = false;
//            cout << "initial: " << initial << endl;
    for(i=0; i<goal.length();i++) {
      if(goal[i] == ',') {
        tempStr = goal.substr(firstIndex, i-firstIndex);
        rowNum = stoi(tempStr);
//        cout << "row is: " << rowNum << endl;
        firstIndex = i+1;
      } else if(goal[i] == '\n') {
        tempStr = goal.substr(firstIndex, i-firstIndex);
        colNum = stoi(tempStr);
//        cout << "col is: " << colNum << endl;
        finish = true;
      }
    }
//    if(!finish) {
//      cout << "string has no \ n in the end" << endl;
//
//      tempStr = str.substr(firstIndex, i-firstIndex);
//      colNum = stoi(tempStr);
//
//    }
    //make pair
    pair<int, int> pairNum2(rowNum, colNum);
    // get value from initialize point
//    State<pair<int, int>> *tempState;
    tempVector = vect[rowNum];
    value = tempVector[colNum]->getCost();
    newState = new State<pair<int, int>>(value, pairNum2);
    this->goalState = newState;




    cout << "end" << endl;

  }
  // to remove to HANDLER class
  static string toString(string str)
  {
    size_t numName = hash<string>{}(str);
    return to_string(numName);
  }
};

#endif //EX4__MATRIXPROBLEM_H_
