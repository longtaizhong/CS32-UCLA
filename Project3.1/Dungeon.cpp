//
//  Dungeon.cpp
//  Project3
//
//  Created by Ryan Zhong  on 5/11/20.
//  Copyright © 2020 Ryan Zhong . All rights reserved.
//

#include "Dungeon.h"
#include "globals.h"


#include <string>
#include <iostream>
#include <stdio.h>


using namespace std;


Dungeon::Dungeon(): m_player(nullptr), m_level(0), pickUp(false), m_StairCase(nullptr), m_GoldenIdol(nullptr){
    m_run = true;
    dungeon_run = true;
}

//Dungeon Destructor
Dungeon::~Dungeon(){
    delete m_player;
    delete m_StairCase;
    delete m_GoldenIdol;
    for(int i = 0; i<m_monsters.size(); i++){
        delete m_monsters.at(i);
    }
    for(int i = 0; i<glist.size(); i++){
        delete glist.at(i);
    }
    for(int i = 1; i<inventory.size(); i++){
        delete inventory.at(i);
    }
    inventory.clear();
    glist.clear();
    m_monsters.clear();
}

//GENERATE DUNGEON, FIRST, make an dungeon with #s and whites and call it baseGrid
void Dungeon::generate(){
    //GENERATE 18 by 70 filled with WALLS
   /* GameObjects* w = new ShortSword("short sword", 5, 5);
    inventory.push_back(w);*/
    
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            m_baseGrid[i][j] = '#';
        }
    }
    cout<<endl;
    
    //BOX 1, LEFT SIDE
    
    int topLRow = randInt(3, 4);
    int topLCol = randInt(3, 7);
    
    int randHeight = randInt(4, 7);
    int randWidth = randInt(6, 15);
    
    int midPointR = topLRow+randHeight/2;
    int midPointC = topLCol+randWidth;
    
    int topLRow5 = randInt(topLRow+randHeight+1, topLRow+randHeight+2);
    int topLCol5 = randInt(3, 7);
    
    int randHeight5 = randInt(3, 4);
    int randWidth5 = randInt(6, 15);
    int midPointR5 = topLRow5;
    int midPointC5 = topLCol5+randWidth5/2;
    
    
    excavate(topLRow5, topLCol5, randHeight5, randWidth5);
    
    
    
    /*
    int topLRow = randInt(2, 6);
    int topLCol = randInt(3, 7);
    
    int randHeight = randInt(10, 10);
    int randWidth = randInt(40, 40);
    */
    excavate(topLRow, topLCol, randHeight, randWidth);
    
    //Display the Grid
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            cerr<<m_baseGrid[i][j];
            //cout<<m_baseGrid[i][j];
        }
        cerr<<endl;
    }
    //BOX2
    int topLRow2 = randInt(2, 6);
    int topLCol2 = randInt(topLCol+randWidth+3, topLCol+randWidth+6);
    
    int randHeight2 = randInt(6, 9);
    int randWidth2 = randInt(6, 15);
    
    int midPointR2 = topLRow2+randHeight2/2;
    int midPointC2 = topLCol2+randWidth2;
    excavate(topLRow2, topLCol2, randHeight2, randWidth2);
    
    
    //BOX3
    int topLRow3 = randInt(3, 5);
    int topLCol3 = randInt(topLCol2+randWidth2+3, topLCol2+randWidth2+6);
    
    int randHeight3 = randInt(4, 5);
    int randWidth3 = randInt(10, 15);
    excavate(topLRow3, topLCol3, randHeight3, randWidth3);
    
    //BOX4
    int topLRow4 = randInt(topLRow3+randHeight3+1, topLRow3+randHeight3+3);
    int topLCol4 = randInt(topLCol2+randWidth2+1, topLCol2+randWidth2+6);
    
    int randHeight4 = randInt(3, 4);
    int randWidth4 = randInt(6, 15);
    
    int midPointR4 = topLRow4;
    int midPointC4 = topLCol4 + randWidth4/2;
    excavate(topLRow4, topLCol4, randHeight4, randWidth4);
    
    //Make corridors
    makeCorridor(midPointR, midPointC);
    makeCorridor(midPointR2-1, midPointC2);
    makeCorridorUp(midPointR4, midPointC4);
    makeCorridorUp(midPointR5, midPointC5);
    
    
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            m_maze[i][j] = m_baseGrid[i][j];
        }
    }
    //if Player has already been made, then add it here
    bool placed = false;
    while(!placed){
        int r = randInt(2, ROWS-2);
        int c = randInt(2, COLS-2);
        if(getBaseGrid(r,c) == ' ' && getGrid(r, c) == ' ' && movable(r, c)){
            addPlayer(r,c);
            cerr<<"Player added at (" << r << " , " << c << ")" << endl;
            placed = true;
            
        }
    }
    //ADD the first 3 items on the level
    int numStartObjects = randInt(2,3);
    for(int i = 0; i<numStartObjects; i++){
        bool placed = false;
        while(!placed){
            int r = randInt(2, ROWS-2);
            int c = randInt(2, COLS-2);
            if(getBaseGrid(r,c) == ' ' && getGrid(r,c) == ' '){
                int initialDrop = randInt(0,6);
                GameObjects* w = nullptr;
                switch(initialDrop){
                    case 0:{
                        w = new ShortSword("short sword", r, c );
                        break;
                    }
                    case 1:{
                        w = new LongSword("long sword", r, c );
                        break;
                    }
                    case 2:{
                        w =  new Mace("mace", r, c );
                        break;
                    }
                    case 3:
                        w = new Scroll("scroll of improve armor", r, c);
                        break;
                    case 4:
                        w = new Scroll("scroll of raise strength", r, c);
                        break;
                    case 5:
                        w = new Scroll("scroll of enhance health", r, c);
                        break;
                    case 6:
                        w = new Scroll("scroll of enhance dexterity", r, c);
                        break;
                    
                }
                glist.push_back(w);
                placed = true;
                if (w != nullptr){
              //      cerr<< w->name() << " is  added at (" << r << " , " << c << ")" << endl;
                }
            }
        }
    }
    //ADD staircase
    addMonsters();
    if(m_level < 4){
        generateStairCase();
    }else{
        generateGoldenIdol();
    }
    
    
 
}
//Generate Staircase if the level is not 5

