#ifndef INTEGER_H
#define INTEGER_H


#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "token.h"
#include "constants.h"

using namespace std;

class Integer : public Token
{
public:
    Integer();
    Integer(double value);
    Integer(string value);

    void Print(ostream &outs=cout) const ;
    TOKEN_TYPES TypeOf(){return INTEGER;}
    int precedence(){return _precedence;}    
    double IntegerOnly(){return i;} //example of a function present in a child
private:
    double i;
    int _precedence;
    
};

#endif // INTEGER_H
