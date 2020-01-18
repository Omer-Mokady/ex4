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
using namespace std;
int main() {
//  string s1 = "123\n";
//  string s2 = "456\n";
//  string s3 = "789\n";
//  string str = s1+s2+s3;
////  MatrixProblem* matrix = new MatrixProblem(str);
// Searchable<pair<int,int>>* matrix = new MatrixProblem(str);
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




//
//
//  int a;
//



  /*
  CacheManager<Student> *my_cache = new FileCacheManager<Student>(3);
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
  }

  my_cache->foreach([](Student& s){s.print();}); //prints all students in cache
*/
  MySerialServer *s = new MySerialServer();
  s->open(5601, new MyClientHandler<string,string>());
//  MySerialServer *s = new MySerialServer();
//  s->open(5601, new MyTestClientHandler<string>());
  return 0;
}