void Dungeon:: generateStairCase(){
    
        bool placed = false;
        while(!placed){
            int r = randInt(2, ROWS-2);
            int c = randInt(2, COLS-2);
            if(getBaseGrid(r,c) == ' ' && getGrid(r,c) == ' ' && isItemAt(r, c)){
                m_StairCase = new StairCase(r, c);
                cerr<< "staircase generated at " << r << ","<< c << endl;
                placed = true;
            }
        }
}
//Generate goldenIdol
void Dungeon:: generateGoldenIdol(){
    bool placed = false;
    while(!placed){
        int r = randInt(2, ROWS-2);
        int c = randInt(2, COLS-2);
        if(getBaseGrid(r,c) == ' ' && getGrid(r,c) == ' ' && isItemAt(r,c) && !occupied(r,c)){
            m_GoldenIdol = new goldenIdol(r, c);
            cerr<< "golden idol  generated at " << r << ","<< c << endl;
            placed = true;
        }
    }
}

//Display the Dungeon. All the positions of units that need to be displayed will be reflected on the display grid here
void Dungeon::display(){
    //generate();
    //DISPLAY staircase, player and gameobjects inside
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            m_maze[i][j] = m_baseGrid[i][j];
        }
    }
    if(m_StairCase != nullptr){
        m_maze[m_StairCase->getRow()][m_StairCase->getCol()] = '>';
    }
    if(m_GoldenIdol != nullptr){
        m_maze[m_GoldenIdol->getRow()][m_GoldenIdol->getCol()] = '&';
    }
    cout<< "Glist size is " << glist.size()<< endl;
    //Generate the weapons on the ground, stored in vector glist
    for(int i = 0; i<glist.size(); i++){
        GameObjects* a = glist.at(i);
        if(a->isScroll() == false){
            m_maze[a->getRow()][ a->getCol()] = ')';
        }else{
            m_maze[a->getRow()][a->getCol()] = '?';
        }
        
    }
    
    //Goes through vector of monsters and display their positions on the maze
    for(int i = 0; i<m_monsters.size(); i++){
        Actor* a = m_monsters.at(i);
        m_maze[a->getRowPos()][a->getColPos()] = a->getSymbol();
    }
        
    //Display the player
    if(m_player != nullptr){
        m_maze[m_player->getRowPos()][m_player->getColPos()] = '@';
    }
    
    clearScreen();
    
    //Display the Grid
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            cout<<m_maze[i][j];
            //cout<<m_baseGrid[i][j];
        }
        cout<<endl;
    }
    
    //Display the Stat messages
    cout<< "Dungeon Level: " << m_level << ", Hit points: " << m_player->getHealth() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dexterity()<<endl;
   
}

