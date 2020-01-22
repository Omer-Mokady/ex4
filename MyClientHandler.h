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

  ~MyClientHandler() {};
  void handleClient(int socketNumber);
  /**
   * delete string's spaces
   * @param str original string
   * @return the current string without spaces
   */
  string deleteSpaces(string str);
  string getSolution(string input);
  string fromMatrixGoalStateToString(S);
  string compareMatrixStates(State<pair<int, int>> first, State<pair<int, int>> second);
 private:
//  CacheManager<S> *cache = new FileCacheManager<S>(5);
  CacheManager<S> *cache;

//  Solver<P,S> *solver = new ObjectAdapter<P,S>();
  Solver<P, S> *solver;
 public:
  MyClientHandler(CacheManager<S> *cache, Solver<P, S> *solver);
  ClientHandler *getClone() {
    return new MyClientHandler(this->cache, this->solver->getClone());
  }

};
template<typename P, typename S>
void MyClientHandler<P, S>::handleClient(int socketNumber) {
//  int counter = 0;
  cout << "inside handleClient" << endl;
//  string start;
//  string end;
  string input = "", tempStr, strSolution, inputForSearch = "";
  char line[1024] = {0};
  string problem1;
  bool endOfInput = false;

  while (!endOfInput) {
    char line[1024] = {0};
    read(socketNumber, line, 1024);
    tempStr = line;
//    cout << "tempStr " << line << endl;
    input = input + tempStr;
//    cout << "input " << input << endl;
    if (input.find("end") != std::string::npos) {
      endOfInput = true;
    }
  }

//  cout << "end of reading" << endl;
  input = deleteSpaces(input);
  int startPoint = 0, i = 0, counterCommas = 0;
  bool oneCommaBefore = false;
  string tempStr1 = "";
  for (i = 0; i < input.length() - 1; i++) {
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
//          cout << "we found final solution: " << strSolution << endl;
          send(socketNumber, strSolution.c_str(), strSolution.length(), 0);
          oneCommaBefore = false;
        }
      }
      counterCommas = 0;
    }
  }




//  input = deleteSpaces(input);
//  strSolution = getSolution(input);
//  cout << "we found final solution: " << strSolution << endl;

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
  P newObj;
  string strProblem = MatrixProblem::toString(input);
  // try to load solution
  if (this->cache->checkSolutionExistent(strProblem)) {
    cout << "already have the solution for this problem.\n" << endl;
    try {
      solution = this->cache->get(strProblem);
      cout << "we got the solution from cache or disc\n" << endl;
    } catch (const char *e) {
      cout << "error1" << endl;
      cout << e << endl;
    }
    // create solution
  } else {
    solution = this->solver->solve(problemObj);
    cout << "don't have the solution for this problem yet.\n" << endl;
    try {
      this->cache->insert(strProblem, solution);
      cout << "we added the solution to the cache" << endl;
    } catch (const char *e) {
      cout << "error2" << endl;
      cout << e << endl;
    }
  }
  strSolution = fromMatrixGoalStateToString(solution);
  cout << strSolution << endl;
  cout << "we found solution" << endl;
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
