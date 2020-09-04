//
//  Dungeon.h
//  Project3
//
//  Created by Ryan Zhong  on 5/11/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#ifndef DUNGEON_INCLUDED
#define DUNGEON_INCLUDED

#include "globals.h"
#include "Actor.h"
#include "utilities.h"
#include "GameObjects.h"
#include <queue>
#include "Game.h"

//Class for Coordinate



class Dungeon{
public:
    Dungeon();
    ~Dungeon();
    //bunch of getters and setters
    void generate();
    void display();
    
    void excavate(int topLeftRow, int topLeftCol, int height, int width);
    void makeCorridor(int midPointR, int midPointL);
    void makeCorridorUp(int midPointR, int midPointL);
    
    void setGrid(int row, int col, char c);
    char getGrid(int row, int col){return m_maze[row][col];};
    
    
    char getBaseGrid(int row, int col){return m_baseGrid[row][col];}
    void setBaseGrid(int row, int rol, char c);
    
    bool addPlayer(int row, int col);
 
    
    
    
    void generateStairCase();
    void generateGoldenIdol();
    
    void moveCharacters(char c);
    void moveMonsters();
    
    void pickUpObjects();
    
    bool movable(int r, int c);
    bool canPickUp(GameObjects* &w, int &indexGlist);
    
    void yieldWeaponOrScroll(char a);
   
    void displayInventory();
    
    void addMonsters();
    bool indexOfMonsAt(int r, int c, int &index);
    
    void attack(Actor* attacker, Actor* defender, string &msg);
    
    void playGame(Game* g, char command);
    void moveMonst(Actor* monster);
    
    bool nextToPlayer(Actor* monster);
    bool moveCloser(Actor* monster);
    
    void printMsg();
    void descend();
    
    void setToSleep(Actor* defender);
    
    int goblinStep(Actor* goblin, int sr, int sc);
    bool occupied(int r, int c);
    
    void cheat();
    bool isItemAt(int r, int c);
private:
    bool dungeon_run;
    bool m_run;
    bool pickUp;
    int m_level;
    int m_numBox;
    char m_baseGrid[ROWS][COLS];
    char m_maze[ROWS][COLS];
    char goblinGrid[ROWS][COLS];
    
    Player* m_player;
    StairCase* m_StairCase;
    goldenIdol* m_GoldenIdol;
    vector<GameObjects*> glist;
    vector<GameObjects*> inventory;
    
    vector<Actor*> m_monsters;
    vector<string> m_msgs;
    vector<string> m_goblinDir;
    
    
};




#endif /* Dungeon_h */
