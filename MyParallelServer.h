//
// Created by gal on 21/01/2020.
//

#ifndef EX4__MYPARALLELSERVER_H_
#define EX4__MYPARALLELSERVER_H_
#include "Server.h"
using namespace server_side;

class MyParallelServer : public Server {
 public:
  ~MyParallelServer() {};
  void open(int portNumber, ClientHandler *c) override;
  void stop(int socketToClose) override;
  void Start(int port, ClientHandler *clientHandler);
  void ClientHandlerThread(int socket, ClientHandler *clientHandler);

};

#endif //EX4__MYPARALLELSERVER_H_
