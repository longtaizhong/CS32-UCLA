//
//  eval.cpp
//  HW2 eval
//
//  Created by Ryan Zhong  on 4/27/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;


string removeSpaces(string str)     //Removes all spaces in a string
{
    string s;
    for(int i=0;i<str.length();i++)
        if(str[i]!=' ')
            s.push_back(str[i]);
    return s;
}

bool properSyntax(string infix){
    int unclosedOpen = 0;
    string str = removeSpaces(infix);
    if(str.size() == 0 || str[0] == '&' || str[0] == '^' || str[0] == ')'){
        // if first letter is invalid, return false
        return false;
    }
    if(str[str.size()-1] == '&' || str[str.size()-1] == '^' ||  str[str.size()-1] == '(' || str[str.size()-1] == '!'){
        return false;
    }
    for(int i = 0; i < str.size(); i++){
        char curr;
        char prev;
        
        if(i == 0){
            curr = str[i];
            prev = '\0';
        }else{
            curr = str[i];
            prev = str[i-1];
        }
        //BUNCH OF CONDITIONS TO CHECK CURR AND PREV
        if(curr == 'T' || curr == 'F'|| curr == '!' || curr == '^' || curr == '&' || curr == ')' || curr == '('){
        }else{
            return false;
        }
        if(curr == '&' || curr == '^' || curr == ')'){  //if operator is followed by another operator, return false except for !
            if(prev == '&' || prev == '^' || prev == '('){
                return false;
            }
        }
        if(curr == '(' || curr == 'T' || curr == 'F'){
            if(prev == 'T' || prev == 'F'){
                return false;
            }
        }
        if(curr == '!'){
            if(prev == 'F' || prev == 'T' || prev == ')'){
                return false;
            }
        }
        //Check if there is an unclosed parenthesis.
        if(curr == '('){
            unclosedOpen++;
        }
        if(curr == ')'){
            if(unclosedOpen == 0){
                return false;
            }else{
                unclosedOpen--;
            }
        }
    }
    if(unclosedOpen != 0){  //if there are more than necessary parenthetis, then return false
        return false;
    }
    return true;
}

bool hasLowerPrecedance(char a, char b){        //Helper function to determine if the first character has lower precedence than the second one
    if(a == '^'){
        if(b == '&' || b == '^' || b == '!'){
            return true;
        }
    }
    if(a == '&'){
        if(b== '!' || b == '&'){
            return true;
        }
    }
    if(a == '!'){
        if(b == '!'){
            return true;
        }
    }
    return false;
}
string convertToPostfix(string infix){
    stack<char> operatorStack;
    string pf = "";
    for(int i = 0; i<infix.size(); i++){
        
        switch(infix[i]){
            case 'T':
            case 'F':
                pf+= infix[i];
                break;
            case '(':
                operatorStack.push(infix[i]);
                break;
            case ')':
                while(operatorStack.top() != '('){
                    char topStack = operatorStack.top();
                    pf += topStack;
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '&':
            case '^':
            case '!':
                while(!operatorStack.empty() && hasLowerPrecedance(infix[i], operatorStack.top())){
                    char topStack = operatorStack.top();
                    pf += topStack;
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
        }
    }
    while(!operatorStack.empty()){
        char topStack = operatorStack.top();
        pf += topStack;
        operatorStack.pop();
    }
    return pf;
}


int evaluate(string infix, string& postfix, bool& result)
{
    if(!properSyntax(infix)){
        return 1;
    }
    string fixed = convertToPostfix(infix);
    postfix = fixed;
    stack<char> operandStack;
    for(int i = 0; i<fixed.size(); i++){
        if(fixed[i] == 'T' || fixed[i] == 'F'){
            operandStack.push(fixed[i]);
        }else if(fixed[i] == '!'){
            char op = operandStack.top();
            operandStack.pop();
            if(op == 'T'){
                operandStack.push('F');
            }else{
                operandStack.push('T');
            }
        }else{
            char op1 = operandStack.top();
            operandStack.pop();
            char op2 = operandStack.top();
            operandStack.pop();
            if(fixed[i] == '&'){
                if(op1 == 'T' && op2 == 'T'){
                    operandStack.push('T');
                }else{
                    operandStack.push('F');
                }
            }
            if(fixed[i] == '^'){
                if(op1 == 'T' && op2 == 'F'){
                    operandStack.push('T');
                }else if(op1 == 'F' && op2 == 'T'){
                    operandStack.push('T');
                }else {
                    operandStack.push('F');
                }
            }
        }
    }
    if(operandStack.top() == 'T'){
        result = true;
    }else{
        result = false;
    }
    return 0;
}

/*
int main(){
    string pf;
    bool answer;
    
    //Testing if its valid infix
    assert(evaluate("T^ F", pf, answer) == 0);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0);
    assert(evaluate(" F  ", pf, answer) == 0 );
    assert(evaluate("((T))", pf, answer) == 0);
    
    //Testing infix Syntax == TRUE
    assert(evaluate("(!    T)", pf, answer) == 0);
    assert(evaluate("!(((!T )))", pf, answer) == 0);
    assert(evaluate("!F&!T^F&  T^F^!T", pf, answer) == 0);
    assert(evaluate("T^  (!F)", pf, answer) == 0);
    assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0);
    
    //Testing infix Syntax == FALSE
    assert(evaluate("(!    T)FT", pf, answer) == 1);
    assert(evaluate("((F&T^!F)))", pf, answer) == 1);
    assert(evaluate("!T&!F^T", pf, answer) == 0);
    

    //Testing Everything combined
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
           &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("T^T", pf, answer) == 0 && pf == "TT^" && !answer);
    assert(evaluate("(T&!F)^F^(F&T)", pf, answer) == 0 && answer);
    
    cout << "Passed all tests" << endl;
}

*/
