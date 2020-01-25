//
// Created by gal on 21/01/2020.
//

#ifndef EX4__MYPARALLELSERVER_H_
#define EX4__MYPARALLELSERVER_H_
#include "Server.h"
using namespace server_side;
/**
 * a parallel server - able to handle many clients simultaneously and solve their problems.
 */
class MyParallelServer : public Server {
 public:
  /**
   * default destructor.
   */
  ~MyParallelServer() {};
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
  /**
   * a thread for taking care in a single client each time - followed by detach so we will be able tp deal with
   * multiple clients at the same time.
   * here we will send the socket the client is seats on to the client Handler.
   * @param socket the socket we received the client on.
   * @param clientHandler the ClientHandler object to take care of the clients.
   */
  void ClientHandlerThread(int socket, ClientHandler *clientHandler);

};

#endif //EX4__MYPARALLELSERVER_H_
