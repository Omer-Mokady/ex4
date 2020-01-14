//
// Created by gal on 14/01/2020.
//

#include "MyTestClientHandler.h"

void MyTestClientHandler::handleClient(int socketNumber) {
  char line[1024] = {0};
  read(socketNumber, line, 1024);
  string buffer = line;
  string answer = this->solver.solve(line);
  cout << answer << endl;
}
