//
// Created by omer on 14/01/2020.
//

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_
#include "Server.h"
using namespace server_side;
/**
 * serial server - gets clients one after another, and taking care of them by turns.
 */
class MySerialServer : public Server {
 public:
  /**
   * default destructor.
   */
  ~MySerialServer();
  /**
   * declared inside server.h.
   */
  void open(int portNumber, ClientHandler *c) override;
  /**
   * declared inside server.h.e
   */
  void stop(int socketToClose) override;
  /**
   * a thread using for receiving clients to our open socket, sent them to the client handler and handle their
   * problems.
   * @param clientHandler an object use us to give the clients solutions.
   */
  void Start(int, ClientHandler *clientHandler);
};

#endif //EX4__MYSERIALSERVER_H_
