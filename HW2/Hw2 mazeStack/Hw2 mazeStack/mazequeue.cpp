//
//  mazequeue.cpp
//  Hw2 mazeStack
//
//  Created by Ryan Zhong  on 4/26/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include <stdio.h>
#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    queue<Coord> coordQueue;
    Coord a(sr,sc);
    coordQueue.push(a);
    maze[sr][sc] = 'D';
    
    while(!coordQueue.empty()){
        Coord b = coordQueue.front();
        cout<<b.r() << " , " << b.c()<<endl;
        coordQueue.pop();
        if(b.r() == er && b.c() == ec){
            return true;
        }
        if(b.r()+1 < 10 && maze[b.r()+1][b.c()]== '.'){//Moving SOUTH
            Coord c(b.r()+1, b.c());
            coordQueue.push(c);
            maze[b.r()+1][b.c()] = 'D';
        }
        if(b.c()-1 >-1 && maze[b.r()][b.c()-1]== '.'){//Moving WEST
            Coord c(b.r(), b.c()-1);
            coordQueue.push(c);
            maze[b.r()][b.c()-1] = 'D';
        }
        if(b.r()-1 > -1 && maze[b.r()-1][b.c()]== '.'){//Moving NORTH
            Coord c(b.r()-1, b.c());
            coordQueue.push(c);
            maze[b.r()-1][b.c()] = 'D';
        }
        if(b.c()+1 < 10 && maze[b.r()][b.c()+1]== '.'){//Moving EAST
            Coord c(b.r(), b.c()+1);
            coordQueue.push(c);
            maze[b.r()][b.c()+1] = 'D';
        }
        
    }
    
    return false;
}

/*
int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','X','.','.','.','X' },
        { 'X','.','X','X','.','X','X','.','.','X' },
        { 'X','X','X','.','.','.','.','X','.','X' },
        { 'X','.','X','X','X','.','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','.','.','X','.','X','.','.','X' },
        { 'X','X','X','X','X','.','X','.','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

*/
