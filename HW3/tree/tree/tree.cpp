//
//  main.cpp
//  tree
//
//  Created by Ryan Zhong  on 5/5/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3
int countContains(const string a1[], int n1, const string a2[], int n2)
{
    if(n2 <= 0){
        return 1;
    }
    if(n1 <= 0){
        return 0;
    }
   
    if(a1[n1-1] != a2[n2-1]){
        return countContains(a1, n1-1, a2, n2);
    }else{
        return countContains(a1, n1-1, a2, n2-1)+countContains(a1, n1-1, a2, n2);
    }
    
}


// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < divider come before all the other elements,
// and all the elements whose value is > divider come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= divider, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < divider
//   * for firstNotLess <= i < firstGreater, a[i] == divider
//   * for firstGreater <= i < n, a[i] > divider
// All the elements < divider end up in no particular order.
// All the elements > divider end up in no particular order.
void divide(string a[], int n, string divider, int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < divider
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == divider
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > divider
    
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > divider)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < divider)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
    /*
    for(int i = 0; i<4; i++){
        cerr<<a[i]<<endl;
    }*/
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if(n<=1){
        return;
    }
    int mid = (n/2)-1;
    int fnl;
    int fg;
    divide(a, n, a[mid], fnl, fg);
    order(a, fnl);
    order(a+fg, n-fg);
}



int main() {
    string a1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    string a2[] = {"stan", "cartman", "butters"};
    string a3[] = {"kyle", "cartman"};
    string a4[] = {};
    
  //Test countContains
    assert(countContains(a1, 7, a2, 3)== 2);
    assert(countContains(a1, 7, a3, 2) == 3);
    assert(countContains(a1, 7, a4, 0) == 1);
    assert(countContains(a4, 0, a4, 0) == 1);
    assert(countContains(a1, 7, a2, -5) == 1);
    
    //test order
    string a[] = {"aaa", "bbb", "ccc", "ddd", "eee"};
    string b[] = {"b", "sdfs", "aaa", "qqqq", "ddd", "popo"};
    
    order(a, 5);
    order(b, 6);
    /*
    for(int i = 0; i<5; i++){
        cerr<<a[i]<<endl;
    }
    for(int i = 0; i<6; i++){
        cerr<<b[i]<<endl;
    }
    */
    
}
