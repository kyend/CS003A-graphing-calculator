#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <cstring>
#include <vector>
#include <ctype.h>
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/leftparen.h"
#include"../token/rightparen.h"

using namespace std;

class Tokenizer
{
    public:
        Tokenizer();
        Tokenizer(string eq);
        vector<string> vec();
        Queue<Token*> tokenize();

    private:
        string _eq;
};

#endif      //TOKENIZER_H