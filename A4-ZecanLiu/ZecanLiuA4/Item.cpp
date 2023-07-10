
/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Item Class Definition File
    Date: 20221030
**************************************************/

#include "Item.h"


//Default Constructor
Item::Item() {
    itemId = id;
    id++;
    name = "Test Item";
    type = ItemType::ITEM;
    useLimit = 0;
    useType = ItemUseType::Unlimited;
    affectAttribute = false;
    affectAttributeName = PlayerAttribute::NA;
    affectAttributeLvl = -1;
    itemDescription = "This is just for test purpose only";
    itemNameList = { "there","is","nothing","in","here" };
    //itemObjectList.emplace_back(*this);
    isConsumable = false;
    bagAmountCap = 0;
    isAttributeBooster = false;
}

//Overload Constructor. Takes string vector as input statement
Item::Item(vector<string> itemStringList) {
    /*
     * The import of item objects are made through a .txt file where information/markers that helps identify and define
     * attributes are defined and separated by ";" as delimiter. Following the order as:
     *
     * Item name: Words;
     * Item type: Number - 1 to 5 marking from Item to Artefact - see Enum Class ItemType definition ;
     * Use type: Number - 1: Fixed, 2:Fixed within a range, 3:Not applicable;
     * Use limit: Mixed - Fixed: XX (a number), Fixed within a range: X1&X2 (X1 X2 are the low and high limits), N/A: NA.
     * Affect attribute name:Words - The name of player attribute that this item affects OR Multi
     *                                                                          - this is exclusively now for potion flask;
     * Affect level:Mixed - N/A:Not available, Fixed: a Number, Multi: to be decided later (can put whatever);
     *                                                                          - again multi here is only for potion flask
     * A description: Words;
     * Consumable marker: Number - 1: is a consumable; 0: is not like a consumable item;
     * Inventory bag cap amount per slot: Number -  How many of this item could be hold in each slot in the bag.
     * Attribute booster marker: Number-> 1:Booster; 0: not a booster - Booster is those item only affect attribute but
     *                                                                          not physically added to the bag.
     */

    itemId = id;
    id++;

    string tempName = itemStringList[0];
    //Stored to a temporary variable first as to avoid memory leak according to suggestion.
    name = tempName;

    itemNameList.emplace_back(tempName);

    switch (stoi(itemStringList[1])) {
    case 1:
        type = ItemType::ITEM;
        break;
    case 2:
        type = ItemType::WEAPON;
        break;
    case 3:
        type = ItemType::ARMOUR;
        break;
    case 4:
        type = ItemType::POTION;
        break;
    case 5:
        type = ItemType::ARTEFACT;
        break;
    default:
        //This default should not be used. This is in case there is an error in the txt file.
        type = ItemType::ITEM;
        break;
    }
    string tempUseLimitRange = itemStringList[3];

    switch (stoi(itemStringList[2])) {
        //Three types in total corresponding to fixed time to use, fixed time but within a range, and unlimited usage.
    case 1:
        useType = ItemUseType::Fixed;
        useLimit = stoi(tempUseLimitRange);
        useLimitRange = tempUseLimitRange + "&" + tempUseLimitRange;
        break;
    case 2:
        useType = ItemUseType::Fixed_Range;
        useLimit = randomIntFromRange(tempUseLimitRange);
        useLimitRange = tempUseLimitRange;
        break;
    case 3:
        useType = ItemUseType::Unlimited;
        useLimit = 1;
        useLimitRange = "1&1";
        break;

    }

    string tempAttributeName = itemStringList[4];
    //affectAttributeName is the name of attribute that this item affect as its efficacy.
    affectAttributeName = static_cast<PlayerAttribute>(
        find(refAttributeList.begin(), refAttributeList.end(),
            tempAttributeName) - refAttributeList.begin());
    //Converting the attribute name as in string to the Enum class of Player Attribute. Beneficial for later use.


    if (affectAttributeName == PlayerAttribute::NA) {
        //NA means the item affect no attribute. Hence, the following definition.
        affectAttributeLvl = 0;
        affectAttribute = false;
    }
    else {
        affectAttribute = true;
        affectAttributeLvl = stoi(itemStringList[5]);
    }

    string tempItemDescription = itemStringList[6];
    itemDescription = tempItemDescription;

    if (stoi(itemStringList[7]) == 1) {
        isConsumable = true;
    }
    else {
        isConsumable = false;
    }

    bagAmountCap = stoi(itemStringList[8]);


    if (stoi(itemStringList[9]) == 1) {
        isAttributeBooster = true;
    }
    else {
        isAttributeBooster = false;
    }

    itemObjectList.emplace_back(*this);
    // Store the created object into the object list. Taking advantage of the "this" pointer in c++.
}

