#ifndef FUNCTION_H      //like sin or cos
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "constants.h"
#include "operator.h"

using namespace std;

class Function : public Operator 
{
public:
    Function();
    Function(string sohcahtoa);
    void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){return FUNCTION;}
    int precedence(){return _precedence;} 
    int identity(){return _identity;}
    double func(double arg, double x);   
    string FunctionOnly(){return _f;}
private:
    string _f;
    int _precedence;
    int _identity;
};



#endif //FUNCTION_H