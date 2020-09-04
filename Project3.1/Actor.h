//
//  Actor.hpp
//  Project3
//
//  Created by Ryan Zhong  on 5/11/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include <string>
#include "GameObjects.h"

using namespace std;

class Dungeon;
class GameObjects;
class Actor{
public:
    Actor(int rowPos, int colPos, string name, char symbol):m_rowPos(rowPos), m_colPos(colPos), m_name(name), m_symbol(symbol), m_weapon(nullptr) {
        m_strength = 2;
        m_armor = 2;
        m_dexterity = 2;
    }
    virtual ~Actor();
    
    //Lot of getters and setters
    //Accessors
    int getRowPos(){return m_rowPos;};
    int getColPos(){return m_colPos;};

    string getName(){return m_name;};
    char getSymbol(){return m_symbol;};
    
    int getHealth(){return m_health;};
    
    void setHealth(int hp){m_health = hp;};
    
    virtual bool dropItem() = 0;
    virtual int strength(){return m_strength;};
    virtual int dexterity(){return m_dexterity;} ;
    virtual int armor(){return m_armor;};
    virtual int smellDistance() const;
    
    bool isSleep(){ return m_sleep;};
    void setSleep(bool sleep, int sleepTurns){m_sleep = sleep; m_sleepTurns = sleepTurns;};
    void setSleepTurns(int sleepTurns){m_sleepTurns = sleepTurns;};
    int getSleepTurns(){return m_sleepTurns;};
    
    void setArmor(int newArmor){m_armor = newArmor; };
    void setStrength(int newStrength){ m_strength =  newStrength;};
    void setDexterity(int newDexterity){m_dexterity = newDexterity;};
    
    bool attemptMove();
    //Setters
    void setRowPos(int newRowPos){
        m_rowPos = newRowPos;
    };
    void setColPos(int newColPos){
        m_colPos = newColPos;
    };
    GameObjects* getWeapon(){return m_weapon;};
    void setWeapon(GameObjects* w){m_weapon = w;};
 
    
  //  void move(int dir);
    bool attemptMove(int dir, int& r, int& c);
    
    GameObjects* getDropItem(){return m_dropItem;};
    virtual void setDropItem(GameObjects* w){m_dropItem = w;};
    
    
private:
    int m_armor;
    int m_dexterity;
    int m_strength;
    
    int m_sleepTurns;
    bool m_sleep;
    int m_health;
    GameObjects* m_weapon;
    GameObjects* m_dropItem;
   
    int m_rowPos;
    int m_colPos;
    string m_name;
    char m_symbol;
    
};

class Player: public Actor{
public:
    Player(int rowPos, int colPos, string name, char symbol);
  //  virtual void attack();
 
    virtual ~Player(){};
    virtual bool dropItem();
   // int increaseArmor(){m_armor}
   
    int maxHealth(){return m_maxHealth;};
    void setMaxHealth(int newMaxHealth){m_maxHealth = newMaxHealth;};
private:
    int m_maxHealth;
};


class SnakeWoman: public Actor{
public:
    SnakeWoman(int rowPos, int colPos, string name, char symbol);
    
    virtual ~SnakeWoman(){};
    virtual int strength();
    virtual int dexterity();
    virtual int armor();
    virtual bool dropItem();
    virtual int smellDistance() const{return 3;};
    
};

class BogeyMan: public Actor{
public:
    BogeyMan( int rowPos, int colPos, string name, char symbol);
    virtual ~BogeyMan(){};
    virtual int strength();
    virtual int dexterity();
    virtual int armor();
    virtual bool dropItem();
    virtual int smellDistance() const{return 5;};
    
};

class Dragon: public Actor{
public:
    Dragon( int rowPos, int colPos, string name, char symbol);
    virtual  ~Dragon(){};
    virtual int strength();
    virtual int dexterity();
    virtual int armor();
    virtual bool dropItem();
    
private:
    GameObjects* m_dropItem;
    
    
//CHANGE LATER
};

class Goblin: public Actor{
public:
    Goblin(int rowPos, int colPos, string name, char symbol);
    virtual ~Goblin(){};
    virtual int strength();
    virtual int dexterity();
    virtual int armor();
    virtual bool dropItem();
    
    
    

   
};



#endif /* Actor_hpp */