//Default destructor function
Item::~Item() = default;

//Assessor functions
string Item::getName() {
    return name;
}
int Item::getUseLimit() const {
    return useLimit;
}
int Item::getItemId() const {
    return itemId;
}
string Item::getDescription() {
    return itemDescription;
}
string Item::getType() {
    string stringType;
    switch (type) {
    case ItemType::ITEM:
        stringType = "Item";
        break;
    case ItemType::ARMOUR:
        stringType = "Amour";
        break;
    case ItemType::ARTEFACT:
        stringType = "Artefact";
        break;
    case ItemType::POTION:
        stringType = "Potion";
        break;
    case ItemType::WEAPON:
        stringType = "Weapon";
        break;
    }
    if (getIsBooster()) {
        stringType = "Booster Item";
    }
    return stringType;
}
string Item::getUseType() {
    string stringUseType;
    switch (useType) {
    case ItemUseType::Unlimited:
        stringUseType = "Unlimited";
        break;
    case ItemUseType::Fixed:
        stringUseType = "Fixed";
        break;
    case ItemUseType::Fixed_Range:
        stringUseType = "Fixed within a range";
        break;
    }
    return stringUseType;
}
vector<string> Item::getItemNameList() {
    return itemNameList;
}
PlayerAttribute Item::getAffectAttributeName() {
    return affectAttributeName;
}
bool Item::getAffectAttribute() const {
    return affectAttribute;
}
bool Item::getIsConsumable() const {
    return isConsumable;
}
int Item::getAffectAttributeLvl() const {
    return affectAttributeLvl;
}
vector <string> Item::getRefAttributeList() {
    return refAttributeList;
}
string Item::getUseLimitRange() const {
    return useLimitRange;
}
int Item::getBagAmountCap() const {
    return bagAmountCap;
}
string Item::getDetails() {
    //Display the item information.
    string useLimitString = "Unlimited";
    if (static_cast<int>(useType) < 2) {
        useLimitString = to_string(useLimit);
    }
    string affectLvlString = "NA";
    if (affectAttributeName != PlayerAttribute::NA) {
        if (affectAttributeLvl == 0) {
            affectLvlString = "Unknown";
        }
        else if (isConsumable) {
            affectLvlString = "?";
        }
        else {
            affectLvlString = to_string(affectAttributeLvl);
        }
    }

    string topLayer = "~~~~~~~~~~~~~~~~Item Overview~~~~~~~~~~~~~~~";
    string itemOutNameType = "\nItem name: " + getName() + "\t|\tType: " + getType();
    string itemOutInfo = "\nUse limit: " + useLimitString + " use\t|\tAffect attribute: " +
        refAttributeList[static_cast<int>(affectAttributeName)]
        + " for " + affectLvlString;
    string itemOutDescription = "\nAbout: " + getDescription();
    string botLayer = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    stringstream itemInfo;
    itemInfo << topLayer << itemOutNameType << itemOutInfo << itemOutDescription << botLayer;

    return itemInfo.str();
}

vector<Item*> Item::getItemObjectList() {
    //The function for extracting built items to the outside through pointers.
    vector<Item*> itemObjectPointerList;
    for (Item& eachItem : itemObjectList)
        itemObjectPointerList.emplace_back(&eachItem);

    return itemObjectPointerList;
}

bool Item::getIsBooster() const {
    return isAttributeBooster;
}

//Mutator functions
/* For item class most attributes are supposed to remain unchanged throughout the game.
 * Hence, the only necessary mutator function defined up to now is to update the remained uses of an item - useLimit
 */
void Item::setUseLimit(int updateValue) {
    useLimit = useLimit + updateValue;
}

void Item::resetUseLimit() {
    //The reset function is to regenerate the item use limit. This is mainly built for consumables.
    useLimit = randomIntFromRange(getUseLimitRange());
}