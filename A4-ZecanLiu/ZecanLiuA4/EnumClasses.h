
#ifndef ENUMCLASSES_H
#define ENUMCLASSES_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Enum Class Header File
    Date: 20221029
**************************************************/

enum class ItemType {
    ITEM,
    WEAPON,
    ARMOUR,
    POTION,
    ARTEFACT
};


enum class ClassType {
    ITEM,
    MONSTER,
    Dragon,
    LOCATION
};

enum class ItemUseType {
    Fixed,
    Fixed_Range,
    Unlimited
};

enum class PlayerAttribute {
    Health,
    Attack,
    Damage,
    Defence,
    Luck,
    NA,
    Multi
};

enum class MonsterAttribute {
    Health,
    Attack,
    Damage,
    Defence
};


enum class EndGameScene {
    userQuitStart,
    userQuit,
    userWin,
    userDie,
    userTrap
};

enum class GameDifficulty {
    Tourist,
    Average,
    Master,
    Hell
};

#endif //ENUMCLASSES_H


