//
//  Set.h
//  Project2
//
//  Created by Ryan Zhong  on 4/18/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#ifndef Set_h
#define Set_h
#include <iostream>
#include <string>
using namespace std;
using ItemType = string;




class Set
{
public:
    Set();         // Create an empty set (i.e., one with no items).
    
    ~Set();
    
    Set(const Set& other);
    Set& operator=(Set other);
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value is actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if it is present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
  //  void dump() const;
    
private:
    //Structure Node takes argument of value, previous and next nodes. Double Linked Array,Nodes are then initialized
    struct Node{
        Node (const ItemType& value, Node* m_prev, Node* m_next):m_data(value),m_prev(m_prev),m_next(m_next){}
        
        ItemType m_data;
        Node *m_next;
        Node *m_prev;
    };
    Node dummy;     //Have private member variable dummy so that it clears corner cases
    int m_size;     //private member variable size
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */

