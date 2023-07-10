
#ifndef ITEM_H
#define ITEM_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Item Class Header File
    Date: 20221030
**************************************************/

#include <iostream>
#include <string>
#include <random>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "EnumClasses.h"
#include "FunctionCollection.h"

using namespace std;

class Item {

private:
    /*
     * Attributes were designed and arranged to allow later interaction with other classes.
     * It is designed to be a bit complicated for the item class as the game requires
     * item to be in connection with all other classes.
     */
    string name;
    ItemType type;
    ItemUseType useType;
    //useType is custom defined to mark whether the object has a certain usage. e.g. the Lamp
    int useLimit;
    //This is to define the initial use allowance assigned to the item.
    string useLimitRange;
    //This is to store the use limit range, if there is one.
    bool affectAttribute;
    //This is to mark if the item has an effect on any of player attribute - bool
    PlayerAttribute affectAttributeName;
    //If it affects attribute, which attribute.
    int affectAttributeLvl;
    //Change the attribute by how much.
    string itemDescription;
    int itemId;
    //This is the id of the item - equivalent to the order item was imported and built. This is current not used.
    bool isConsumable;
    int bagAmountCap;
    bool isAttributeBooster;

    /*
     * The following are static variables - class variables
     * The intention for creating these variables are to have class-global variables that stores the object information
     * and other useful information that's share among objects.
     * To have class objects all stored in the class like a library makes the later use of object more organised.
     * And enabled the use of a single class creating function to be used to initiate different classes.
     */
    static vector<string> refAttributeList;
    //This is the player attribute name list - to make reference to set affected attribute name
    static vector<string> itemNameList;
    //This is just to store the names of items that were created.
    static vector<Item> itemObjectList;
    //This is the list for holding all objects created.
    static int id;
    //This is the counter for each object, which is then assigned to attribute itemId.

public:
    //Default constructor
    Item();
    //Overload constructor
    explicit Item(vector<string> itemStringList);
    //Default destructor
    ~Item();

    //Accessors function
    string getName();
    string getType();
    int getItemId() const;
    string getUseType();
    int getUseLimit() const;
    string getDescription();
    string getDetails();
    PlayerAttribute getAffectAttributeName();
    bool getAffectAttribute() const;
    int getAffectAttributeLvl() const;
    bool getIsConsumable() const;
    string getUseLimitRange() const;
    int getBagAmountCap() const;
    bool getIsBooster() const;
    // For static variables the assessor functions are also made static, which could be called directly.
    static vector <string> getRefAttributeList();
    static vector<Item*> getItemObjectList();
    static vector<string> getItemNameList();

    //Mutators
    void setUseLimit(int updateValue);
    void resetUseLimit();
protected:
};


#endif //ITEM_H

