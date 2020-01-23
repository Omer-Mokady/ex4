//
// Created by gal on 14/01/2020.
//

#include "StringReverser.h"
#include <bits/stdc++.h>
string StringReverser::solve(string problem) {
  string answer = problem;
  reverse(answer.begin(), answer.end());
  return answer;
}
Solver<string, string> *StringReverser::getClone() {
  return new StringReverser();
}
