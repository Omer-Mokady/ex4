//
// Created by gal on 16/01/2020.
//

#ifndef EX4__MYCLIENTHANDLER_H_
#define EX4__MYCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "CacheManager.h"
#include <string>
//#include <string.h>
#include <string>
#include <algorithm>
#include "Solver.h"
#include "Searchable.h"
#include "MatrixProblem.h"
#include "ObjectAdapter.h"
#include <stack>
using namespace std;

template<typename P, typename S>
class MyClientHandler : public ClientHandler {
  /**
   * Destructor
   */
  ~MyClientHandler() {};
  /**
   * get problem from client and bring him back solution
   * @param socketNumber socket number
   */
  void handleClient(int socketNumber);
  /**
   * delete string's spaces
   * @param str original string
   * @return the current string without spaces
   */
  string deleteSpaces(string str);
  /**
   * get solution info and bring solution (string type)
   * @param input (string type) solution info
   * @return solution (string type)
   */
  string getSolution(string input);
  /**
   * convert solution from state pointer, into string
   * @return solution (type string)
   */
  string fromMatrixGoalStateToString(S);
  /**
   * compare between 2 states for a path
   */
  string compareMatrixStates(State<pair<int, int>> first, State<pair<int, int>> second);
 private:
  // cache memory
  CacheManager<S> *cache;
  // solver Object
  Solver<P, S> *solver;
 public:
  /**
   * Constructor
   * @param cache cache memory
   * @param solver solver Object
   */
  MyClientHandler(CacheManager<S> *cache, Solver<P, S> *solver);
  /**
   * get a copy of the Object
   * @return copy of the Object
   */
  ClientHandler *getClone() {
    return new MyClientHandler(this->cache, this->solver->getClone());
  }

};
template<typename P, typename S>
void MyClientHandler<P, S>::handleClient(int socketNumber) {
  cout << "inside handleClient" << endl;
  string input = "", tempStr, strSolution, inputForSearch = "";
  string problem1;
  bool endOfInput = false;
  // get problem info
  while (!endOfInput) {
    char line[1024] = {0};
    read(socketNumber, line, 1024);
    tempStr = line;
    input = input + tempStr;
    if (input.find("end") != std::string::npos) {
      endOfInput = true;
    }
  }
  input = deleteSpaces(input);
  int startPoint = 0, counterCommas = 0;
  unsigned int i = 0;
  bool oneCommaBefore = false;
  string tempStr1 = "";
  for (i = 0; i < input.length() - 1; i++) {
//    cout << input[i] << endl;
    if (input.find("end") == i) {
      break;
    }
    if (input[i] == ',') {
      counterCommas++;
    } else if (input[i] == '\n') {
      if (counterCommas == 1) {
        if (!oneCommaBefore) {
          oneCommaBefore = true;
        } else {
          inputForSearch = input.substr(startPoint, i + 1);
          startPoint = i + 1;
          strSolution = getSolution(inputForSearch);
          send(socketNumber, strSolution.c_str(), strSolution.length(), 0);
          oneCommaBefore = false;
        }
      }
      counterCommas = 0;
    }
  }
}

template<typename P, typename S>
string MyClientHandler<P, S>::getSolution(string input) {
  string strSolution;

  string goal, initial, strMatrix;
  int goalEndIndex = 0, initialEndIndex = 0, initialStartIndex = 0, i = input.length() - 1, counterMarks = 0;
  // divide input into 3 different strings: matrix, initial and goal
  while (i > 0) {
    if (input[i] == '\n') {
      if (counterMarks == 0) {
        goalEndIndex = i;
      } else if (counterMarks == 1) {
        initialEndIndex = i;
      } else if (counterMarks == 2) {
        initialStartIndex = i;
        break;
      }
      counterMarks++;
    }
    i--;
  }
  goal = input.substr(initialEndIndex + 1, goalEndIndex - initialEndIndex);
  initial = input.substr(initialStartIndex + 1, initialEndIndex - initialStartIndex);
  strMatrix = input.substr(0, initialStartIndex + 1);
  S solution;
  // create our problem object
  Searchable<pair<int, int>> *problemObj = new MatrixProblem(strMatrix, initial, goal);
  string strProblem = MatrixProblem::toString(input);
  // try to load solution
  if (this->cache->checkSolutionExistent(strProblem)) {
    try {
      solution = this->cache->get(strProblem);
    } catch (const char *e) {
      cout << e << endl;
    }
    // create solution
  } else {
    solution = this->solver->solve(problemObj);
    try {
      this->cache->insert(strProblem, solution);
    } catch (const char *e) {
      cout << e << endl;
    }
  }
  if(solution == nullptr) {
    strSolution = "there is no access to the goal.\n";
    return strSolution;
  }
  strSolution = fromMatrixGoalStateToString(solution);
  cout << strSolution << endl;
  return strSolution;
}

template<typename P, typename S>
string MyClientHandler<P, S>::compareMatrixStates(State<pair<int, int>> first, State<pair<int, int>> second) {
  string output;
  int value = 0;
  pair<int, int> firstPair = first.getCurState();
  pair<int, int> secondtPair = second.getCurState();
  // check if it moves down
  if (firstPair.first < secondtPair.first) {
    value = second.getPathCost();
    output = "down(" + to_string(value) + ")";
    // check if it moves up
  } else if (firstPair.first > secondtPair.first) {
    value = second.getPathCost();
    output = "up(" + to_string(value) + ")";
    // check if it moves right
  } else if (firstPair.second < secondtPair.second) {
    value = second.getPathCost();
    output = "right(" + to_string(value) + ")";
    // check if it moves left
  } else if (firstPair.second > secondtPair.second) {
    value = second.getPathCost();
    output = "left(" + to_string(value) + ")";
  }
  return output;
}
template<typename P, typename S>
string MyClientHandler<P, S>::fromMatrixGoalStateToString(S finalState) {
  string solution = "";
  State<pair<int, int>> *first;
  State<pair<int, int>> *second;
  State<pair<int, int>> *tempState = finalState;
  // make a stack of all the states with order of: from start to end
  stack<State<pair<int, int>> *> stackStates;
  while (tempState != nullptr) {
    stackStates.push(tempState);
    tempState = tempState->getCameFrom();
  }
  if (stackStates.size() == 1) {
    return solution;
  } else if (stackStates.size() > 1) {
    second = stackStates.top();
    stackStates.pop();
    while (!stackStates.empty()) {
      first = second;
      second = stackStates.top();
      stackStates.pop();
      if (!solution.empty()) {
        solution = solution + ", " + compareMatrixStates(*first, *second);
      } else {
        solution = compareMatrixStates(*first, *second);
      }
    }

  }
  return solution;
}

template<typename P, typename S>
string MyClientHandler<P, S>::deleteSpaces(string str) {
  string::iterator endP = remove(str.begin(), str.end(), ' ');
  str.erase(endP, str.end());

  return str;
}
template<typename P, typename S>
MyClientHandler<P, S>::MyClientHandler(CacheManager<S> *cache1, Solver<P, S> *solver1) {
  this->cache = cache1;
  this->solver = solver1;
}

#endif //EX4__MYCLIENTHANDLER_H_