//Make selected char an empty char
void Dungeon::excavate(int topLeftRow, int topLeftCol, int height, int width ){
    for(int m = topLeftRow; m<topLeftRow+height; m++){
        for(int n = topLeftCol; n<topLeftCol + width; n++){
            m_baseGrid[m][n] = ' ';
        }
    }
}

//Helper function: Set the display grid to character
void Dungeon::setGrid(int row, int col, char c){
    m_maze[row][col] = c;
}

//Set the base grid to some character
void Dungeon::setBaseGrid(int row, int col, char c){
    m_baseGrid[row][col] = c;
}


//Add player to display grid and add his item to inventory
bool Dungeon::addPlayer(int row, int col){
    if (m_player != nullptr){
        return false;
    }
    m_player = new Player( row, col, "Player", '@');
    GameObjects* w = m_player->getWeapon();
    inventory.push_back(w);
    return true;
}

//Add monsters to floor randomly
void Dungeon::addMonsters(){
    int numMonsters = randInt(2, 5*(m_level+1)+1);
    //int numMonsters = 3;
    
    for(int i = 0; i<numMonsters; i++){
        bool placed = false;
        while(!placed){
            int r = randInt(2, ROWS-2);
            int c = randInt(2, COLS-2);
            if(getBaseGrid(r,c) == ' ' && getGrid(r,c) == ' ' && movable(r,c) && r != m_player->getRowPos() && c!= m_player->getColPos()){
                int mons = 0;
                
                if(m_level == 0){
                    mons = randInt(0, 1);
                  //  mons = randInt(0,0);
                }
                if(m_level == 1){
                    mons = randInt(0,1);
                }
                if(m_level == 2){
                    mons = randInt(0,2);
                }
                if(m_level >= 3){
                    mons = randInt(0,3);
                }
                
                Actor* a = nullptr;
                switch(mons){
                    case 1:{
                        a = new SnakeWoman( r, c,  "SnakeWoman", 'S');
                     //   cerr<<"SnakeWoman is at " << r << " , " << c << endl;
                     //   cerr<<"with DEX: " << a->dexterity()<< endl;
                        placed = true;
                        break;
                    }
                    case 2:{
                        a = new BogeyMan( r, c,  "BogeyMan", 'B');
                        cerr<<"BogeyMan is at " << r << " , " << c << endl;
                        placed = true;
                        break;
                    }
                    case 3:{
                        a = new Dragon( r, c,  "Dragon", 'D');
                        cerr<<"Dragon is at " << r << " , " << c << endl;
                        placed = true;
                        break;
                    }
                    case 0:{
                        a = new Goblin( r, c, "Goblin", 'G');
                        cerr<<"Goblin is at " << r << " , " << c << endl;
                        placed = true;
                        break;
                    }
                }
                m_monsters.push_back(a);
            }
        }
    }
}


//Move the player based on the keyboard effect
void Dungeon::moveCharacters(char c){
    string msg = "";
    int index;
    if(!m_player->isSleep()){
        switch(c){
            case ARROW_UP:
            //    if(movable(m_player->getRowPos()-1, m_player->getColPos())){
                if(indexOfMonsAt(m_player->getRowPos()-1, m_player->getColPos(), index)){
                    attack(m_player, m_monsters.at(index), msg);
                    m_msgs.push_back(msg);
                }else if(movable(m_player->getRowPos()-1, m_player->getColPos())){
                    m_player->setRowPos(m_player->getRowPos()-1);
                }
                break;
            case ARROW_DOWN:
                if(indexOfMonsAt(m_player->getRowPos()+1, m_player->getColPos(), index)){
                    attack(m_player, m_monsters.at(index), msg);
                    m_msgs.push_back(msg);
                }else  if(movable(m_player->getRowPos()+1, m_player->getColPos())){
                    m_player->setRowPos(m_player->getRowPos()+1);
                }
              
                break;
            case ARROW_RIGHT:
                if(indexOfMonsAt(m_player->getRowPos(), m_player->getColPos()+1, index)){
                    attack(m_player, m_monsters.at(index), msg);
                    m_msgs.push_back(msg);
                }else if(movable(m_player->getRowPos(), m_player->getColPos()+1)){
                    m_player->setColPos(m_player->getColPos()+1);
                }

                cout<<msg<<endl;
                break;
            case ARROW_LEFT:
                if(indexOfMonsAt(m_player->getRowPos(), m_player->getColPos()-1, index)){
                    attack(m_player, m_monsters.at(index), msg);
                    m_msgs.push_back(msg);
                }else if(movable(m_player->getRowPos(), m_player->getColPos()-1)){
                    m_player->setColPos(m_player->getColPos()-1);
                }

                cout<<msg<<endl;
                break;

        }
    }else{
        cerr<< "player is sleeping for " << m_player->getSleepTurns() << " more turns"<< endl;
        if(m_player->getSleepTurns() == 0){
            m_player->setSleep(false, 0);
           // cerr<< monster->getName() << " woke up " << endl;
        }
        m_player->setSleepTurns(m_player->getSleepTurns() - 1);
    }
}

