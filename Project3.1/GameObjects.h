//
//  GameObjects.hpp
//  Project3.1
//
//  Created by Ryan Zhong  on 5/11/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#ifndef GameObjects_h
#define GameObjects_h
#include <string>
#include <stdio.h>
using namespace std;

class Actor;

//Structure for Gameobjects
class GameObjects{
public:
    GameObjects(string name, int r, int c);
    virtual ~GameObjects();
    virtual string actionString()= 0;
    string name() const;
    virtual int dexterity();
    virtual int damagePoints();
    int getRow();
    int getCol();
    void setRow(int r);
    void setCol(int c);
    virtual bool isScroll();
    
private:
    
    int m_row;
    int m_col;
    string m_name;
    
};
// for different weapons
class ShortSword: public GameObjects{
public:
    ShortSword(string name, int r, int c);
    virtual int dexterity();
    virtual int damagePoints();
    virtual string actionString();
    
};

class LongSword: public GameObjects{
public:
    LongSword(string name, int r, int c);
    virtual int dexterity();
    virtual int damagePoints();
    virtual string actionString();
    
};

class Mace: public GameObjects{
public:
    Mace(string name, int r, int c);
    virtual int dexterity();
    virtual int damagePoints();
    virtual string actionString();
    
};

class MFS: public GameObjects{
public:
    MFS(string name, int r, int c);
    virtual int dexterity();
    virtual int damagePoints();
    virtual string actionString();
};

class MagicAxes: public GameObjects{
public:
    MagicAxes(string name, int r, int c);
    virtual int dexterity();
    virtual int damagePoints();
    virtual string actionString();
};


class Scroll: public GameObjects{
public:
    Scroll(string name, int r, int c);
    virtual string actionString();
    virtual bool isScroll(){return true;};
};




//Class for staircase and goldenIdol
class StairCase{
public:
    StairCase(int r, int c);
    int getRow() {return m_row;};
    int getCol(){return m_col;};
private:
    int m_row;
    int m_col;
};

class goldenIdol{
public:
    goldenIdol(int r, int c);
    int getRow() {return m_row;};
    int getCol(){return m_col;};
private:
    int m_row;
    int m_col;
};


#endif /* GameObjects_hpp */
