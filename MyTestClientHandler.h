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
  MyTestClientHandler();
  ~MyTestClientHandler(){};
  void handleClient(int socketNumber);
 private:
  StringReverser *solver;
  FileCacheManager<S> cache;
};

#endif //EX4__MYTESTCLIENTHANDLER_H_