//Go through each monster in monster vector and move them
void Dungeon::moveMonsters(){
    string msg ="";
    for(int i = 0; i<m_monsters.size(); i++){
        if(m_monsters.at(i)->getName() == "Goblin"){
            //
            if(!nextToPlayer(m_monsters.at(i))){
                int stepSize = goblinStep(m_monsters.at(i), m_monsters.at(i)->getRowPos(), m_monsters.at(i)->getColPos());
                if(stepSize <= 15 && stepSize != 0){
                    if(m_goblinDir.front() == "right"){
                        if(movable(m_monsters.at(i)->getRowPos(),m_monsters.at(i)->getColPos()+1 ) && !occupied(m_monsters.at(i)->getRowPos(),m_monsters.at(i)->getColPos()+1)){
                            m_monsters.at(i)->setColPos(m_monsters.at(i)->getColPos()+1);
                        }
                    }
                    if(m_goblinDir.front() == "left"){
                        if(movable(m_monsters.at(i)->getRowPos(),m_monsters.at(i)->getColPos()-1 ) && !occupied(m_monsters.at(i)->getRowPos(),m_monsters.at(i)->getColPos()-1)){
                             m_monsters.at(i)->setColPos(m_monsters.at(i)->getColPos()-1);
                        }
                    }
                    if(m_goblinDir.front() == "up"){
                        if(movable(m_monsters.at(i)->getRowPos()-1,m_monsters.at(i)->getColPos()) && !occupied(m_monsters.at(i)->getRowPos()-1,m_monsters.at(i)->getColPos())){
                            m_monsters.at(i)->setRowPos(m_monsters.at(i)->getRowPos()-1);
                        }
                    }
                    if(m_goblinDir.front() == "down"){
                         if(movable(m_monsters.at(i)->getRowPos()+1,m_monsters.at(i)->getColPos() ) && !occupied(m_monsters.at(i)->getRowPos()+1,m_monsters.at(i)->getColPos())){
                             m_monsters.at(i)->setRowPos(m_monsters.at(i)->getRowPos()+1);
                         }
                    }
                   
                    m_goblinDir.erase(m_goblinDir.begin());
                }
                m_goblinDir.clear();
            }else if(nextToPlayer(m_monsters.at(i))){
                attack(m_monsters.at(i), m_player, msg);
                m_msgs.push_back(msg);
                
            }
            
        }else{
        moveMonst(m_monsters.at(i));
        }
        
    }
    for(int i = 0; i<m_monsters.size(); i++){
        cerr<< m_monsters.at(i)->getRowPos() << " , " << m_monsters.at(i)->getColPos() << endl;
    }
}

//When the player is on top of gameobject and pressing g, player picks it up and adds it to inventory
void Dungeon::pickUpObjects(){
    GameObjects* w = nullptr;
    int indexGlist;
    
    if(canPickUp(w, indexGlist)){
        if(inventory.size() == 26){
            cout << "Your knapsack is full; you can't pick that up. " << endl;
        }else{
            inventory.push_back(w);
            if(!w->isScroll()){
                cout<< "You pick up " + w->name()<<endl;
            }else{
                cout << "You pick up a scroll called " + w->name() << endl;
            }
            //delete *(glist.begin()+indexGlist);
            glist.erase(glist.begin()+indexGlist);
          
            
        }
    }
    if(m_level == 4){
        if(m_GoldenIdol->getRow() == m_player->getRowPos() && m_GoldenIdol->getCol() == m_player->getColPos()){
            cout<< "You pick up the golden idol" << endl;
            cout<< "Congratulations! You won!" << endl;
            m_run = false;
        }
    }
    
}

