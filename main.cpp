#include <iostream>
#include "Server.h"
#include "Solver.h"
#include "StringReverser.h"
#include <string>
#include "Server.h"
#include "MySerialServer.h"
//#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "CacheManager.h"


int main() {

  MySerialServer *s = new MySerialServer();
  s->open(5601, new MyTestClientHandler<string>());
  return 0;
}