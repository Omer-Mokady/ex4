#include <iostream>
#include "Server.h"
#include "Solver.h"
#include "StringReverser.h"
#include <string>

int main() {
  StringReverser *s = new StringReverser();
  std::cout << s->solve("Hello World!") << std::endl;
  return 0;
}