//Tells monsters and player if they can go on the grid
bool Dungeon::movable(int r, int c){
    if(getGrid(r, c) == '#'){
        return false;
    }
    if(getGrid(r, c) == 'S'){
        return false;
    }
    if(getGrid(r, c) == 'G'){
        return false;
    }
    if(getGrid(r, c) == 'D'){
        return false;
    }
    for(int i = 0; i<m_monsters.size(); i++){
        if(m_monsters.at(i)->getRowPos() == r && m_monsters.at(i)->getColPos() == c){
            return false;
        }
    }
    return true;
}

//If theres an object there and if it can be picked up
bool Dungeon::canPickUp(GameObjects* &w, int &indexGlist){
    if(m_player != nullptr){
        for(int i = 0; i<glist.size(); i++){
            if(glist.at(i) != nullptr && glist.at(i)->getRow() == m_player->getRowPos() &&
               glist.at(i)->getCol() == m_player->getColPos()){
                w = glist.at(i);
                indexGlist = i;
                return true;
            }
        }
    }
    return false;
}

//WHen player presses w, show inventory and make them yield weapon if they press the corresponding letter
void Dungeon::yieldWeaponOrScroll(char a){
    string msg = "";
    clearScreen();
    char ch = 'a';
    cout<< "Inventory:" <<endl;
    for(int i = 0; i<inventory.size(); i++){
        cout<< char(ch+i) << ". " << inventory.at(i)->name() << endl;
    }
    char chooseWeapon = getCharacter();
    int inventoryIndex = chooseWeapon-97;
    if(inventoryIndex < inventory.size()){
        if(a == 'w'){
            if(!inventory.at(inventoryIndex)->isScroll()){
                m_player->setWeapon(inventory.at(inventoryIndex));
                msg = "You are wielding " + inventory.at(inventoryIndex)->name();
            }else{
                msg = "You can't wield " + inventory.at(inventoryIndex)->name();
            }
        }else if(a== 'r'){
            if(inventory.at(inventoryIndex)->isScroll()){
                string nameScroll = inventory.at(inventoryIndex)->name();
                if(nameScroll == "scroll of improve armor"){
                    int extraArmor = randInt(1,3);
                    m_player->setArmor(m_player->armor()+extraArmor);
                    msg = "You read a " + nameScroll + ". Your armor glows blue.";
                }
                if(nameScroll == "scroll of enhance dexterity"){
                    m_player->setDexterity(m_player->dexterity()+ 1);
                    msg = "You read a " + nameScroll + ". You feel like less of a klutz.";
                }
                if(nameScroll == "scroll of raise strength"){
                    int extraSTR = randInt(1,3);
                    m_player->setStrength(m_player->strength()+ extraSTR);
                    msg = "You read a " + nameScroll + ". Your muscles bulge.";
                }
                if(nameScroll == "scroll of enhance health"){
                    int extraHP = randInt(3,8);
                    m_player->setMaxHealth(m_player->getHealth() + extraHP);
                    msg = "You read a " + nameScroll + ". You feel your heart beating stronger.";
                }
                if(nameScroll == "scroll of teleportation"){
                    bool placed = false;
                    while(!placed){
                        int r = randInt(2, ROWS-2);
                        int c = randInt(2, COLS-2);
                        if(getBaseGrid(r,c) == ' ' && getGrid(r, c) == ' ' && movable(r, c)){
                            m_player->setRowPos(r);
                            m_player->setColPos(c);
                            cerr<<"Player teleported to (" << r << " , " << c << ")" << endl;
                            placed = true;
                        }
                    }
                    msg = "You read a " + nameScroll + ". You feel your body wrenched in space and time.";
                }
                delete *(inventory.begin()+inventoryIndex);
                inventory.erase(inventory.begin()+inventoryIndex);
                cerr<< "New inventory size is " << inventory.size() << endl;
            }else{
                msg = "You can't read a " + inventory.at(inventoryIndex)->name();
            }
        }
    }
    clearScreen();
    display();
    cout<<msg<<endl;
}




