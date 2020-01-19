//
// Created by gal on 16/01/2020.
//

#ifndef EX4__MYCLIENTHANDLER_H_
#define EX4__MYCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "CacheManager.h"
#include <string>
#include <string.h>
#include "Solver.h"
#include "Searchable.h"
#include "MatrixProblem.h"
#include "ObjectAdapter.h"
using namespace std;


template<typename P,typename S>
class MyClientHandler : public ClientHandler{
  ~MyClientHandler(){};
  void handleClient(int socketNumber);
 private:
  CacheManager<S> *cache = new FileCacheManager<S>(5);
//  Solver<P,S> *solver = new ObjectAdapter<P,S>();
  Solver<P,S> *solver = new ObjectAdapter<P,S>();

};
template<typename P,typename S>
void MyClientHandler<P,S>::handleClient(int socketNumber){
//  int counter = 0;
  cout << "inside handleClient" << endl;
//  string start;
//  string end;
  string input="", tempStr;
  char line[1024] = {0};
  string problem1;
  bool endOfInput = false;
  do {
    read(socketNumber, line, 1024);
    tempStr =line;
    input= input+tempStr;
    if(input.find("end")!= std::string::npos) {
      endOfInput =true;
    }
  } while(!endOfInput);
//  read(socketNumber, line, 1024);
//  start = line;
//  end = line;
//  while (!strcmp(line, "end")){
//    counter++;
//    if (counter > 2){
//      start = end;
//    }
//    end = line;
//    problem1.append(line);
//    problem1.append("@"); //insert directly as line to the state.
//    read(socketNumber, line, 1024);
//  }
  cout << "after getting input from client\n" << endl;

  string goal, initial, strMatrix;
  int goalEndIndex =0, initialEndIndex =0, initialStartIndex =0, i=(input.find("end")), counterMarks=0;
  // divide input into 3 different strings: matrix, initial and goal
  while(i>0) {
    if(input[i] == '\n') {
      if(counterMarks == 0) {
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
  goal = input.substr(initialEndIndex+1, goalEndIndex-initialEndIndex);
  initial = input.substr(initialStartIndex+1, initialEndIndex-initialStartIndex);
  strMatrix = input.substr(0, initialStartIndex+1);


  // for Omer
  S solution;

  cout << "got new string" << endl;
  //"1,28,3\n4,567,6\n7,86,9\n0,1\n2,1\nend";
  // create our problem object
//  auto* problemObj = new MatrixProblem(strMatrix, initial, goal);
  Searchable<pair<int,int>>* problemObj = new MatrixProblem(strMatrix, initial, goal);
//  MatrixProblem* problemObj = new MatrixProblem(strMatrix, initial, goal);
  P newObj;
  this->solver->solve(problemObj);

//  auto* problemObj = new MatrixProblem(strMatrix, initial, goal);


  cout << "got matrix\n" << endl;
  string strProblem = MatrixProblem::toString(input);
  cout << "got name\n" << endl;
  // try to load solution
  if (this->cache->checkSolutionExistent(strProblem)) {
    cout << "already have the solution for this problem.\n" << endl;
    try {
      solution = this->cache->get(strProblem);
      cout << "we got the solution from cache or disc\n" << endl;
    } catch (const char * e) {
      cout << "error1" << endl;
      cout << e << endl;
    }
  // create solution
  } else {
    cout << "don't have the solution for this problem yet.\n" << endl;
    solution = this->solver->solve(problemObj);
    try {
      this->cache->insert(strProblem, solution);
      cout << "we added the solution to the cache" << endl;
    } catch (const char * e) {
      cout << "error2" << endl;
      cout << e << endl;
    }
  }


}
#endif //EX4__MYCLIENTHANDLER_H_
