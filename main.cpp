#include <iostream>
#include "Server.h"
#include "Solver.h"
#include "StringReverser.h"
#include <string>
#include <vector>
#include "Server.h"
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "CacheManager.h"
#include "State.h"
#include "MatrixProblem.h"
#include "Searcher.h"
#include "ObjectAdapter.h"
#include "BFSAlgo.h"
#include "MyParallelServer.h"
using namespace std;

Searchable<pair<int,int>>* checkFunc(MatrixProblem* matrix) {


  matrix->matrix[1][1]->setCameFrom(matrix->initialState);
  cout << "inside checkFunc" << endl;

}

// for checking cacheManager:
/*
// Testing Class
class Student
{
  int id;
  int value;
  const char* data;
 public:
  static const string class_name; //every class will have a class static name called: class_name
  Student(int _key, int _value, const char* _data): id(_key), value(_value), data(_data) {}
  Student() {}; //every class will have a default constructor
  void print() {
    cout<<"Student Object: "<<id<<", "<<value<<", "<<data<<endl;
  };
  ~Student(){};

};
const string Student::class_name = "StudentClass";
 using namespace std;

class Employee
{
  const char* name;
 public:
  static const string class_name; //every class will have a class static name called: class_name
  Employee(const char* _name): name(_name) {};
  Employee(){}; //every class will have a default constructor
  void print() {
    cout<<"Employee Object: "<<name<<endl;
  };/
  ~Employee(){};

};
const string Employee::class_name = "EmployeeClass";
*/
int main() {



  // for gal:
  string s1 = "1,28,3,54\n";
  string s2 = "4,567,6,32\n";
  string s3 = "7,86,9,84\n";
  string initial = "0,1\n";
  string goal = "2,1\n";
  string str = s1+s2+s3;
// Searchable<pair<int,int>>* matrix = new MatrixProblem(str, initial, goal);
// State<pair<int,int>> tempState = (matrix->getInitialState());


//  MatrixProblem* newMatrix = new MatrixProblem(str, initial, goal);
//  Searcher<pair<int,int>>* bfsAlgo = new BFSAlgo<pair<int,int>>();
//  State<pair<int,int>>* tempSolution = bfsAlgo->Search(newMatrix);
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


     // end for gal





//
//  vector<vector<State<pair<int,int>>*>> vect;
//  int rowNum=0, colNum=0, i=0;
//  while (i<str.length()) {
//    colNum = 0;
//    vector<State<pair<int, int>> *> row;
//    while (str[i] != '\n') {
//      pair<int, int> pairNum(rowNum, colNum);
//      int value = str[i] - '0';
//      State<pair<int, int>> *newState = new State<pair<int, int>>(value, pairNum);
//      size_t randNum1 = hash<string>{}(str);
//      to_string(randNum1);
//      cout << (str) << endl;
//      row.push_back(newState);
////      row.push_back(State<pair<int,int>>(0,pair<rowNum,colNum>);
//
//      i++;
//      colNum++;
//    }
//    rowNum++;
//    vect.push_back(row);
//    i++;
//  }
//  to_string()



//  }
//  for (i = 0; i < str.length(); i++) {
//
//  }
//



// for checking cacheManager:
//     CacheManager<State<pair<int,int>>> *my_cache = new FileCacheManager<State<pair<int,int>>>(1);
//  CacheManager<State<int>> *my_cache2 = new FileCacheManager<State<int>>(1);
//  CacheManager<State<pair<int,int>>> *my_cache = new FileCacheManager<State<pair<int,int>>>(1);



//  CacheManager<State<pair<int,int>>*> *my_cache = new FileCacheManager<State<pair<int,int>>*>(1);

//  State<pair<int,int>>* state1 = new State<pair<int,int>>(1, pair<int,int>(1,1));
//  State<pair<int,int>>* state2 = new State<pair<int,int>>(2, pair<int,int>(2,2));
//  state2->setCameFrom(state1);
//  State<pair<int,int>>* state3 = new State<pair<int,int>>(3, pair<int,int>(3,3));
//  state3->setCameFrom(state2);
//
//
//  try {
//  my_cache->insert("check1", state1);
//  my_cache->insert("check2", state3);
//  } catch  (const char * e) {
//    cout << e << endl;
//  }
//  try {
//    State<pair<int,int>>* result = (my_cache->get("check1"));//not in cache but in filesystem
//    cout << "result" << endl;
//  } catch (const char * e) {
//    cout << e << endl;
//  }


  /*
   *   CacheManager<Student> *my_cache = new FileCacheManager<Student>(3);

//  CacheManager<> my_cache(3);
  try {
    my_cache->insert("0", Student(0,22,"student1"));
    my_cache->insert("1", Student(1,23,"student2"));
    my_cache->insert("2", Student(2,25,"student3"));
    my_cache->insert("3", Student(3,29,"student4"));
  } catch  (const char * e) {
    cout << e << endl;
  }
  try {
    Student return_obj = my_cache->get("0");//not in cache but in filesystem
  } catch (const char * e) {
    cout << e << endl;
  }./a.out
  my_cache->foreach([](Student& s){s.print();}); //prints all students in cache
*/

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




//works:
//  MySerialServer *s = new MySerialServer();
//  s->open(5601, new MyClientHandler<Searchable<pair<int,int>>*,string>());

//  Searcher<pair<int,int>>* dsfAlgo = new DFSAlgo<pair<int,int>>();


//  MySerialServer *s = new MySerialServer();
  MyParallelServer *s = new MyParallelServer();
  CacheManager<State<pair<int,int>>*> *cache = new FileCacheManager<State<pair<int,int>>*>(5);
  Solver<Searchable<pair<int,int>>*,State<pair<int,int>>*> *solver = new ObjectAdapter<Searchable<pair<int,int>>*,State<pair<int,int>>*>();

  s->open(5601, new MyClientHandler<Searchable<pair<int,int>>*,State<pair<int,int>>*>(cache, solver));

  return 0;
}