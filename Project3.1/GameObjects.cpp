//
//  GameObjects.cpp
//  Project3.1
//
//  Created by Ryan Zhong  on 5/11/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include "GameObjects.h"
using namespace std;
#include <iostream>

GameObjects::GameObjects(string name, int r, int c):m_name(name),m_row(r), m_col(c) {
}

GameObjects:: ~GameObjects(){
  //  cerr<< "Delete " << name() << endl;
};

int GameObjects::dexterity(){
    return 0;
}

int GameObjects:: damagePoints(){
    return 0;
}

string GameObjects::name() const{
    return m_name;
}


int GameObjects:: getCol(){
    return m_col;
}

int GameObjects:: getRow(){
    return m_row;
}

void GameObjects:: setCol(int c){
    m_col = c;
}

void GameObjects:: setRow(int r){
    m_row = r;
}

bool GameObjects:: isScroll(){
    return false;
}

ShortSword::ShortSword(string name, int r, int c):GameObjects(name, r, c){
}

int ShortSword::dexterity(){
    return 0;
}

int ShortSword::damagePoints(){
    return 2;
}

string ShortSword::actionString(){
    return " slashes short sword at the ";
}


LongSword::LongSword(string name, int r, int c):GameObjects(name, r, c){
}

int LongSword::dexterity(){
    return 2;
}

int LongSword::damagePoints(){
    return 4;
}

string LongSword::actionString(){
    return " swings long sword at the ";
}

Mace::Mace(string name, int r, int c):GameObjects(name, r, c){
}

int Mace::dexterity(){
    return 0;
}

int Mace::damagePoints(){
    return 2;
}

string Mace::actionString(){
    return " swings mace at the ";
}

MFS::MFS(string name, int r, int c):GameObjects(name, r, c){
}

int MFS::dexterity(){
    return 3;
}

int MFS::damagePoints(){
    return 2;
}

string MFS::actionString(){
    return " strikes magic fangs at the ";
}

MagicAxes::MagicAxes(string name, int r, int c):GameObjects(name, r, c){
}

int MagicAxes::dexterity(){
    return 5;
}

int MagicAxes::damagePoints(){
    return 5;
}

string MagicAxes::actionString(){
    return " chops magic axe at the ";
}


StairCase:: StairCase(int r, int c):m_row(r), m_col(c){
}

goldenIdol:: goldenIdol(int r, int c): m_row(r), m_col(c){
    
}

Scroll::Scroll(string name, int r, int c):GameObjects(name, r, c){
    
}

string Scroll::actionString(){
    return "";
}


