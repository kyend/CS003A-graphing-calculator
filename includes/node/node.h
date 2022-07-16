#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

using namespace std;

template <typename T>
struct node
{
public:
    node();
    node(T item);

    template <typename U>
    friend std::ostream& operator <<(std::ostream& outs, const node<U> &printMe);
    T _item;
    node* _next;
};

template <typename T>
node<T>::node(){
    _item = 0;
    _next = nullptr;
}

template <typename T>
node<T>::node(T item){
    _item = item;
    _next = nullptr;
}

template <typename U>
ostream& operator <<(ostream& outs, const node<U> &printMe){
    // node<U>*walker = printMe;
    // outs << "H->";
    // while (walker != nullptr){
        outs << "[" << printMe._item << "]->";
    //     walker = walker->_next;
    // }
    // outs << "|||" << endl;
    return outs;
}



#endif