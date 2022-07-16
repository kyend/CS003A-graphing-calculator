#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include "constants.h"

using namespace std;

class Token
{
public:
    Token();
    friend ostream& operator <<(ostream& outs, const Token& Token);
    virtual void Print(ostream& outs=cout) const;
    virtual TOKEN_TYPES TypeOf(){cout<<"Token type of..."<<endl;}
    virtual int precedence(){cout << "Token precedence..." << endl;}  
};

#endif // TOKEN_H
