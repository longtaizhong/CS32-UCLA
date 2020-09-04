// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

#include <string>
using namespace std;

class Dungeon;

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    ~Game();
    void setRunFalse(){m_run = false;};

private:
    bool m_run;
    Dungeon* m_Dungeon;

   
};




#endif // GAME_INCLUDED
