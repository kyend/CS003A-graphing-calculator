#include <iostream>
#include <iomanip>
#include <cstring>
#include "alpha.h"

using namespace std;

Alpha::Alpha(){
    a = "x";
    _precedence = 0;
}

Alpha::Alpha(string letter){
    a = letter;
    _precedence = 0;
}
void Alpha::Print(ostream& outs) const{
    outs << a;
}