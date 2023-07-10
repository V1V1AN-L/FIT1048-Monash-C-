
#ifndef MASTERROSHI_H
#define MASTERROSHI_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Master Roshi Class Header File
    Date: 20221030
**************************************************/

#include "TreasureHunter.h"
class MasterRoshi : public TreasureHunter {
public:
    //Default constructor
    MasterRoshi();
    //Overload constructor
    explicit MasterRoshi(string nameInput);
    //Default destructor
    ~MasterRoshi();

    //Override functions as to the base class
    void getDetails() override;
    void interaction(Player* activePlayer) override;
    void speak() override;
};


#endif //MASTERROSHI_H
