#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

#include "../linked_list_functions/linked_list_functions.h"
#include "../node/node.h"

using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
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

    Queue(){
        _front = nullptr;
        _rear = nullptr;
        _size = 0;
    }

    Queue(const Queue<T>& copyMe){
        _size = copyMe._size;
        _rear = _copy_list(_front, copyMe._front);
    }


    ~Queue(){
        _clear_list(_front);
        _rear = nullptr;
    }

    Queue& operator=(const Queue<T>& RHS){
        if (this == &RHS){
            return *this;
        }
        if (_front != nullptr){
            _clear_list(_front);
        }
        _size = RHS._size;
        _rear = _copy_list(_front, RHS._front);
        return *this;
    }

    bool empty(){
        if(_front == nullptr){
            return true;
        }
        return false;
    }

    T front(){
        if(_front == nullptr){
            return T();
        }
        return _front->_item;
    }

    T back(){
        if(_rear == nullptr){
            // cout << "error: rear == nullptr" << endl; 
            return T();
        }
        return _rear->_item;
    }

    void push(T item){
        if(_front == nullptr && _rear == nullptr){
            _front = _insert_head(_front, item);
            _rear = _front;
        }
        else{
       _rear = _insert_rear(_rear, item);
        }
       _size++;
    }

    T pop(){
        assert(_front != nullptr && "error queue pop: _front == nullptr");
        T popped = _remove_head(_front);
        if (_front == _rear){
            _rear = nullptr;    
        }
        _size--;
        return popped;
    }

    Iterator begin() const{
        return Iterator(_front);
    }            //Iterator to the head node
    
    Iterator end() const{
        return Iterator(nullptr);
    }              //Iterator to NULL

    void print_pointers(){
        _print_pointers(_front);
    }

    int size() const { 
        return _size; 
    }
    
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
        cout << "Queue: ";
        _print_list(printMe._front);
        return outs;
    }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

#endif //MYQUEUE_H