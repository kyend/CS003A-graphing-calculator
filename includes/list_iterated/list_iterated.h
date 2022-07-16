#ifndef LIST_ITERATED_H
#define LIST_ITERATED_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

#include "../linked_list_functions/linked_list_functions.h"
#include "../node/node.h"

using namespace std;

template <class T>
class List
{
public:
    class Iterator{
    public:
        friend class List;                              //give access to list to access _ptr
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
    
    List(){
        _head_ptr = nullptr;
        _size = 0;
    }                                                     //CTOR
                                                                //BIG 3:
    ~List(){
        _clear_list(_head_ptr);
    }
    List(const List<T> &copyThis){
        _head_ptr = _copy_list(copyThis._head_ptr);
        _size = copyThis._size;
    }
    List& operator =(const List& RHS){
        if (this == &RHS){
            return *this;
        }
        if (_head_ptr != nullptr){
            _clear_list(_head_ptr);
        }
        _size = RHS._size;
        _head_ptr = _copy_list(RHS._head_ptr);
        return *this;
    }

    //int size();
    Iterator insert_head(T i){
        node<T>* headptr = _insert_head(_head_ptr, i);
        _size++;
        return Iterator(headptr);
    }                           //insert at the head of list
    Iterator insert_after(T i, Iterator iMarker){
        node<T>* temp = _insert_after(_head_ptr, iMarker._ptr, i);             //iMarker now points to temp
        _size++;
        return Iterator(temp);                 //returns newly reassigned pointer to new inserted value
    
    }    //insert after marker
    Iterator insert_before(T i, Iterator iMarker){
        node<T>* temp = _insert_before(_head_ptr, iMarker._ptr, i);              //returns pointer to newly inserted node
        _size++;
        return Iterator(temp);    
    }   //insert before marker
    Iterator insert_sorted(T i){
            bool ascending = true;
        node<T>* temp = _insert_sorted(_head_ptr, i, ascending);
        _size++;
        return Iterator(temp);
    }                         //insert in a sorted list

    T Delete(List<T>::Iterator iMarker){
        T popped = _delete_node(_head_ptr, iMarker._ptr);
        _size--;
        return popped;
    }        //delete node pointed to by marker
    void Print() const{
        _print_list(_head_ptr);
    }
    Iterator search(const T &key){
        node<T>* ptr = _search_list(_head_ptr, key);
        return Iterator(ptr);
    }                      //return Iterator to node [key]
    Iterator prev(Iterator iMarker){
        node<T>* temp = _previous_node(_head_ptr, iMarker._ptr);
        return Iterator(temp);
    }                            //previous node to marker

    T& operator[](int index){
        T temp = _at(_head_ptr, index);
        return temp;
    }                           //return item at position index
    Iterator begin() const{
        return Iterator(_head_ptr);
    }                                     //Iterator to the head node
    Iterator end() const{
        return Iterator();
    }                                       //Iterator to NULL
    Iterator last_node() const{
        node<T>* temp = _last_node(_head_ptr);
        return Iterator(temp);
    }                                  //Iterator to the last node
    bool empty()const {
        return _head_ptr == NULL;
    }

    template <class U>                                          //Note the template arg U
    friend ostream& operator <<(ostream& outs, const List<U>& l){
        l.Print();
        return outs;
    }

    int size()const { 
        return _size; 
    }

private:
    node<T>* _head_ptr;
    int _size;
};

#endif //LIST_ITERATED_H