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

template<typename P,typename S>
class MyClientHandler : public ClientHandler{
  ~MyClientHandler(){};
  void handleClient(int socketNumber);
 private:
  CacheManager<S> *cache = new FileCacheManager<S>(1);
  Solver<P,S> *solver = new StringReverser();;
};
template<typename P,typename S>
void MyClientHandler<P,S>::handleClient(int socketNumber){
  int counter = 0;
  cout << "inside handleClient" << endl;
  string start;
  string end;
  char line[1024] = {0};
  string problem1 = "";
  read(socketNumber, line, 1024);
  start = line;
  end = line;
  while (!strcmp(line, "end")){
    counter++;
    if (counter > 2){
      start = end;
    }
    end = line;
    problem1.append(line);
    problem1.append("@"); //insert directly as line to the state.
    read(socketNumber, line, 1024);
  }

  // for Omer
//  string solution = "temp solution";
//  string strProblem = "123/n456/n789/n";
  string strProblem = "123";

  Searchable<pair<int,int>>* problem = new MatrixProblem(strProblem);
  if (this->cache->checkSolutionExistent(strProblem)) {
    cout << "already have the solution for this problem." << endl;
    cout << this->cache->get(strProblem) << endl;
  } else {
    cout << "don't have the solution for this problem yet." << endl;
    string solution = this->solver->solve(strProblem);
    this->cache->insert(strProblem, solution);
    cout << solution << endl;
  }


}
#endif //EX4__MYCLIENTHANDLER_H_
