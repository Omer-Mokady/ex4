#include <iostream>
#include "Server.h"
#include "Solver.h"
#include <string>
#include <vector>
#include "MyClientHandler.h"
#include "CacheManager.h"
#include "State.h"
#include "Searcher.h"
#include "ObjectAdapter.h"
#include "MyParallelServer.h"
using namespace std;

namespace boot {
class Main {
 public:
  void main(int port) {
    MyParallelServer *s = new MyParallelServer();
    CacheManager<State<pair<int, int>> *> *cache = new FileCacheManager<State<pair<int, int>> *>(5);
    Solver<Searchable<pair<int, int>> *, State<pair<int, int>> *>
        *solver = new ObjectAdapter<Searchable<pair<int, int>> *, State<pair<int, int>> *>();
    s->open(port, new MyClientHandler<Searchable<pair<int, int>> *, State<pair<int, int>> *>(cache, solver));
  }
};
}

int main(int argc, char *argv[]) {
    int port;
    if(argc>1) {
      string strPort = argv[1];
      port = stoi(argv[1]);
    } else {
      port = 5600;
    }
    boot::Main ourMain;
    ourMain.main(port);
  return 0;
}