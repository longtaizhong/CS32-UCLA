//
//  Set.cpp
//  Project2
//
//  Created by Ryan Zhong  on 4/18/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//
#include "Set.h"


Set::Set():dummy(ItemType(), nullptr,nullptr){
    m_size = 0;             //Initialize size as 0, and when the set is first created, next node and previous                         nodes are both null.
}        // Create an empty set (i.e., one with no items).

Set::~Set(){
    //delete items thats after dummy until its empty 
    while(!empty()){
        ItemType x = dummy.m_next->m_data;
        erase(x);
    }
    
}

Set::Set(const Set& other):Set(){   //Initialize dummy
    m_size = other.m_size;          //have size equal to each other
 
    Node* p = other.dummy.m_next;
    for(int i = 0; i<other.size(); i++){        //Iterate through the nodes in other and insert the element into this Set
        insert(p->m_data);
        p = p->m_next;
    }
}

Set& Set::operator=(Set other){ //Swap and return
    if(this!=&other)        // check to make sure the two sets are different sets.
    {
        Set temp(other);    // copy and swap
        swap(temp);
    }
    return *this;
}

bool Set::empty() const{
    if(dummy.m_next == nullptr){
        return true;                //If one after dummy(first node) is null, that means set doesnt have anything
    }
    
    return false;
}  // Return true if the set is empty, otherwise false.

int Set::size() const{
    return m_size;
}    // Return the number of items in the set.

bool Set::insert(const ItemType& value){
    if(contains(value)){            //if the value exists in Set, dont insert
        return false;
    }
    Node* prev = &dummy;            //Set previous node as dummy
    Node* curr = dummy.m_next;      //set node curr as whatever thats after dummy
    
    for(;; prev = curr, curr = curr->m_next){
        //execute whats inside, if its still not out of the loop, then make prev as curr, and curr as nodeafter curr
    
        if( curr == nullptr || value <= curr->m_data){ //if the node is at the end, or the node being inserted it smaller than one after
            Node* toBeInserted = new Node(value, prev, curr);
            prev->m_next = toBeInserted;
            if(curr != nullptr){
                curr->m_prev = toBeInserted;        //If the node is not being added to the very end, then change the next node's prev to the new node that is being added.
            }
            
            m_size++;
            return true;
        }
    }
  //  return false;
}
// Insert value into the set if it is not already present.  Return
// true if the value is actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// was already in the set or because the set has a fixed capacity and
// is full).

bool Set::erase(const ItemType& value){
    
    for(Node* p = dummy.m_next; p!= nullptr; p = p->m_next){        //iterates the loop until meets NULL, which is end of list
        if(p->m_data == value){
    //
            if(p->m_next == nullptr){           //If the item is at the very end, then remove the item and change that to nullptr.
                p->m_prev->m_next = nullptr;
                
                
            }else{
            (p->m_prev)->m_next = p->m_next;        //otherwise update the links
            (p->m_next)->m_prev = p->m_prev;
            }
            
            delete p;
            m_size--;
            return true;
        }
    }
    return false;
  
}
// Remove the value from the set if it is present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

bool Set::contains(const ItemType& value) const{
    for(Node* p = dummy.m_next; p != nullptr; p = p->m_next){
        if(p->m_data == value){         //if the m_data matches with value, then return true
            return true;
        }
    }
    return false;
}
// Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value) const{
    if(i>=m_size || i<0){       ///if the i is bigger than the size or is negative, then immediately return false
        return false;
    }
    int counter = 0;
    for(Node* p = dummy.m_next; counter<=i; p = p->m_next ){        //update the itemtype 
        if(i == counter){
            value = p->m_data;
        }
        
        counter++;
    }
    return true;
}
// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.

void Set::swap(Set& other){
    Node* temp = dummy.m_next;
    dummy.m_next = other.dummy.m_next;
    other.dummy.m_next = temp;
    dummy.m_next->m_prev = &dummy;
    other.dummy.m_next->m_prev = &(other.dummy);
    
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}
// Exchange the contents of this set with the other one.
/*
void Set::dump() const{
    
    for(Node* p = dummy.m_next; p != nullptr; p = p->m_next){
        cerr<< p->m_data<<endl;
    }
 
}*/

void unite(const Set& s1, const Set& s2, Set& result){
  //  Set united;
    ItemType x;
    for(int i = 0; i<s1.size(); i++){      //insert every node of s1 into the result, the insert will handle the duplicates
        s1.get(i, x);
        result.insert(x);
    }
    for(int j = 0; j<s2.size(); j++){       //insert every node of s2 into the result
        s2.get(j, x);
        result.insert(x);
    }
   
}

void subtract(const Set& s1, const Set& s2, Set& result){
    
    ItemType x;
    for(int i = 0; i<s1.size(); i++){
        s1.get(i,x);
        if(!s2.contains(x)){ //if there is an element in s1 that is not being contained in s2, then add it to result 
            result.insert(x);
        }
    }
}
