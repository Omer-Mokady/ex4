//
// Created by gal on 16/01/2020.
//

#ifndef EX4__MYCLIENTHANDLER_H_
#define EX4__MYCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "CacheManager.h"
#include <string>
#include <string.h>
#include "Solver.h"

template<typename S>
class MyClientHandler : public ClientHandler{
  ~MyClientHandler(){};
  void handleClient(int socketNumber);
 private:
  CacheManager<S> *cache = new FileCacheManager<S>(1);
};
template<typename S>
void MyClientHandler<S>::handleClient(int socketNumber){
  int counter = 0;
  string start;
  string end;
  char line[1024] = {0};
  string problem = "";
  read(socketNumber, line, 1024);
  start = line;
  end = line;
  while (!strcmp(line, "end")){
    counter++;
    if (counter > 2){
      start = end;
    }
    end = line;
    problem.append(line);
    problem.append("@"); //insert directly as line to the state.
    read(socketNumber, line, 1024);
  }

}
#endif //EX4__MYCLIENTHANDLER_H_
