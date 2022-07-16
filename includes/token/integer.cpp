#include "integer.h"

Integer::Integer(){
    const bool debug = false;
    if(debug){
        cout << "int ctor 0 args is 0" << endl;
    }
    i = 0;
    _precedence = 0;
}

Integer::Integer(double value){
    i=value;
    _precedence = 0;
}

Integer::Integer(string value){
    i = atof(value.c_str());
    _precedence = 0;
}

void Integer::Print(ostream& outs) const{
    outs<<"["<<i<<"]";
}
