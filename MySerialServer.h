//
// Created by omer on 14/01/2020.
//

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_
#include "Server.h"
using namespace server_side;

class MySerialServer : public Server {
 public:
  ~MySerialServer();
  void open(int portNumber, ClientHandler *c) override;
  void stop(int socketToClose) override;
  void Start(int port, ClientHandler *clientHandler);
};

#endif //EX4__MYSERIALSERVER_H_
