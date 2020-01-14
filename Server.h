//
// Created by omer on 14/01/2020.
//

#ifndef EX4__SERVER_H_
#define EX4__SERVER_H_

using namespace std;
namespace server_side {
  /**
   * Server Interface
   */
  class Server {

   public:
    virtual void open(int port) = 0;
    virtual void stop() = 0;
    virtual ~Server() {}
  };
}


#endif //EX4__SERVER_H_
