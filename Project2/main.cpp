//
//  main.cpp
//  Project2
//
//  Created by Ryan Zhong  on 4/18/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include <iostream>
#include "Set.h"
#include <cassert>
int main(int argc, const char * argv[]) {
    
    //tests were performed by alias being int
    Set s;      //Inserting in different size orders
    s.insert(50);
    s.insert(30);
    s.insert(20);
    s.insert(10);
    s.insert(60);
    s.insert(90);
    
    //Inserting duplicates
    s.insert(20);
    s.insert(10);
    s.insert(50);
    
    
    //Testing contains
    assert(s.contains(30) && s.contains(10) && !s.contains(40) && !s.contains(39));
    
    //cerr<<"Testing get function" <<endl;
    ItemType x = 0;
    
    assert(s.get(0,x) && x == 10);
    assert(s.get(1,x) && x == 20);
    assert(s.get(2,x) && x == 30);
    assert(s.get(3,x) && x == 50);
    assert(s.get(4,x) && x == 60);
    assert(!s.get(342,x));
    
   // Testing erase function
    s.erase(60);
    s.erase(60);
    //Test if re-linking works when node is removed
    assert(s.get(4,x) && x == 90);
    s.erase(400);
    s.erase(20);
    s.erase(50);
    
  //  s.erase(90);
    //s.erase(10);
    //s.erase(30);
    
    
    //Removing all the variables and then testing empty
 //   assert(s.empty());
//    cerr<<s.size()<<endl;
    
    //Testing swap functions
    
    Set ss1;
    ss1.insert(100);
    ss1.insert(400);
    ss1.insert(300);
    ss1.insert(700);
    
    Set ss2;
    ss2.insert(5);
    ss2.insert(1);
    ss2.insert(4231);
    ss2.insert(331);
    ss2.insert(342);
    ss2.insert(11);
    
    
    //swap ss1 and ss2, now print ss1 (should have contents of ss2)
    ss1.swap(ss2);
  //  cerr<<"print ss1, which now has content of ss2"<<endl;
  //  ss1.dump();
    
  //  ss2.swap(ss1);
    
    ItemType y;
    assert(ss2.get(0, y) && y == 100);
    assert(ss2.get(1, y) && y == 300);
    //also test the size
    assert(ss2.size() == 4);
    //swap ss1 and ss2, now print ss2 (should have contents of ss1)
    assert(ss1.get(0,y) && y == 1);
    assert(ss1.get(1,y) && y == 5);
    assert(ss1.size() == 6);
    
    
   
 
    //testing unite function
    Set result;
    unite(ss1, ss2,result);
   // result.dump();
    ItemType z;
    assert(result.get(0,z) && z == 1);
    assert(result.get(4,z) && z == 300);
    assert(result.get(7,z) && z == 400);
    assert(result.size() == 10);
    
    
   //testing subtract function
    
    Set ss5;
    ss5.insert(10);
    ss5.insert(20);
    ss5.insert(30);
    ss5.insert(40);
    ss5.insert(50);
    ss5.insert(60);
    
    Set ss6;
    ss6.insert(10);
    ss6.insert(40);
    ss6.insert(90);
    ss6.insert(110);
    ss6.insert(20);
    
    Set result2;
    subtract(ss5, ss6, result2);
    assert(result2.get(0,y) && y ==30);
    assert(result2.get(1,y) && y ==50);
    assert(result2.get(2,y) && y ==60);
    
    //Test the other way around
    Set result3;
    subtract(ss6,ss5,result3);
    assert(result3.get(0,y) && y == 90);
    assert(result3.get(1,y) && y == 110);
    assert(!result3.get(2,y));
    
    //Set now should be empty and contains no node
    Set result4;

    subtract(ss6,ss6,result4);
    assert(result4.empty());
    
    cerr<<"passed all tests"<<endl;
    
    
    
}


