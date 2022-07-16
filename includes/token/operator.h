#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <iomanip>
#include <string>
#include "token.h"
#include "constants.h"

using namespace std;

class Operator : public Token
{
public:
    Operator();
    Operator(string symbol);
    void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){return OPERATOR;}
    int precedence(){return _precedence;}
    string OperatorOnly(){return _op;}
    double eval(double arg1, double arg2);
private:
    string _op;
    int _precedence;
};

#endif      //OPERATOR_H