
#ifndef PLAYER_H
#define PLAYER_H

/**************************************************
	Project: FIT1048 Assignment 4 - Major Project B
	Project Name: Treasure Caverns of Doom
	Author: Zecan Liu
	Purpose: Player Class Header File
	Date: 20221029
**************************************************/

#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <utility>
#include <cstring>

#include "Item.h"
#include "EnumClasses.h"
#include "FunctionCollection.h"

using namespace std;


class Player
{
private:
    string name;
    float health, attack, defence, damage, luck;
    bool bagFull;
    bool specialAttackKHH;
    /*
     * Inventory bag as a vector of Item object pointers.
     * Effectively reducing the copying of same variable across different uses.
     */
    vector <Item*> inventoryBag;
    vector <int> inventoryBagUseLimit;


    void itemPickUpCheckLoop(vector<string> myVector, Item* tempItem);

public:
    //All functions are made public at the moment.

    //Default constructor here if no input are given
    Player();
    //Overload constructor
    explicit Player(string name);
    //Destructor
    ~Player();

    //Accessor functions
    string getName();
    int getHealth() const;
    int getAttack() const;
    int getDefence() const;
    int getDamage() const;
    int getLuck() const;

    bool getBagFull() const;
    bool getSpecialAttack() const;
    string getDetails();
    vector <Item*> getInventoryBag();
    vector <int> getInventoryBagUseLimit();

    //Mutator functions
    void setAttribute(int intUpdateAmount, PlayerAttribute type);
    void setInventoryBagUseLimit(int location, int& updateAmount);
    void setBagFull(bool check);
    void setSpecialAttack(bool check);

    //Game play functions
    void pickItemUp(const string& itemName);
    void useItemConsumable();
    string getBagInformation();
    vector <string> getBagItemNameList(const string& category);
    void dropItem();
    string getUserSelectionFromBag(const string& preFilledQuestion, const string& itemType);
    int collectedArtefactCounter();

protected:
};

#endif //PLAYER_H

