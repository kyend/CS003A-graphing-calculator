#include "tokenizer.h"

Tokenizer::Tokenizer(){

}

Tokenizer::Tokenizer(string eq){
    _eq = eq;
}

vector<string> Tokenizer::vec(){
    vector<string> _vec;
    int i = 0;
    
    while(_eq[i]){      //while the string index isnt empty
        if(ispunct(_eq[i])){    //if punctuation, should only be 1 char; if you want a double, exclude the period and include it in isdigit
            string punc;
            punc.push_back(_eq[i]);     //pushing char into string 
            _vec.push_back(punc);
            i++;
        }
        else if(isdigit(_eq[i])){       //if digit, could be more than 1 char
            string digit;
            while(isdigit(_eq[i])){     //loop for while there are digits
                digit.push_back(_eq[i]);    //adding chars to digit string
                i++;
            }
            _vec.push_back(digit);      //
        }
        else if(isalpha(_eq[i])){
            string alpha;
            while(isalpha(_eq[i])){
                alpha.push_back(_eq[i]);
                i++;
            }
            _vec.push_back(alpha);
        }
        else{
            i++;
        }
    }
    return _vec;
}

Queue<Token*> Tokenizer::tokenize(){
    vector<string> _vec = vec();      //getting the vector string 
    Queue<Token*> _q;
    int i = 0;
    //somewhere in here
    // while(_vec[i][0]){      //use vector size in for loop
    for(i = 0; i < _vec.size(); i++){
        // cout << "tokenize " << _vec[i] << endl;
        if(_vec[i] == "("){
            _q.push(new LeftParen());
        }
        else if(_vec[i] == ")"){
            _q.push(new RightParen());
        }
        else if(ispunct(_vec[i][0])){
            _q.push(new Operator(_vec[i]));
        }
        else if(isdigit(_vec[i][0])){
            _q.push(new Integer(_vec[i]));
        }
        else if(isalpha(_vec[i][0])){
            _q.push(new Function(_vec[i]));
        }
        // i++;
    }
    return _q;
}