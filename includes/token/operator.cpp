#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include "operator.h"

using namespace std;

Operator::Operator(){

}

Operator::Operator(string symbol){
    _op = symbol;
    if (_op == "+" || _op == "-"){
        _precedence = 1;
    }
    if (_op == "*" || _op == "/"){
        _precedence = 2;
    }
    if (_op == "^"){
        _precedence = 3;
    }
}

void Operator::Print(ostream& outs) const{
    outs << _op;
}

double Operator::eval(double arg1, double arg2){
    double value;
    switch(_op[0]){
        case '*':
            value = arg1 * arg2;
            return value;
            break; 
        case '/':
            value = arg1/arg2;
            return value;
            break;
        case '+':
            value = arg1 + arg2;
            return value;
            break;
        case '-':
            value = arg1 - arg2;
            return value;
            break;
        case '^':
            value = pow(arg1, arg2);
            return value;
            break;
    }
}