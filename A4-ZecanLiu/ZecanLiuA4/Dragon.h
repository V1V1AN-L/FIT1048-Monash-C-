
#ifndef DRAGON_H
#define DRAGON_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Dragon Class Header File
    Date: 20221029
**************************************************/

#include "Monster.h"

class Dragon : public Monster {
    /*
    Dragon class as an inheritance of the monster class.
    Most of the class definition is the same expect one special attack.
    */
private:
    int damageSpFire;
    string damageSpFireRange;
    bool isBoss;
    //Dragon exclusive attribute.


    static vector<Dragon> dragonObjectList;
    //Same as that of monster objects, the created dragon is here stored in the vector
public:
    //Default constructor
    Dragon();
    //Overload constructor
    Dragon(vector<string> monsterList, vector <string> dragonList);
    //Default destructor
    ~Dragon();

    //Needed accessors
    string getDetails() override;
    int getDamageSpFire() const override;
    bool getIsBoss() const override;
    static vector<Dragon*> getDragonObjectList();

    //Game play function
    void resetSpecialFireDamage() override;

};


#endif //DRAGON_H
