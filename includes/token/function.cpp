#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include "function.h"

// Function::Function(){

// }

Function::Function(string sohcahtoa){
    _f = sohcahtoa;
    if (_f == "sin"){
        _precedence = 50;
        _identity = 1;
    }
    if (_f == "cos"){
        _precedence = 50;
        _identity = 2;
    }
    if (_f == "tan"){
        _precedence = 50;
        _identity = 3;
    }
    if (_f == "sec"){
        _precedence = 50;
        _identity = 4;
    }
    if (_f == "csc"){
        _precedence = 50;
        _identity = 5;
    }
    if (_f == "cot"){
        _precedence = 50;
        _identity = 6;
    }
    if(_f == "abs"){
        _precedence = 50;
        _identity = 7;
    }
    if(_f == "log"){
        _precedence = 50;
        _identity = 8;
    }
    if(_f == "sqrt"){
        _precedence = 50;
        _identity = 9;
    }
    if(_f == "cbrt"){
        _precedence = 50;
        _identity = 11;
    }
    if (_f == "x" || _f == "X"){
        _precedence = 0;
        _identity = 10;
    }
}

double Function::func(double arg, double x){
    const bool debug = false;
    double value;
    switch (_identity){
        case 1:{        //sin
            value = sin(arg);
            if (debug) cout << "sin of " << arg << endl << "sin value: " << value << endl;
            return value;
        }break;
        case 2:{        //cos
            value = cos(arg);
            if (debug) cout << "cos of " << arg << endl << "cos value: " << value << endl;
            return value;
        }break;
        case 3:{        //tan
            value = tan(arg);
            if (debug) cout << "tan of " << arg << endl << "tan value: " << value << endl;
            return value;
        }break;
        case 4:{        //sec
            value = 1/cos(arg);
            if (debug) cout << "sec of " << arg << endl << "sec value: " << value << endl;
            return value;
        }break;
        case 5:{        //csc
            value = 1/sin(arg);
            if (debug) cout << "csc of " << arg << endl << "csc value: " << value << endl;
            return value;
        }break;
        case 6:{        //cot
            value = 1/tan(arg);
            if (debug) cout << "cot of " << arg << endl << "cot value: " << value << endl;
            return value;
        }break;
        case 7:{        //abs
            value = abs(arg);
            return value;
        }break;
        case 8:{        //log
            value = log(arg);
            return value;
        }break;
        case 9:{        //sqrt
            value = sqrt(arg);
            return value;
        }break;
        case 11:{        //cbrt
            value = cbrt(arg);
            return value;
        }break;
        
        default:{      //x 
            value = x;
            if (debug) cout << "value: " << value << endl;
            return value;
        }break;
    }
    
    return value;
} 

void Function::Print(ostream& outs) const{
    outs << _f; 
}