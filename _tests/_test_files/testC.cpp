#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "../../includes/queue/MyQueue.h"
#include "../../includes/tokenizer/tokenizer.h"

using namespace std;

int main(){
    string eq = "3 + 4 * x";
    Tokenizer token(eq);

    Queue<Token*> _q = token.tokenize();

    cout << "should be: 3 + 4 * x" << endl;
    _q.print_pointers();


    return 0;
}