//Tells us the index of monster in the monster vector
bool Dungeon::indexOfMonsAt(int r, int c, int &index){
    for(int i = 0; i<m_monsters.size(); i++){
        if(m_monsters.at(i)->getRowPos() == r && m_monsters.at(i)->getColPos() == c){
            index = i;
            return true;
        }
    }
    return false;
}

//Take two actors, and make one attack the otehr, set the messages
void Dungeon::attack(Actor* attacker, Actor* defender, string &msg){
    
    //Calculate attackerpoints, defenderpoints and damage points based on the formula given
    int attackerPoints = attacker->dexterity() + attacker->getWeapon()->dexterity();
    int defenderPoints = defender->dexterity() + defender->armor();
    int damagePoints = randInt(0, attacker->strength() + attacker->getWeapon()->damagePoints() - 1);
    
    
    if(randInt(1, attackerPoints) >= randInt(1, defenderPoints)){
        //ATTACKER HAS HIT DEFENDER
        msg = "the " + attacker->getName() + attacker->getWeapon()->actionString() + defender->getName() + " and hits.";
        defender->setHealth(defender->getHealth()-damagePoints);
        
        //IF THE WEAPON IS MAGIC FANG OF SLEEP, Make them sleep
        if(attacker->getWeapon()->name() == "magic fangs of sleep"){
            setToSleep(defender);
            if(defender->isSleep()){
                msg = "the " + attacker->getName() + attacker->getWeapon()->actionString() + defender->getName() + " and hits, putting the " + defender->getName() +  " to sleep.";
            }else{
                 msg = "the " + attacker->getName() + attacker->getWeapon()->actionString() + defender->getName() + " and hits.";
            }
        }
        
        //IF the attacker defeats the defender, possibly drop items on the ground and add it to the item vector so it gets reflected on grid, remove that defender from the list of monsters
        if(defender->getHealth() <= 0){
            msg = "the " + attacker->getName() + attacker->getWeapon()->actionString() + defender->getName() + " dealing a final blow.";
            if(defender->getName() == "Player"){
                dungeon_run = false;
            }
           int index;
            if(indexOfMonsAt(defender->getRowPos(), defender->getColPos(), index)){
                if(defender->dropItem()){
                    GameObjects* w = defender->getDropItem();
                    
                    w->setRow(defender->getRowPos());
                    w->setCol(defender->getColPos());
                    
                    if(getGrid(defender->getRowPos(), defender->getColPos() == ' ')){
                        cerr<< "item dropped: " << w->name()<< endl;
                        glist.push_back(w);
                    }
                }
                //delete w;
         //       delete m_monsters.at(index);
         //       delete *(m_monsters.begin()+index);
                vector<Actor*>::iterator i = m_monsters.begin()+index;
                //delete(*(i));
                m_monsters.erase(i);
            }
        }
        //When attack misses
    }else{
        msg = "the "+ attacker->getName() + attacker->getWeapon() -> actionString() + defender->getName() + " and misses.";
    }
    
    
}
//Take the letters and apply in switch statements

//Main function that takes in command from Game.cpp and decide the way
void Dungeon::playGame(Game* g, char command){
    
    //Before command executes, heal the player by 1
    if(m_player->getHealth() < m_player->maxHealth()){
        int heal = randInt(1,10);
        if(heal == 1){
            m_player->setHealth(m_player->getHealth() + 1);
        }
    }
    switch(command){
        case 'q':
            g->setRunFalse();
            break;
        case 'w':
        case 'r':
            yieldWeaponOrScroll(command);
            break;
        case 'g':
            pickUpObjects();
            if(!m_run){
                g->setRunFalse();
            }
            break;
        case '>':
            descend();
            break;
        case 'i':
            displayInventory();
            break;
        case 'c':
            cheat();
            break;
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
          
            moveCharacters(command);
            moveMonsters();
            if(!dungeon_run){
                g->setRunFalse();
                clearScreen();
                display();
                printMsg();
            }else{
            clearScreen();
            display();
            printMsg();
            }
            break;
        default:
            moveMonsters();
            if(!dungeon_run){
                g->setRunFalse();
                clearScreen();
                display();
                printMsg();
            }else{
            clearScreen();
            display();
            printMsg();
            }
    }
}

//Display inventory, pressing any letter will make it switch back to the grid
void Dungeon::displayInventory(){
    string msg = "";
    clearScreen();
    char ch = 'a';
    cout<< "Inventory:" <<endl;
    for(int i = 0; i<inventory.size(); i++){
        cout<< char(ch+i) << ". " << inventory.at(i)->name() << endl;
    }
    getCharacter();
    clearScreen();
    display();
}

