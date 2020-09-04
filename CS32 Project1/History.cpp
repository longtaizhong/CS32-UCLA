//
//  History.cpp
//  CS32 Project1
//
//  Created by Ryan Zhong  on 4/3/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include "History.h"
#include "Arena.h"

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    for(int i = 1; i<=m_rows; i++){
        for(int j = 1; j<=m_cols; j++){
            m_historyGrid[i-1][j-1] = '.';
        }
    }
}

bool History::record(int r, int c){
    if(r>=1 && c>=1 && r<=m_rows && c<=m_cols )
    {
        if(m_historyGrid[r-1][c-1] >= 'A' && m_historyGrid[r-1][c-1] <= 'Z'){
            m_historyGrid[r-1][c-1]++;
        }else{
            m_historyGrid[r-1][c-1] = 'A';
        }
    
        return true;
    }else{
        return false;
    }
}

void History::display() const{
    clearScreen();
    for (int r = 1; r <=m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
            cout << m_historyGrid[r-1][c-1];
        cout << endl;
    }
    cout<<endl;
}

