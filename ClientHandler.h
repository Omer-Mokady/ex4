//
// Created by omer on 14/01/2020.
//

#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_
#include <iostream>

/**
   * ClientHandler Interface
   */
class ClientHandler {

 public:
  virtual void handleClient(int socketNumber) = 0;
  virtual ~ClientHandler() {}
};


#endif //EX4__CLIENTHANDLER_H_