//Move mnosters and attack the player if its next to it
void Dungeon::moveMonst(Actor* monster){
    string msg = "";
    if(!monster->isSleep()){
        if(abs(monster->getRowPos()-m_player->getRowPos()) <= monster->smellDistance() &&
           abs(monster->getColPos()-m_player->getColPos()) <= monster->smellDistance()){
       //     cerr<<"smelled player"<<endl;
            if(!nextToPlayer(monster)){
                moveCloser(monster);
            }else{
                attack(monster, m_player, msg);
                /*
                if(monster->getWeapon()->name() == "magic fangs of sleep"){
                    cerr<<"SET PLAYER TO SLEEP" << endl;
                    setToSleep(m_player);
                }*/
                m_msgs.push_back(msg);
            }
        }else{
         //   cerr<<"DRAGON IS NEXT TO PLAYER" << endl;
            //WHEN PLAYER IS NEXT TO DRAGON
            if(nextToPlayer(monster)){
                cerr<<"DRAGON IS NEXT TO PLAYER" << endl;
                attack(monster, m_player, msg);
                m_msgs.push_back(msg);
            }
        }
        
    }else{
        //If the monster is asleep, make the sleepturn decrease by one.
        cerr<< monster->getName() << " is sleeping " << endl;
        cerr<< "its sleeping for " << monster->getSleepTurns() << " more turns " << endl;
        
        if(monster->getSleepTurns() == 0){
            monster->setSleep(false, 0);
            cerr<< monster->getName() << " woke up " << endl;
        }
        monster->setSleepTurns(monster->getSleepTurns() - 1);
    }
}

//Tells if a monster is next to the player
bool Dungeon::nextToPlayer (Actor* monster){
    if(monster->getRowPos() == m_player->getRowPos() && abs(monster->getColPos()-m_player->getColPos()) ==1){
 //       cerr<<"next to player"<<endl;
        return true;
    }
    if(monster->getColPos() == m_player->getColPos() && abs(monster->getRowPos()-m_player->getRowPos()) ==1){
//          cerr<<"next to player"<<endl;
        return true;
    }
    return false;
}


//If SnakeWoman or Bogeyman smell the player, find the direction of where it should and move there
bool Dungeon::moveCloser(Actor* monster){
    if(abs(monster->getRowPos()+1 - m_player->getRowPos()) < abs(monster->getRowPos() -m_player->getRowPos())){
     //   cerr<<"move down" << endl;
        if(movable(monster->getRowPos()+1, monster->getColPos())){
            monster->setRowPos(monster->getRowPos()+1);
            return true;
        }
    }
    if(abs(monster->getRowPos()-1 - m_player->getRowPos()) < abs(monster->getRowPos() -m_player->getRowPos())){
        if(movable(monster->getRowPos()-1, monster->getColPos())){
      //      cerr<<"move up" << endl;
            monster->setRowPos(monster->getRowPos()-1);
            return true;
        }
    }
    if(abs(monster->getColPos()+1 - m_player->getColPos()) < abs(monster->getColPos() -m_player->getColPos())){
        if(movable(monster->getRowPos(), monster->getColPos()+1)){
      //      cerr<<"move right" << endl;
            monster->setColPos(monster->getColPos()+1);
            return true;
        }
    }
    if(abs(monster->getColPos()-1 - m_player->getColPos()) < abs(monster->getColPos() -m_player->getColPos())){
   //     cerr<<"move left"<<endl;
        if(movable(monster->getRowPos(), monster->getColPos()-1)){
            monster->setColPos(monster->getColPos()-1);
            return true;
        }
    }
    return false;
}

//print all the messages and delete them
void Dungeon:: printMsg(){
    for(int i = 0; i<m_msgs.size(); i++){
        cout<<m_msgs.at(i)<<endl;
    }
    m_msgs.clear();
}

