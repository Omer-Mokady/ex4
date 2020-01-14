//
// Created by omer on 14/01/2020.
//

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_
#include "Server.h"
using namespace server_side;

class MySerialServer : public Server {
  virtual void open(int port);
  virtual void close();
};

#endif //EX4__MYSERIALSERVER_H_
