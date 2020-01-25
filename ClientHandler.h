//
// Created by omer on 14/01/2020.
//

#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
/**
   * ClientHandler Interface
   */

class ClientHandler {
 public:
  /**
   * get problem from client and bring him back solution
   * @param socketNumber socket number
   */
  virtual void handleClient(int socketNumber) = 0;
  /**
   * Destructor
   */
  virtual ~ClientHandler() {}
  /**
   * get copy of the Object
   * @return copy of the Object
   */
  virtual ClientHandler *getClone() = 0;
};

#endif //EX4__CLIENTHANDLER_H_
