#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>

#include "../node/node.h"

using namespace std;


//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);


template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//insert rear
template <typename T>
node<T>* _insert_rear(node<T>* rear, T insert_this);

//remove headptr and return new headptr
template <typename T>
T _remove_head(node<T>*& head);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head,
                                node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*&head,
                        node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//print_pointers from a Queue List of pointers 
template <typename T>
void _print_pointers(node<T>* head);

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines. 
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending=true);       //insert

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head,
                                        T item,
                                        bool ascending=true);
//node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head,
                                T item,
                                bool ascending=true);
//Last Node in the list
template <typename T>
node<T>* _last_node(node<T>* head);            



//===============definitions===============
//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head){
    // if(head == nullptr){
    //     cout << "list is empty" << endl;
    // }
    if(head != nullptr){
        cout << "H ->";
        node<T>* walker = head;
        while (walker != nullptr){
            cout << "[" << walker->_item << "]->";
            walker = walker->_next;
        }
        cout << "|||" << endl;
    }
}

template <typename T>
void _print_list_backwards(node<T> *head){
    int counter = 1;
    node<T>* walker = head;
    while (walker->_next != nullptr){       //takes the list all the way to the end
        walker = walker->_next;
        counter++;                          //tells the future for loop when to stop
    }
    cout << "||| ->";
    for(int i = counter; i > 0; i--){
        cout << "[" << walker->_item << "]->";
        walker = _previous_node(head, walker);
    }
    cout << "H" << endl;
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key){
    if (head == nullptr){
        return nullptr;
    }
    //head is not null if you are here.
    node<T>* walker1 = head;

    while (walker1 != nullptr){  //checks walker2 node item
        if (walker1->_item == key)
            return walker1;
        walker1 = walker1->_next;
    }
    //if you are here, then the item did not exist in this list
    return nullptr;
}


template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this){
    node<T>* temp = new node<T>(insert_this);
    temp->_next = head;
    head = temp;
    return head;
}

//insert after ptr
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this){
    if (head == nullptr){
        node<T>* headptr = _insert_head(head, insert_this);
        return headptr;
    }
    node<T>* temp = new node<T>(insert_this);     //makes new node
    temp->_next = after_this->_next;         //temp points to next node in list
    after_this->_next = temp;                   //after_this now points to temp
    return after_this;                         //returns newly reassigned pointer to new inserted value
}

//insert before ptr
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this){
    node<T>* temp = new node<T>(insert_this);
    node<T>* where_i_goes = _previous_node(head, before_this);
    if (where_i_goes == nullptr){   //if prev return nullptr, call insert_head and return head
        head = _insert_head(head, insert_this);
        return head;
    }
    else{
        temp = _insert_after(head, where_i_goes, insert_this);
        return temp;                    //returns pointer to newly inserted node
    }
}

//insert rear
template <typename T>
node<T>* _insert_rear(node<T>* rear, T insert_this){
    node<T>* rear_end = new node<T>(insert_this);
    rear->_next = rear_end;
    return rear_end; 
}

//remove headptr and return new headptr
template <typename T>
T _remove_head(node<T>*& head){
    if(head == nullptr){
        return T();
    }
    node<T>* temp = head;
    T popped = temp->_item;
    head = temp->_next;
    delete temp;
    return popped;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prev_to_this){
    if (prev_to_this == nullptr){  //if at beginning of list is nullptr
        return nullptr;
    }
    if (prev_to_this == head){
        return nullptr;
    }
    node<T>* walker = head;
    while (walker != nullptr){   //searches through list to find matching ptr
        if (walker->_next == prev_to_this){
            return walker;
        }
        else{
            walker = walker->_next;  //if not found, advances
        }
    }
    assert(walker != nullptr && "error prev: prev_to_this not found"); //if not found in entire list, asserts an error
}    //get the previous node; start at beginning and look for iMarker


