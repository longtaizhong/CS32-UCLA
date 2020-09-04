//
//  Game.h
//  CS32 Project1
//
//  Created by Ryan Zhong  on 4/3/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#ifndef Game_h
#define Game_h
#include <string>
using namespace std;
class Arena;
class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nVampires);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
};

#endif /* Game_h */
