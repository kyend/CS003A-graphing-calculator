#include <iostream>
#include <iomanip>
#include <cstring>
#include "leftparen.h"

using namespace std;

LeftParen::LeftParen():Token(){
  p = "(";
  _precedence = 98;
}

LeftParen::LeftParen(string parenthesis){
  p = parenthesis;
  _precedence = 98;
}

void LeftParen::Print(ostream& outs) const{
  outs << p;
}