//When player is on staircase and presses >, descend to the level below
void Dungeon::descend(){
    if(m_player->getRowPos() == m_StairCase->getRow() && m_player->getColPos() == m_StairCase->getCol()){
        m_level++;
        for(int i = 0; i<m_monsters.size(); i++){
            delete m_monsters.at(i);
        }
        for(int i = 0; i<glist.size(); i++){
            delete glist.at(i);
        }
        glist.clear();
        m_monsters.clear();
        
        
        bool placed = false;
        m_StairCase = nullptr;
        generate();
        while(!placed){
            int r = randInt(2, ROWS-2);
            int c = randInt(2, COLS-2);
            if(getBaseGrid(r,c) == ' ' && getGrid(r, c) == ' ' && movable(r, c)){
                m_player->setRowPos(r);
                m_player->setColPos(c);
                cerr<<"Player teleported to (" << r << " , " << c << ")" << endl;
                placed = true;
                
            }
        }
        
        
        display();
    }
}

//Set the defender to asleep 
void Dungeon::setToSleep(Actor* defender){
    int makeSleep = randInt(1,5);
    int sleepFor = randInt(2,6);
    if(makeSleep == 1){
        if(defender->isSleep()){
            int newSleepTime = max(defender->getSleepTurns(), sleepFor);
            defender->setSleep(true, newSleepTime);
        }else{
        defender->setSleep(true, sleepFor);
        }
    }
}

//Recursive goblin Function
int Dungeon::goblinStep(Actor* goblin, int sr, int sc){
    
    if(sr == m_player->getRowPos() && abs(sc-m_player->getColPos()) ==1){
     //   cerr<< m_goblinDir.size()<< endl;
    //    cerr<< "MOVE GOBLIN"<< endl;
        return 0;
    }
    if(sc == m_player->getColPos() && abs(sr-m_player->getRowPos()) ==1){
        //          cerr<<"next to player"<<endl;
   //     cerr<< "MOVE GOBLIN"<< endl;
        return 0;
    }
    goblinGrid[sr][sc] = 'A';
    
    if(abs(sc-1 - m_player->getColPos()) < abs(sc -m_player->getColPos())){
        if(movable(sr, sc-1) && !occupied(sr, sc-1)){
            m_goblinDir.push_back("left");
            return goblinStep(goblin, sr, sc-1)+1;
        }
        
    }
    if(abs(sc+1 - m_player->getColPos()) < abs(sc -m_player->getColPos())){
        if(movable(sr, sc+1) &&  !occupied(sr, sc+1)){
            m_goblinDir.push_back("right");
            return goblinStep(goblin, sr, sc+1)+1;
        }
    }
    if(abs(sr+1 - m_player->getRowPos()) < abs(sr - m_player->getRowPos())){
        if(movable(sr+1, sc) &&  !occupied(sr+1, sc)){
            m_goblinDir.push_back("down");
            return goblinStep(goblin, sr+1, sc)+1;
        }
    }
    if(abs(sr-1 - m_player->getRowPos()) < abs(sr - m_player->getRowPos())){
        if(movable(sr-1, sc) &&  !occupied(sr-1, sc)){
            m_goblinDir.push_back("up");
            return goblinStep(goblin, sr-1, sc)+1;
        }
    }
    return 0;
    
    
    
}

bool Dungeon:: occupied(int r, int c){
    for(int i = 0; i<m_monsters.size(); i++){
        if(m_monsters.at(i)->getRowPos() == r && m_monsters.at(i)->getColPos() == c){
            return true;
        }
    }/*
    for(int i = 0; i<glist.size(); i++){
        if(glist.at(i)->getRow() == r && glist.at(i)->getCol() == c){
            return true;
        }
    }*/
    return false;
}

void Dungeon:: cheat(){
    m_player->setStrength(9);
    m_player->setMaxHealth(50);
    m_player->setHealth(50);
    clearScreen();
    display();
}

bool Dungeon::isItemAt(int r, int c){
    
    for(int i = 0; i<glist.size(); i++){
        if(glist.at(i)->getRow() == r && glist.at(i)->getCol() == c){
            return false;
        }
    }
    return true;
    
}

void Dungeon::makeCorridor(int midPointR, int midPointC){
  
    //int i = 0;
    
    for(int i = 0; i<15; i++){
        if(getBaseGrid(midPointR, midPointC+i) == ' '){
            break;
        }
        setBaseGrid(midPointR, midPointC+i, ' ');
    }
}

void Dungeon::makeCorridorUp(int midPointR, int midPointC){

    //int i = 0;
    
    for(int i = 1; i<10; i++){
        if(getBaseGrid(midPointR-i, midPointC) == ' '){
            break;
        }
        setBaseGrid(midPointR-i, midPointC, ' ');
    }
}
