#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include "token.h"
#include "constants.h"

using namespace std;

class RightParen : public Token
{
public:
    RightParen();
    RightParen(string parenthesis);
    void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){return RIGHTPAREN;}
    int precedence(){return _precedence;}    
    string RightparenOnly(){return p;}
private:
    string p;
    int _precedence;
};

#endif      //RIGHTPAREN_H