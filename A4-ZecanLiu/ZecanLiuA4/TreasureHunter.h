
#ifndef TREASUREHUNTER_H
#define TREASUREHUNTER_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Treasure Hunter (Abstract) Class Header File
    Date: 20221029
**************************************************/

#include <iostream>
#include <string>
#include <random>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Player.h"
#include "Item.h"
#include "EnumClasses.h"
#include "FunctionCollection.h"
#include "Monster.h"
#include "Location.h"
#include "Dragon.h"


class TreasureHunter {
    /*
    * The Treasure Hunter class is build as a pure abstract class which creates the basic class structures for treasure hunters to be created. 
    * The Treasure Hunters will be the special NPCs in the game that player needs to interact with.
    */
private:
    string name;
    //Simple current setup as of now.
public:
    //Default constructor
    TreasureHunter();
    //Overload constructor
    TreasureHunter(string nameInput);
    //Default destructor
    ~TreasureHunter();
    
    //Assessor function
    string getName();
    virtual void getDetails() = 0;
    
    //Game play functions
    virtual void speak() = 0;
    virtual void interaction(Player* activePlayer) = 0;

};


#endif //TREASUREHUNTER_H
