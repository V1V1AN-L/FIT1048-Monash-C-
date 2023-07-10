
/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Monster Class Definition File
    Date: 20221029
**************************************************/

#include "Monster.h"
#include <utility>
#include "FunctionCollection.h"

//Constructor
Monster::Monster() {
    /*
     This is default constructor with default attributes to 0 and no name assigned.
     This is not intended to be used anywhere in the code.
     */
    name = "Testing Monster Only";
    level = 0;
    health = 0;
    attack = 0;
    defence = 0;
    damage = 0;
    itemChance = 0;
    carryItemName = "No Item For This Guy";
    id++;
    monsterId = id;
    monsterDescription = "This is not a real monster";
    healthRange = attackRange = damageRange = defenceRange = "There is no range";
    carryItem = false;
}
//Overload Constructor
Monster::Monster(vector<std::string> monsterStringList) {
    /*
     * The import of Monster objects are made through a .txt file where information/markers that helps identify and define
     * attributes are defined and separated by ";" as delimiter. Following the order as:
     * Monster name: Word;
     * Monster level: Number;
     * Monster health range: Mixed: h1&h2 - h1 and h2 correspond to the upper and lower limit of the health range;
     * Monster attack range: Mixed: a1&a2 - a1 and a2 correspond to the upper and lower limit of the attack range;
     * Monster defence range: Mixed: de1&de2 - de1 and de2 correspond to the upper and lower limit of the defence range;
     * Monster holding item chance: Number;
     * Monster description: Words;
     */


    id++;
    monsterId = id;
    //load the first and second elements into name and level
    string tempName = monsterStringList[0];
    name = tempName;
    level = stoi(monsterStringList[1]);

    //for each attribute both the definition range and a random value are stored
    string tempHealthRange = monsterStringList[2];
    health = level * randomIntFromRange(tempHealthRange);
    healthRange = tempHealthRange;

    string tempAttackRange = monsterStringList[3];
    attack = level + randomIntFromRange(tempAttackRange);
    attackRange = tempAttackRange;

    string tempDefenceRange = monsterStringList[4];
    defence = level + randomIntFromRange(tempDefenceRange);
    defenceRange = tempDefenceRange;

    string tempDamageRange = monsterStringList[5];
    damage = level + randomIntFromRange(tempDamageRange);
    damageRange = tempDamageRange;

    itemChance = stoi(monsterStringList[6]);

    carryItemName = "Add item when allocated to the game";
    string tempDescription = monsterStringList[7];
    monsterDescription = tempDescription;
    carryItem = false;

    if (name!="Dragon") {
        monsterObjectList.emplace_back(*this);
        monsterNameList.emplace_back(name);
    }
}

Monster::~Monster() = default;

//The accessor function for retrieving monster information
string Monster::getName() {
    return name;
}
int Monster::getLevel() const {
    return level;
}
int Monster::getHealth() const {
    return health;
}
int Monster::getAttack() const {
    return attack;
}
int Monster::getDefence() const {
    return defence;
}
int Monster::getDamage() const {
    return damage;
}
int Monster::getItemChance() const {
    return itemChance;
}
vector <string> Monster::getRefAttributeList() {
    return refAttributeNameList;
}
vector<string> Monster::getMonsterNameList() {
    return monsterNameList;
}
string Monster::getMonsterDescription() {
    return monsterDescription;
};
string Monster::getCarryItemName() {
    return carryItemName;
}
bool Monster::getCarryItem() const {
    return carryItem;
}

int Monster::getDamageSpFire() const { return 0; }
bool Monster::getIsBoss() const { return 0; }
//These are virtual functions applicable to the dragon class.

vector<Monster*> Monster::getMonsterObjectList() {
    //Returning pointers of what's stored in the object list.
    vector<Monster*> monsterObjectPointerList;
    for (Monster& eachMonster : monsterObjectList)
        monsterObjectPointerList.emplace_back(&eachMonster);

    return monsterObjectPointerList;
}
string Monster::getDetails() {
    //Get and display details of a monster object
    string topLayer = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "~~~~~~~~~~~Monster Status Summary~~~~~~~~~~";
    string nameInfo = "\nName: " + name;
    string attributeInfo = "\nHealth: " + to_string(int(health)) + "\t|\tCarry Item Chance: " + to_string(int(itemChance)) + "\t|" +
        "\nAttack: " + to_string(int(attack)) + "\t|\tDefence: " + to_string(int(defence)) + "\t|\tDamage: " + to_string(int(damage)) + "\t|";
    string otherInfo = "\nMonster description: " + monsterDescription + "\nCarrying Item : " + carryItemName;
    string botLayer = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    stringstream monsterInfo;
    monsterInfo << topLayer << nameInfo << attributeInfo << otherInfo << botLayer << "\n";

    return monsterInfo.str();
}

//The mutator functions
void Monster::setCarryItemName(string itemName) {
    carryItemName = std::move(itemName);
}
void Monster::setAttribute(int updateAmount, MonsterAttribute type) {
    //This is essentially the same as the mutator function for Player class

    switch (type) {
    case MonsterAttribute::Health: {
        //Update the corresponding attribute.
        health = health + updateAmount;
        break;
    }
    case MonsterAttribute::Attack: {
        attack = attack + updateAmount;
        break;
    }
    case MonsterAttribute::Damage: {
        damage = damage + updateAmount;
        break;
    }
    case MonsterAttribute::Defence: {
        defence = defence + updateAmount;
        break;
    }
    }
}

void Monster::setCarryItem(bool set) {
    carryItem = set;
}

//Game play functions

void Monster::monsterResetAfterCombat() {
    //This is after a encounter with player, to be ready for the next encounter, monster needs to be reset/refreshed. Avoid duplicated monsters.
    health = level * randomIntFromRange(healthRange);
    defence = level + randomIntFromRange(defenceRange);
    damage = level + randomIntFromRange(damageRange);
    attack = level + randomIntFromRange(attackRange);

    carryItemName = "Add item when allocated to the game";

}

void Monster::resetSpecialFireDamage() {}