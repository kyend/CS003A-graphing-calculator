#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

#include "../linked_list_functions/linked_list_functions.h"
#include "../node/node.h"

using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){
            _ptr = nullptr;
        }                                     //default ctor
        Iterator(node<T>* p){
            _ptr = p;
        }                   //Point Iterator to where p is pointing to
        operator bool(){
            if(_ptr != nullptr){
                return true;
            }
            return false;
        }                                //casting operator: true if _ptr not NULL
                                                        //      this turned out to be a pain!


        T& operator *(){ 
            return _ptr->_item;
        }                        //dereference operator
        T* operator ->(){
            return &(_ptr->_item);
        }                       //member access operator

        bool is_null(){
            if (_ptr == nullptr){
                return true;
            }
            return false;
        }                                 //true if _ptr is NULL

        friend bool operator !=(const Iterator& left, const Iterator& right){
            if (left._ptr != right._ptr){
                return true;
            }
            return false;
                                } //true if left != right

        friend bool operator ==(const Iterator& left, const Iterator& right){
            if(left._ptr == right._ptr){
                return true;
            }
            return false;
        } //true if left == right

        Iterator& operator++(){
            _ptr = _ptr->_next;
            return *this;
        }                         //member operator: ++it; or ++it = new_value

        friend Iterator operator++(Iterator& it, int unused){
            it._ptr = it._ptr->_next;
            return Iterator(it._ptr);
        }         //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };      

    Stack(){                                //0 args CTOR
        _top = nullptr;
        _size = 0;
    }

    Stack(const Stack<T>& copyMe){          //COPY CTOR
        _top = _copy_list(_top, copyMe._top);
        _size = copyMe._size;
    }   

    ~Stack(){                               //destructor
        _clear_list(_top);
    }

    Stack<T>& operator=(const Stack<T>& RHS){   
        if (this == &RHS){
            return *this;
        }
        if (_top != nullptr){
            _clear_list(_top);              //emptying list
        }
        _size = RHS._size;
        _top = _copy_list(_top, RHS._top);
        return *this;
    }

    T top(){
        assert(_top != nullptr && "error stack top: _top == to nullptr");
        return _top->_item;                 //return value stored at _top
    }

    bool empty(){
        if (_top == nullptr){
            return true;
        }
        return false;
    }

    void push(T item){
        _top = _insert_head(_top, item);    //inserts at _top and returns new _top
        _size++;
    }

    T pop(){
        assert(_top != nullptr && "error stack pop: _top == to nullptr");
        T popped = _remove_head(_top);
        _size--;
        return popped;
    }

    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe){
        cout << "Stack: ";
        _print_list(printMe._top);
        return outs;
    }

    void print_pointers(){
        _print_pointers(_top);
    }

    Iterator begin() const{
        return Iterator(_top);
    }              //Iterator to the head node
    Iterator end() const{
        return Iterator(nullptr);
    }               //Iterator to NULL
    int size() const {
        return _size; 
        }

private:
    node<T>* _top;
    int _size;
};

#endif //MYSTACK_H