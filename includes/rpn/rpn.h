#ifndef RPN_H
#define RPN_H

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

class RPN
{
public:
    RPN(){
    }

    RPN(Queue<Token*> queue){
        _q = queue;
    }

    bool empty(){
        return _q.empty();
    }

    Stack<Token*> _stack(){
        return _s;
    }

    Queue<Token*> _queue(){
        return _q;
    }

    void set_input(Queue<Token*> change){
        _q = change;
    }

    // template <typename T>
    double evaluate(double x = 0){
        if(empty()){
            return 0;       //return 0 if RPN is empty
        }
        //if we are here, RPN is not empty
        Queue<Token*>::Iterator it(_q.begin());
            //pointing to token ptrs in queue 
        while(it != _q.end()){
            Token* p = *it; 
            int type = p->TypeOf();
            //cout << "type: " << type << endl; 
            switch(type){
                case 1:{                 //integer
                    _s.push(p);
                    //cout << "pushed to stack" << endl;
                    it++;
                }break;
                case 2:{                 //operator
                    assert(_s.top() != nullptr && "error: stack is empty cannot perform operation");
                    Integer* b_ptr = static_cast<Integer*>(_s.pop());       //static casting popped token* to Int*
                    Integer* a_ptr = static_cast<Integer*>(_s.pop());

                    double b = b_ptr->IntegerOnly();                        //extracting double value from Int*
                    double a = a_ptr->IntegerOnly();

                    Operator* op_ptr = static_cast<Operator*>(p);           //static casting token* to Op*
                    Operator op = *op_ptr;                                  //type Op to put through maths
                    
                    double c = op.eval(a, b);                               //c is product of a (eval) b
                    Integer* cc = new Integer(c);                           //Int* to Int of c
                    _s.push(cc);                                            //pushing c onto stack
                    //cout << "found op: pop x2, then push" << endl;
                    it++;
                }break;
                case 3:{             //alpha aka x
                    _s.push(new Integer(x));
                    //cout << "substituted x:" << x << endl;
                    it++;
                }break;
                case 4:{                //function
                    // assert(_s.top() != nullptr && "error: stack is empty cannot perform operation");
                    Function* _f_ptr = static_cast<Function*>(p);       //static casting token* to Func*
                    Function _f = *_f_ptr;                              //type Func to put through maths

                    int alpha_func = _f.identity();                     //determining is it ALPHA y/n
                    if (alpha_func == 10){                              //if function is an ALPHA
                        _s.push(new Integer(x));                        //if ALPHA, don't pop, just push to stack
                        //cout << "substituted x:" << x << endl;
                        it++;
                    }
                    else{
                        Integer* arg_ptr = static_cast<Integer*>(_s.pop());     //pop the top of the stack
                        double arg = arg_ptr->IntegerOnly();                    //turn into a double, no ptr

                        double sohcahtoa = _f.func(arg, x);                     //doing the maths
                        Integer* product = new Integer(sohcahtoa);              //Int* to Int of sohcahtoa
                        _s.push(product);                                       //pushing to the stack
                        //cout << "found func: pop x1, then push" << endl;
                        it++;    
                    }
                }break;
            }
        }
        Integer* final_int = static_cast<Integer*>(_s.top());
        double final = final_int->IntegerOnly();
        return final;
    }

    double operator()(double x = 0){
        double return_me = evaluate(x);
        return return_me;
    }


private:
    Queue<Token*> _q;
    Stack<Token*> _s;
};


#endif      //RPN_H