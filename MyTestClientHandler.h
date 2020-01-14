//
// Created by gal on 14/01/2020.
//

#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "Solver.h"
#include "StringReverser.h"
#include <string>

using namespace std;
//template<typename Problem, typename Solution>
class MyTestClientHandler : public ClientHandler {
 public:
  ~MyTestClientHandler(){};
  void handleClient(int socketNumber);
 private:
  StringReverser solver; //need to change it somehow to Solver solver instead of StringReverser solver.
};

#endif //EX4__MYTESTCLIENTHANDLER_H_
