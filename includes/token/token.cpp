#include <iostream>
#include <iomanip>
#include <string>
#include "Token.h"

using namespace std;

Token::Token(){
}

ostream& operator <<(ostream& outs, const Token& Token){
    Token.Print(outs);
    return outs;
}

void Token::Print(ostream &outs) const{
    outs<<"TOKEN Print: DON't ^%#$# call me again!"<<endl;
    //Blank
}
