//
// Created by gal on 14/01/2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include <string>
#include "ClientHandler.h"
#include "Solver.h"
#include "StringReverser.h"
#include "CacheManager.h"

using namespace std;
template<typename S>

class MyTestClientHandler : public ClientHandler {
 public:
//  MyTestClientHandler();
  ~MyTestClientHandler() {};
  void handleClient(int socketNumber);
  ClientHandler *getClone();

 private:
  StringReverser *solver = new StringReverser();
  CacheManager<S> *cache = new FileCacheManager<S>(2);
};


template<typename S>
void MyTestClientHandler<S>::handleClient(int socketNumber){
  char line[1024] = {0};
  read(socketNumber, line, 1024);
  string problem = line;
  if (this->cache->checkSolutionExistent(problem)) {
    cout << "already have the solution for this problem." << endl;
    cout << this->cache->get(problem) << endl;
  } else {
    cout << "don't have the solution for this problem yet." << endl;
    string solution = this->solver->solve(problem);
    this->cache->insert(problem, solution);
    cout << solution << endl;
  }

}
template<typename S>
ClientHandler *MyTestClientHandler<S>::getClone() {
  return new MyTestClientHandler();
}

#endif //EX4__MYTESTCLIENTHANDLER_H_