//delete, return item
template <typename T>
T _delete_node(node<T>*&head, node<T>* delete_this){
    assert(delete_this != nullptr && "Error: delete this is equal to nullptr");
    if(delete_this == head){
        T popped = _remove_head(head);
        return popped;
    }
    if (delete_this != nullptr){
        T popped = delete_this->_item;      //holds item value to be returned
        node<T>* temp = _previous_node(head, delete_this);  //finding the prior node
        temp->_next = delete_this->_next;               //making sure there are no gaps
        delete delete_this;
        //cout << "popped: " << popped << endl;                     //releases memory 
        return popped;
    }
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head){
    if (head == nullptr){
        return nullptr;
    }
    //if we are here, head is NOT empty
    node<T>* head_walker = head;
    node<T>* copied = new node<T>(head_walker->_item);      //head of copied list
    node<T>* copied_walker = copied;                    //walker for the copied list

    head_walker = head_walker->_next;           //moving head from first node to second

    while (head_walker != nullptr){
        //if we are here, there are more than 2 nodes in original list
        node<T>* temp = _insert_after(copied, copied_walker, head_walker->_item);   //copies item into new list, moves walker
        copied_walker = copied_walker->_next;
        head_walker = head_walker->_next;
    }
    return copied;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){
    if(src == nullptr){
        return nullptr;
    }
    //if we are here, src is NOT empty
    node<T>* src_walker = src;
    dest = nullptr;
    dest = new node<T>(src_walker->_item);      //assuming dest is empty
    node<T>* dest_walker = dest;
    src_walker = src_walker->_next;             //moving src to second node

    while(src_walker != nullptr){
        //if we are here, there are 2 or more nodes in the original list
        node<T>* temp = _insert_after(dest, dest_walker, src_walker->_item);
        dest_walker = dest_walker->_next;
        src_walker = src_walker->_next;
    }
    return dest_walker; 
}

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head){
    const bool debug = false;
    while(head != nullptr){
        T popped = _remove_head(head);
        // T popped = _delete_node(head, head);  **not working**
        if (debug){
            cout << "popped: " << popped << endl;
            _print_list(head);
        }
    }
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos){
    node<T>* walker = head;
    for(int i = 0; i < pos; i++){   //will keep movin until i = pos
        assert(walker != nullptr && "error pos: pos not found; not enough nodes"); //if list runs out of nodes
        walker = walker->_next;         //moves to next node
    }
    return walker->_item;           //returns walker item 
}


//print_pointers from a Queue List of pointers 
template <typename T>
void _print_pointers(node<T>* head){
    node<T>* walker = head; 
    cout << "Queue H: ";
    while(walker != nullptr){
        cout << "[" << *walker->_item << "]->";
        walker = walker->_next; 
    }
    cout << "|||" << endl;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//                              Sorted List Routines. 
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending){
    node<T>* sorted;
    node<T>* put_here = _where_this_goes(head, item, ascending);
        if(put_here == nullptr){
            sorted = _insert_head(head, item);
            return sorted;
        }
        if(put_here->_item == item){
            return put_here;
        }
        sorted = _insert_after(head, put_here, item);
        return sorted;
}       //insert but if dupe, don' t add

//insert or add if a dup
template <typename T>
node<T>* _insert_sorted_and_add(node<T>* &head, T item, bool ascending){
    node<T>* sorted;
    node<T>* put_here = _where_this_goes(head, item, ascending);
        if(put_here == nullptr){                     //if head is empty OR if item needs to go FIRST
            sorted = _insert_head(head, item);       //returns headptr
            return sorted;
        }
        sorted = _insert_after(head, put_here, item);
        return sorted;
}
//returns node after which this item goes order: 0 ascending
template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending){
    if (head == nullptr){       //if list is empty, return null
        return nullptr;
    }
    node<T>* follower = head;
    node<T>* leader = head->_next;

    //loop:
    //cout<<setw(7)<<"leader"<<setw(7)<<"follower"<<endl;

    if(ascending == true){
        if (follower->_item > item){
            //cout << "less than follower item: returned null" << endl;
            return nullptr;
        }
        while(leader != nullptr){
            // cout <<setw(7)<< leader->_item;
            // cout << setw(7)<< follower->_item<<endl;
            if(leader->_item > item){
                return follower;
            }
            leader = leader->_next;
            follower = follower->_next;
        }
        return follower;
    }
    if(ascending == false){
        if (follower->_item < item){
        //cout << "less than follower item: returned null" << endl;
        return nullptr;
        }
        while(leader != nullptr){
            // cout <<setw(7)<< leader->_item;
            // cout << setw(7)<< follower->_item<<endl;
            if(leader->_item < item){
                return follower;
            }
            leader = leader->_next;
            follower = follower->_next;
        }
        return follower;
    }
}
//Last Node in the list **stupid dont do**
template <typename T>
node<T>* _last_node(node<T>* head){
    if (head == nullptr){
        return nullptr;
    }
    node<T>* leader = head->_next;
    node<T>* follower = head;

    while(leader != nullptr){
        leader = leader->_next;
        follower = follower->_next;
    }
    return follower;
}            //


#endif      //LINKED_LIST_FUNCTIONS_H