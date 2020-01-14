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
template <typename S>

class MyTestClientHandler : public ClientHandler {
 public:
//  MyTestClientHandler();
  ~MyTestClientHandler(){};
  void handleClient(int socketNumber);
 private:
  StringReverser *solver;
  CacheManager<S> *cache = new FileCacheManager<S>(5);
};
template<typename S>
void MyTestClientHandler<S>::handleClient(int socketNumber) {
  char line[1024] = {0};
  read(socketNumber, line, 1024);
  string buffer = line;
  string answer = this->solver->solve(line);
  cout << answer << endl;
}

#endif //EX4__MYTESTCLIENTHANDLER_H_
