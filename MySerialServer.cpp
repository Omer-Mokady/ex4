//
// Created by gal on 13/01/2020.
//

#include "MySerialServer.h"
#include <thread>

MySerialServer::~MySerialServer() {

}
//test
void MySerialServer::open(int portNumber, ClientHandler *clientHandler) {
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    throw "Could not create a socket\n";
  } else {
//    cout << "socket created" << endl;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(portNumber);

  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    throw "Could not bind the socket to the ip\n";
  } else {
//    cout << "bind the socket to the ip" << endl;
  }

  if (listen(socketfd, 10) == -1) {
    throw "Error during listening command\n";
  } else {
//    cout << "listening command is ok" << endl;
  }
  this->socketNumber = socketfd;
  thread starter([clientHandler, portNumber, this] { Start(portNumber, clientHandler); });
  starter.join();
}

void MySerialServer::Start(int, ClientHandler *clientHandler) {
  struct sockaddr_in cli_addr;
  int newsockfd, clilen;
  clilen = sizeof(cli_addr);
  struct timeval tv;
  tv.tv_sec = 120; // set timeout of 2 minutes for the socket.
  tv.tv_usec = 0;
  setsockopt(this->socketNumber, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
  while (true) {
//    cout << "inside while!" << endl;
    newsockfd = accept(this->socketNumber, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd == -1) {
      if (errno == EWOULDBLOCK) {
        cout << "timeOut!\n";
        break;
      } else {
        cout << "Error with accepting client\n";
        break;
      }
    }
    clientHandler->handleClient(newsockfd);
    this->stop(newsockfd);
  }
  this->stop(this->socketNumber);
}

void MySerialServer::stop(int socketToClose) {
  close(socketToClose);
}


