
#ifndef HEROLIKUI_H
#define HEROLIKUI_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Hero LiKui Class Header File
    Date: 20221030
**************************************************/

#include "TreasureHunter.h"
class HeroLiKui : public TreasureHunter {
    /*
    * This is essentially the same structure as that of the master Roshi class. 
    * Both are inheriting the base class of Treasure Hunter.
    */
public:
    HeroLiKui();
    explicit HeroLiKui(string nameInput);
    ~HeroLiKui();

    void getDetails() override;
    void interaction(Player* activePlayer) override;
    void speak() override;
};


#endif //HEROLIKUI_H
