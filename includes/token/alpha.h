#ifndef ALPHA_H
#define ALPHA_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include "token.h"
#include "constants.h"

using namespace std;

class Alpha : public Token
{
public:
    Alpha();
    Alpha(string letter);
    void Print(ostream& outs=cout) const;
    TOKEN_TYPES TypeOf(){return ALPHA;}
    int precedence(){return _precedence;}
    string AlphaOnly(){return a;}
private:
    string a;
    int _precedence;
};

#endif //ALPHA_H