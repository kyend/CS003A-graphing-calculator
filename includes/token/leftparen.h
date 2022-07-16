#ifndef LEFTPAREN_H
#define LEFTPAREN_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include "token.h"
#include "constants.h"

using namespace std;

class LeftParen : public Token
{
public:
    LeftParen();
    LeftParen(string parenthesis);
    void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){return LEFTPAREN;}
    int precedence(){return _precedence;}    
    string LeftparenOnly(){return p;}
private:
    string p;
    int _precedence;
};

#endif  //LEFTPAREN_H