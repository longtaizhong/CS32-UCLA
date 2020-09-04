// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include <iostream>

#include "globals.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance):m_Dungeon(nullptr)
{
    m_run = true;
    m_Dungeon = new Dungeon();

}
//Destructor for game
Game:: ~Game(){
    delete m_Dungeon;
}
//process input character to dungeon variable 
void Game::play()
{
    m_Dungeon->generate();
    m_Dungeon->display();
    cout << "Press q to exit game." << endl;
    
    while (m_run){
        m_Dungeon->playGame(this, getCharacter());
    }
}

/*
string Game::takePlayerTurn(){
    string playerMove;
    getline(cin, playerMove);
    
    Player* plalyer = m_Dungeon->getPlayer();
    
    
    
    
    return "";
}*/





// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
