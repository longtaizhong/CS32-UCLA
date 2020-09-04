//
//  Vampire.h
//  CS32 Project1
///Users/RyanZhong/Desktop/CS32 Project1/CS32 Project1/Arena.h
//  Created by Ryan Zhong  on 4/3/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#ifndef Vampire_h
#define Vampire_h
class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Vampire declaration.

class Vampire
{
public:
    // Constructor
    Vampire(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;
};

#endif /* Vampire_h */
