//
//  Actor.cpp
//  Project3
//
//  Created by Ryan Zhong  on 5/11/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include "Actor.h"
#include "utilities.h"
#include "Dungeon.h"
using namespace std;
#include <iostream>


//smellDistance is 0 by DEFAULT because Dragon and player dont move using it
int Actor:: smellDistance() const{
    return 0;
}

//Delete weapons that actors have
Actor:: ~Actor(){
    
        
   // cerr<< "removing weapon of " << getName()<< endl;
   // delete m_weapon;
   // delete m_dropItem;
    
};
//Constructor for player, create new weapon and make it its personall weapon, also set health
Player::Player(int rowPos, int colPos, string name, char symbol):Actor(rowPos, colPos, "Player", '@'){
    GameObjects* w = new ShortSword("short sword", 5, 5);
    setWeapon(w);
    setHealth(20);
    setSleep(false, 0);
    m_maxHealth = 20;
    setDropItem(nullptr);
}

//Player::~Player(){
//}


bool Player:: dropItem(){
    return false;
}

//SnakeWoman uses magic fangs of sleep as weapon, and the hp is from 3 to 6
SnakeWoman::SnakeWoman( int rowPos, int colPos, string name, char symbol):Actor( rowPos, colPos, "Snakewoman", 'S'){
    GameObjects* w = new MFS("magic fangs of sleep", 5, 5);
    setWeapon(w);
    
    GameObjects* d = new MFS("magic fangs of sleep", 5, 5);
    setDropItem(d);
    int hp = randInt(3,6);
    setHealth(hp);
    setSleep(false, 0);
}

int SnakeWoman:: strength(){
    return 2;
}
int SnakeWoman:: dexterity(){
    return 3;
}
int SnakeWoman:: armor(){
    return 2;
}

bool SnakeWoman::dropItem(){
    int a = randInt(1,3);
    if(a == 1){
        return true;
    }
    return false;
}
/*
GameObjects* SnakeWoman::getDropItem(){
    GameObjects* w = new MFS("magic fangs of sleep", 3, 3);
    return w;
}*/

//Bogeyman Constructor. Uses short sword and has health between 5 to 10
BogeyMan::BogeyMan( int rowPos, int colPos, string name, char symbol):Actor(rowPos, colPos, "Bogeyman", 'B'){
    GameObjects* w = new ShortSword("short sword", 5, 5);
    setWeapon(w);
    GameObjects* d = new ShortSword("short sword", 5, 5);
    setDropItem(d);
    int hp = randInt(5,10);
    setHealth(hp);
    setSleep(false, 0);
}

int BogeyMan:: strength(){
    
    return randInt(2,3);
}
int BogeyMan:: dexterity(){
    return randInt(2,3);
}
int BogeyMan:: armor(){
    return 2;
}

bool BogeyMan::dropItem(){
    int a = randInt(1,10);
    if(a == 1){
        return true;
    }
    return false;
}



//Dragon uses longsword by default and hp is from 20 to 25
Dragon::Dragon(int rowPos, int colPos, string name, char symbol):Actor( rowPos, colPos, "Dragon", 'D'){
    GameObjects* w = new LongSword("long sword", 5, 5);
    setWeapon(w);
    
    int hp = randInt(20,25);
    setHealth(hp);
    setSleep(false, 0);
    
    GameObjects* s = nullptr;
    int a = randInt(1,5);
    switch(a){
        case 1:
            s = new Scroll("scroll of teleportation", 5, 5);
            break;
        case 2:
            s = new Scroll("scroll of improve armor", 5, 5);
            break;
        case 3:
            s = new Scroll("scroll of raise strength", 5, 5);
            break;
        case 4:
            s = new Scroll("scroll of enhance health", 5, 5);
            break;
        case 5:
            s = new Scroll("scroll of enhance dexterity", 5, 5);
            break;
    }
    setDropItem(s);
    
    
}

int Dragon:: strength(){
    
    return 4;
}
int Dragon:: dexterity(){
    return 4;
}
int Dragon:: armor(){
    return 4;
}

bool Dragon::dropItem(){
    int a = randInt(1,1);
    if(a == 1){
        return true;
    }
    return false;
}

//DEecide which scroll is going to be dropped when a dragon dies.
/*
GameObjects* Dragon::getDropItem(){
    GameObjects* s = nullptr;
    int a = randInt(1,5);
    switch(a){
        case 1:
            s = new Scroll("scroll of teleportation", 5, 5);
            break;
        case 2:
            s = new Scroll("scroll of improve armor", 5, 5);
            break;
        case 3:
            s = new Scroll("scroll of raise strength", 5, 5);
            break;
        case 4:
            s = new Scroll("scroll of enhance health", 5, 5);
            break;
        case 5:
            s = new Scroll("scroll of enhance dexterity", 5, 5);
            break;
    }
    return s;
}*/

//Constructor for goblin 
Goblin::Goblin( int rowPos, int colPos, string name, char symbol):Actor(rowPos, colPos, "Goblin", 'G'){
    GameObjects* w = new ShortSword("short sword", 5, 5);
    setWeapon(w);
    int hp = randInt(15,20);
    setHealth(hp);
    setSleep(false, 0);
    GameObjects* s = new ShortSword("short sword", 5, 5);
    setDropItem(s);
}

int Goblin:: strength(){
    return 3;
}
int Goblin:: dexterity(){
    return 1;
}
int Goblin:: armor(){
    return 1;
}

bool Goblin::dropItem(){
    int a = randInt(1,3);
    if(a == 1){
        return true;
    }
    return false;
}


