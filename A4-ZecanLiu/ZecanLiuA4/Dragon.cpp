
/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Dragon Definition Header File
    Date: 20221030
**************************************************/

#include "Dragon.h"
#include <utility>

Dragon::Dragon() :Monster() {
    //Using the default constructor of Monster class pluss additional definition of special damage.
    damageSpFire = 0;
    isBoss = true;
    damageSpFireRange = "0&0";
}

Dragon::Dragon(vector<string> monsterList, vector <string> dragonList) :
    Monster(std::move(monsterList)) {
    /*
    The overload constructor takes in two vectors of strings.
    The first one being the same as that for the monster object, which is then passed into the monster constructor.
    The second vector contain the dragon-explicit information that is being constructed here in the dragon constructor.
    */
    string tempSpFireRange = dragonList[0];
    damageSpFireRange = tempSpFireRange;
    damageSpFire = getLevel() * randomIntFromRange(tempSpFireRange);
    //setting up the special fire breathing damage
    isBoss = true;
    //this is to later identify it as the dragon. ALso easier implementation later if there will be multiple bosses.
    setCarryItemName("Balthazar's Spell Tome");
    setCarryItem(true);
    //Set the dragon to be carrying the specific artefact.

    dragonObjectList.emplace_back(*this);
    //Still has the vector holding dragon object, though now there is only one.
}

Dragon::~Dragon() = default;


int Dragon::getDamageSpFire() const {
    return damageSpFire;
}

bool Dragon::getIsBoss() const {
    return isBoss;
}

string Dragon::getDetails() {
    //Additional special attack information added to the dragon class get details. Overwriting the monster class getDetails()
    string topLayer = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "~~~~~~~~~~~Monster Status Summary~~~~~~~~~~";
    string nameInfo = "\nName: " + getName();
    string attributeInfo = "\nHealth: " + to_string(int(getHealth())) + "\t|\tCarry Item Chance: " +
        to_string(int(getItemChance())) + "\t|" + "\nAttack: " + to_string(int(getAttack())) + "\t|\tDefence: " +
        to_string(int(getDefence())) + "\t|\tDamage: " + to_string(int(getDamage())) + "\t|";

    string specialAttributeInfo = "\nSpecial fire attack: ***** \t|";
    //The special attack damage is hidden for making it more exciting to play. Every special attack is random.
    string otherInfo = "\nMonster description: " + getMonsterDescription() + "\nCarrying Item : " + getCarryItemName();
    string botLayer = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    stringstream monsterInfo;
    monsterInfo << topLayer << nameInfo << attributeInfo << specialAttributeInfo << otherInfo << botLayer << "\n";

    return monsterInfo.str();

}

vector<Dragon*> Dragon::getDragonObjectList() {
    vector<Dragon*> dragonObjectPointerList;
    for (Dragon& eachDragon : dragonObjectList)
        dragonObjectPointerList.emplace_back(&eachDragon);

    return dragonObjectPointerList;
}

void Dragon::resetSpecialFireDamage() {
    damageSpFire = getLevel() * randomIntFromRange(damageSpFireRange);
}