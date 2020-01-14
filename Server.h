//
// Created by omer on 14/01/2020.
//

#ifndef EX4__SERVER_H_
#define EX4__SERVER_H_
#include "ClientHandler.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "ClientHandler.h"
#include <unistd.h>
#include <iostream>
using namespace std;
namespace server_side {
  /**
   * Server Interface
   */
  class Server {
   public:
    virtual ~Server() {}
    /**
   * open a socket
   * @param portNumber port to listen on.
   * @param c ClientHandler Object.
   */
    virtual void open(int portNumber, ClientHandler *c) = 0;
    /**
     * closing the socket.
     */
    virtual void stop(int socketToClose) = 0;
   protected:
    int socketNumber;
  };
}


#endif //EX4__SERVER_H_
