#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "../token/token.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/rightparen.h"
#include "../token/leftparen.h"
#include "../linked_list_functions/linked_list_functions.h"

using namespace std;

class ShuntingYard
{
public:
    ShuntingYard(){
    }

    ShuntingYard(Queue<Token*> infix){
        _infix = infix;
    }

    void infix(Queue<Token*> change){
        _infix = change;
    }

    Queue<Token*> postfix(Queue<Token*> infix){
        _infix = infix;
        Queue<Token*> return_me = postfix();
        return return_me;
    }

    Queue<Token*> postfix(){
        Queue<Token*>::Iterator it(_infix.begin());
        Queue<Token*> output;
        Stack<Token*> opstack;
        int prec_new;
        int prec_prev = 0;
        int prec_stack;
        while (it != _infix.end()){
            Token* p = *it;     //token pointer to beginning of infix
            int type = p->TypeOf();
            //cout << "type: " << type << endl;
            switch(type){
                case 1:
                case 3:{        //integer
                    output.push(p);
                    //cout << "pushed to output queue" << endl;
                    it++;
                }break;
                case 2:{         //operator
                    //leave room for precedence here
                    // Operator* print_me = static_cast<Operator*>(p);     //this is just to print the operator
                    // cout << print_me->OperatorOnly() << endl;

                    prec_new = p->precedence();         //sets new prec for current operator
                    if(prec_new <= prec_prev && prec_prev != 98){           // ^ = 3; */ = 2; +- = 1; default 0
                        //cout << "prec new > prev" << endl;
                        output.push(opstack.pop());     //if smaller, then we pop n push
                        if (opstack.empty() == false){        //if stack isn't empty, we need to check more
                            Token* p_stack = *opstack.begin();
                            //cout << "more on the stack" << endl;
                            prec_stack = p_stack->precedence();     //check precedence
                            while(prec_stack >= prec_new && opstack.empty() == false && prec_stack != 98){
                                output.push(opstack.pop());     //continue to pop n push
                                prec_stack = p_stack->precedence();     //reassess top of stack
                                //cout << "pop and push again" << endl;
                            }
                        }
                        if(opstack.empty() == true){        //if stack is empty reset prev to 0
                            prec_prev = 0;
                            //cout << "stack empty" << endl;
                        }
                    }
                    opstack.push(p);
                    it++;
                    prec_prev = prec_new;
                }break;
                case 4:{
                    // Function* print_func = static_cast<Function*>(p);     //this is just to print the function
                    // cout << print_func->FunctionOnly() << endl;

                    prec_new = p->precedence();         //sets new prec for current function
                    if (prec_new == 0){                          //prec = 0 when ALPHA, treats it like a number
                        output.push(p);
                        //cout << "pushed to output queue" << endl;
                        it++;
                    }
                    else{
                       if(prec_new <= prec_prev && prec_prev != 98){           // ^ = 3; */ = 2; +- = 1; default 0
                        //cout << "prec new > prev" << endl;
                        output.push(opstack.pop());            //if smaller, then we pop n push
                        if (opstack.empty() == false){        //if stack isn't empty, we need to check more
                            Token* p_stack = *opstack.begin();
                            //cout << "more on the stack" << endl;
                            prec_stack = p_stack->precedence();     //check precedence
                            while(prec_stack >= prec_new && opstack.empty() == false){
                                output.push(opstack.pop());     //continue to pop n push
                                prec_stack = p_stack->precedence();     //reassess top of stack
                                //cout << "pop and push again" << endl;
                            }
                        }
                        if(opstack.empty() == true){        //if stack is empty reset prev to 0
                            prec_prev = 0;
                            //cout << "stack empty" << endl;
                        }
                    }
                    opstack.push(p);
                    it++;
                    prec_prev = prec_new;               //setting prec prev to the just received p
                    }    
                }break;
                case 7:{             //left parenthesis
                    opstack.push(p);                    //pushes ( onto stack
                    it++;
                    prec_prev = 98;
                }break;
                case 8:{             //right parenthesis
                    Token* p_Rparen = *opstack.begin();      //token pointer at the top of the stack
                    prec_stack = p_Rparen->precedence();     //check precedence
                    while(prec_stack < 98){
                        output.push(opstack.pop());     //continue to pop n push
                        p_Rparen = *opstack.begin();        //reassess top of stack
                        prec_stack = p_Rparen->precedence();     //check precedence of top of stack
                        //cout << "prec_stack in ) while loop: " << prec_stack << endl;
                    }
                    opstack.pop();                      //pops the ( and discards it
                    if (opstack.empty() == true){       //if the stack is empty, prev_prec = 0
                        prec_prev = 0;
                    }
                    else{                                           //if stack is NOT empty
                        p_Rparen = *opstack.begin();        //reassess top of stack one more time
                        prec_stack = p_Rparen->precedence();     //check precedence
                        prec_prev = prec_stack;                 //prec_prev now set again
                    }     //keeping track of precedence of whatever is left on stack
                    it++;                   //finally moves the iterator on infix queue
                }break;
            }
        }    
        //input queue now empty; pop remaining things in stack
        while (opstack.empty() == false){
            output.push(opstack.pop());
        }
        return output;
    }

private:
    Queue<Token*> _infix;
};

#endif      //SHUNTING_YARD_H