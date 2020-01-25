//
// Created by gal on 21/01/2020.
//

#include "MyParallelServer.h"
#include <thread>

void MyParallelServer::open(int portNumber, ClientHandler *clientHandler) {
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
  int optval = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
    throw "Could not bind the socket to the ip\n";
  } else {
//    cout << "bind the socket to the ip" << endl;
  }

  if (listen(socketfd, 1) == -1) {
    throw "Error during listening command\n";
  } else {
//    cout << "listening command is ok" << endl;
  }
  this->socketNumber = socketfd;
  thread starter([clientHandler, portNumber, this] { Start(portNumber, clientHandler); });
  starter.join(); // wail till this thread is finished - which mean all clients got their answers.
}

void MyParallelServer::Start(int, ClientHandler *clientHandler) {
  struct sockaddr_in cli_addr;
  int newsockfd, clilen;
  clilen = sizeof(cli_addr);
  struct timeval tv;
  tv.tv_sec = 120; // set timeout of 2 minutes for the socket.
  tv.tv_usec = 0;
  setsockopt(this->socketNumber, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
  while (true) {
//    cout << "inside parallel while!" << endl;
    newsockfd = accept(this->socketNumber, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
//    cout << "opened socket " << newsockfd << endl;
    if (newsockfd == -1) {
      if (errno == EWOULDBLOCK) {
        cout << "timeOut!\n";
        break;
      } else {
        cout << "Error with accepting client\n";
        break;
      }
    }
    thread handler([clientHandler, newsockfd, this] { ClientHandlerThread(newsockfd, clientHandler); });
    handler.detach(); //supporting multiple receiving to the socket.
  }

  this->stop(this->socketNumber);
}
void MyParallelServer::stop(int socketToClose) {
  close(socketToClose);
}

void MyParallelServer::ClientHandlerThread(int socket, ClientHandler *clientHandler) {
  ClientHandler *clientHandler2 = clientHandler->getClone();
  clientHandler2->handleClient(socket);
  this->stop(socket);
}
