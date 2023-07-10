#ifndef MONSTER_H
#define MONSTER_H

/**************************************************
	Project: FIT1048 Assignment 4 - Major Project B
	Project Name: Treasure Caverns of Doom
	Author: Zecan Liu
	Purpose: Monster Class Header File
	Date: 20221030
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

using namespace std;

#include "EnumClasses.h"
#include "Item.h"

class Monster
{
private:
    //Similar to the location and item classes, the monster class attributes are designed to suit the game play.
    string name;
    int level, health, attack, defence, damage, itemChance;
    string healthRange, attackRange, defenceRange, damageRange;
    //The range attributes are stored so that the same monster could be "refreshed" - re-generating the attribute values.
    string carryItemName, monsterDescription;
    bool carryItem;
    int monsterId = 0;

    //Similar to item&location classes, the following static attributes are used as class variables.
    static vector<string> refAttributeNameList;
    static vector<string> monsterNameList;
    static vector<Monster> monsterObjectList;
    static int id;

public:
    //Default constructor here if no input are given
    Monster();
    //Overload constructor
    explicit Monster(vector<string> monsterStringList);
    //Default destructor
    ~Monster();

    //Accessor functions
    string getName();
    int getLevel() const;
    int getHealth() const;
    int getAttack() const;
    int getDefence() const;
    int getDamage() const;
    int getItemChance() const;
    string getMonsterDescription();
    virtual string getDetails();
    string getCarryItemName();
    bool getCarryItem() const;

    //The following tow are the virtual functions built for the dragon class exclusively.
    virtual bool getIsBoss() const;
    virtual int getDamageSpFire() const;

    static vector <string> getRefAttributeList();
    static vector<Monster*> getMonsterObjectList();
    static vector<string> getMonsterNameList();

    //Mutator functions
    void setCarryItemName(string itemName);
    void setAttribute(int updateAttribute, MonsterAttribute type);
    void setCarryItem(bool set);

    //Gameplay functions
    void monsterResetAfterCombat();
    virtual void resetSpecialFireDamage();
};


#endif //MONSTER_H

