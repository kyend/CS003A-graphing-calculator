#include <iostream>
#include <iomanip>
#include <cstring>
#include "rightparen.h"

using namespace std;

RightParen::RightParen():Token(){
  p = ")";
  _precedence = 99;
}

RightParen::RightParen(string parenthesis){
  p = parenthesis;
  _precedence = 99;
}

void RightParen::Print(ostream& outs) const{
  outs << p;
}