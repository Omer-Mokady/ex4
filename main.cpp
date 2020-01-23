#include <iostream>
#include "Server.h"
#include "Solver.h"
#include "StringReverser.h"
#include <string>
#include <vector>
#include "Server.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "MyTestClientHandler.h"
#include "CacheManager.h"
#include "State.h"
#include "MatrixProblem.h"
#include "Searcher.h"
#include "ObjectAdapter.h"
#include "BFSAlgo.h"
#include "MyParallelServer.h"
#include "BestFirstSearch.h"
#include "AstarAlgo.h"
using namespace std;

namespace boot {
class Main {
 public:
  int main(int port) {
    MyParallelServer *s = new MyParallelServer();
//  MySerialServer *s = new MySerialServer();
    CacheManager<State<pair<int, int>> *> *cache = new FileCacheManager<State<pair<int, int>> *>(5);
    Solver<Searchable<pair<int, int>> *, State<pair<int, int>> *>
        *solver = new ObjectAdapter<Searchable<pair<int, int>> *, State<pair<int, int>> *>();
    s->open(port, new MyClientHandler<Searchable<pair<int, int>> *, State<pair<int, int>> *>(cache, solver));
  }
};
}



int main(int argc, char *argv[]) {



  // for gal:

// string str = "12,3,9,18,8,7,12,10,20,15,0,12,0,4,0,9,3,1,13,7,16,3,7,19,3,20,17,13,10,15\n2,18,2,13,0,20,3,9,1,11,2,-1,0,9,11,16,19,9,14,5,6,9,7,9,8,11,18,8,11,4\n5,6,5,0,7,-1,16,1,5,6,5,-1,17,4,-1,16,17,16,-1,17,0,13,3,13,11,-1,11,17,20,14\n12,20,15,7,20,16,7,15,12,1,5,19,20,2,5,16,12,13,18,3,10,20,9,8,0,19,2,9,15,18\n18,0,1,1,1,2,1,6,10,7,2,1,2,-1,7,17,-1,-1,18,2,19,10,8,7,17,18,1,20,5,7\n3,-1,2,5,11,10,10,11,12,4,12,9,19,-1,12,20,13,2,11,18,18,11,15,4,16,14,1,17,8,2\n11,20,11,-1,14,5,2,4,17,0,4,10,13,11,13,9,7,11,8,8,10,8,15,6,13,15,9,16,6,6\n8,2,7,14,-1,12,2,1,3,4,20,1,7,17,14,18,-1,5,8,1,2,18,0,19,1,15,20,11,15,15\n2,0,14,5,17,16,16,19,0,10,16,3,20,18,3,2,3,0,18,8,3,6,-1,-1,19,5,18,4,20,12\n-1,13,-1,12,6,8,17,17,0,18,11,4,-1,12,16,5,10,4,4,10,8,14,1,4,12,9,1,1,13,8\n18,2,-1,17,6,18,14,0,19,10,13,19,1,6,17,19,12,6,17,3,10,6,9,8,-1,4,3,3,20,5\n12,5,14,5,4,19,9,1,11,7,3,14,2,4,19,3,9,11,8,0,16,4,18,20,11,14,0,2,2,8\n10,17,6,18,11,5,16,17,6,14,2,20,19,15,6,5,6,6,3,10,18,13,10,3,11,-1,10,16,12,6\n11,5,17,-1,20,-1,1,4,2,18,15,11,15,20,1,10,7,5,8,1,19,18,9,13,10,1,8,20,15,11\n1,0,2,8,7,17,11,-1,12,12,-1,17,14,11,5,14,10,3,20,19,1,7,-1,12,9,17,17,15,1,10\n0,5,14,20,14,18,14,16,7,11,-1,4,4,0,11,4,8,11,20,-1,16,4,15,0,14,11,13,10,17,11\n20,7,5,16,0,7,-1,17,3,0,18,2,20,14,6,16,10,3,17,3,-1,7,12,11,16,19,13,20,7,5\n14,20,20,10,2,11,9,11,12,4,16,3,11,7,20,18,9,17,9,7,16,8,8,10,14,6,15,9,5,17\n3,11,1,10,0,6,15,5,11,3,7,0,5,2,9,17,15,19,17,11,1,7,12,17,5,16,14,10,8,6\n0,15,17,3,9,14,5,2,16,20,-1,10,14,12,11,14,19,10,1,3,16,17,16,19,-1,0,7,5,0,7\n20,15,3,8,3,14,4,12,15,15,9,19,9,7,18,6,10,8,17,2,19,1,3,5,14,1,19,19,20,11\n5,16,13,9,18,18,5,11,17,18,8,5,13,19,11,4,4,9,17,12,15,15,19,5,15,1,13,12,1,11\n7,15,10,11,4,4,13,11,0,16,1,11,15,3,9,5,2,4,11,12,-1,4,14,12,8,1,9,15,5,4\n19,10,1,3,8,6,16,11,3,3,11,7,17,19,12,15,14,-1,1,8,12,1,19,-1,9,3,19,-1,11,2\n15,7,5,0,8,15,9,13,2,8,7,6,7,18,16,4,7,16,0,4,0,6,4,1,2,6,15,8,0,19\n5,0,19,18,2,7,1,19,3,11,19,13,18,5,11,6,20,14,1,9,2,13,17,17,0,15,15,18,10,12\n16,2,15,19,1,6,14,2,18,19,3,11,18,13,7,17,20,10,19,16,12,-1,19,19,9,5,18,20,10,3\n8,10,15,13,11,12,13,2,3,15,10,19,-1,16,4,5,1,1,0,14,14,20,15,-1,5,17,11,5,11,11\n20,6,9,17,15,13,5,-1,12,1,18,10,1,4,-1,17,14,18,2,3,9,0,3,13,17,18,2,20,12,1\n-1,4,17,16,18,15,17,8,20,-1,-1,4,3,16,18,8,8,12,8,15,16,16,14,-1,3,12,19,10,-1,7";
//  string initial = "0,0\n";
//  string goal = "29,29\n";
//    MatrixProblem* newMatrix = new MatrixProblem(str, initial, goal);
////  Searcher<pair<int,int>>* bfsAlgo = new BFSAlgo<pair<int,int>>();
//  Searcher<pair<int,int>>* bestForSearchAlgo = new BestFirstSearch<pair<int,int>>();
//  State<pair<int,int>>* tempSolution = bestForSearchAlgo->Search(newMatrix);
//  Searcher<pair<int,int>>* astarAlgo = new AstarAlgo<pair<int,int>>();
//  State<pair<int,int>>* tempSolution = astarAlgo->Search(newMatrix);
//  State<pair<int,int>>* tempSolution = bestForSearchAlgo->Search(newMatrix);


//  cout << "end" << endl;
//  cout << "end" << endl;


//  string s1 = "1,28,3,54\n";
//  string s2 = "-1,567,6,32\n";
//  string s3 = "7,86,9,84\n";
//  string initial = "0,1\n";
//  string goal = "2,1\n";
//  string str = s1 + s2 + s3;
//  MatrixProblem* newMatrix = new MatrixProblem(str, initial, goal);
//
//
//  Searcher<pair<int,int>>* bfsAlgo = new BFSAlgo<pair<int,int>>();
//  State<pair<int,int>>* tempSolution = bfsAlgo->Search(newMatrix);

//  Searcher<pair<int,int>>* bestForSearchAlgo = new BestFirstSearch<pair<int,int>>();
//  State<pair<int,int>>* tempSolution = bestForSearchAlgo->Search(newMatrix);
//  cout << "end" << endl;










//  checkFunc(newMatrix);
//   State<pair<int, int>> *tempState1 = new State<pair<int, int>>(2, pair<int, int>(1, 1));
//   int a =0;
//   tempState1->setColor('b');
//   a=1;
//   if(tempState1->getColor() == 'b')
//   {
//         cout << "we got 'b'" << endl;
//   } else if(tempState1->getColor() != 'b') {
//     cout << "we didn't!! got 'b'" << endl;
//   }
//  State<pair<int, int>> *tempState2 = new State<pair<int, int>>(2, pair<int, int>(1, 1));
//  list<State<pair<int, int>>*> newList = newMatrix->getAllPossibleStates(*tempState1);
//    cout << "1 is good" << endl;


//if(tempState1->equals(*tempState2)) {
//  cout << "1 is good" << endl;
//}
//  if(tempState1->equals(*(newMatrix->goalState))) {
//    cout << "2 is good" << endl;
//  }
//  if(newMatrix->isGoalState(*tempState1)){
//    cout << "gggood" << endl;
//
//  } else {
//    cout << "baddd" << endl;
//
//  }

//
//  State<pair<int,int>> tempStateX = (newMatrix->getInitialState());
//
//
//  string solution;
// solution = BFSClassExample.search(matrix);






  //important:
//  ClientHandler *c = new MyClientHandler<string,string>();


//  Solver<Searchable<pair<int,int>>*,string> *solv = new ObjectAdapter<Searchable<pair<int,int>>*,string>();
////  MatrixProblem* newMatrix1 = new MatrixProblem(str, initial, goal);
//  Searchable<pair<int,int>>* newMatrix1 = new MatrixProblem(str, initial, goal);
//
//
//  cout << "before solve" << endl;
//  solv->solve(newMatrix1);
//  cout << "after solve" << endl;




// importantttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
    int port;
    if(argc>1) {
      string strPort = argv[1];
      port = stoi(argv[1]);
    } else {
      port = 5600;
    }
    boot::Main ourMain;
    ourMain.main(port);


//  MyParallelServer *s = new MyParallelServer();
////  MySerialServer *s = new MySerialServer();
//
//  CacheManager<State<pair<int, int>> *> *cache = new FileCacheManager<State<pair<int, int>> *>(5);
//  Solver<Searchable<pair<int, int>> *, State<pair<int, int>> *>
//      *solver = new ObjectAdapter<Searchable<pair<int, int>> *, State<pair<int, int>> *>();
//
//  s->open(5601, new MyClientHandler<Searchable<pair<int, int>> *, State<pair<int, int>> *>(cache, solver));


//// for reverseString
//  MyParallelServer *s1 = new MyParallelServer();
////  MySerialServer *s = new MySerialServer();
//
//  CacheManager<State<pair<int, int>> *> *cache1 = new FileCacheManager<State<pair<int, int>> *>(5);
//  Solver<string, string> *solver1 = new StringReverser();
//
//  s1->open(5601, new MyTestClientHandler<string>());

  return 0;
}