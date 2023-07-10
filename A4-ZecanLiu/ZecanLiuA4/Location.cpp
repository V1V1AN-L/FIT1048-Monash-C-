
/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Location Class Definition File
    Date: 20221030
**************************************************/

#include "Location.h"

#include <utility>
#include "FunctionCollection.h"

//Default Constructor
Location::Location() {

    name = "This is just a test location";
    locationId = 0;
    locationItemName = "There is no item here";
    locationMonsterName = "We don't have a monster here";
    playerOnSite = false;
    locationDescription = "This is just a test location";
    nextLocationIdList = { 0,0,0 };
    exitDirList = { "0","0","0" };
    monsterOnSite = false;
    itemOnSite = false;
    itemHidden = true;
    dragonOnSite = false;
    locationAvailableItemList = {};
    locationAvailableItemNumber = {};
    playerExamined = false;
}

//Overload Constructor
Location::Location(vector<std::string> locationStringList) {
    /*
     * The import of item objects are made through a .txt file where information/markers that helps identify and define
     * attributes are defined and separated by ";" as delimiter. Following the order as:
     * Location ID: Number - Location ID, where 1 is always the entry location/cave;
     * Name: Words - the location name;
     * Description: Words -  A description of the location/cave;
     * Next location ids: Mixed - Should strictly follow the form as id1-id2-id3-....;
     * Next location directions Words - Should strictly follow the form as dir1-dir2-dir3-...., choose from NSWE;
     */
    string tempName = locationStringList[1];
    name = tempName;
    locationId = stoi(locationStringList[0]);
    string tempDescription = locationStringList[2];
    locationDescription = tempDescription;
    //Store name,ID, and location description.

    string tempNextLocationIDString = locationStringList[3];

    const string delimiter = "-";
    size_t indexText;
    while ((indexText = tempNextLocationIDString.find(delimiter)) != string::npos) {
        nextLocationIdList.push_back(stoi(tempNextLocationIDString.substr(0, indexText)));
        tempNextLocationIDString.erase(0, indexText + 1);
    }
    nextLocationIdList.push_back(stoi(tempNextLocationIDString));

    //Take in and store next location IDs.

    string tempNextLocationDirString = locationStringList[4];
    for (int index = 0; index < tempNextLocationDirString.length(); index++) {
        if (tempNextLocationDirString[index] != '-') {
            exitDirList.emplace_back(tempNextLocationDirString.substr(index, 1));
        }
    }
    //Store the next location information into appropriate attributes.

    locationItemName = "";
    locationMonsterName = "";
    monsterOnSite = false;
    itemOnSite = false;
    itemHidden = false;
    locationAvailableItemList = {};
    locationAvailableItemNumber = {};
    playerExamined = false;
    dragonOnSite = false;
    //Default setting up the game play attributes as above, each requires a separate activation.

    if (locationId == 1)
        playerOnSite = true;
    else
        playerOnSite = false;
    //Location 1 is the entry.

    locationObjectList.emplace_back(*this);
    locationNameList.emplace_back(name);
    //Store information into the reference static attributes.
}

Location::~Location() = default;

//Accessors
string Location::getName() {
    return name;
}
string Location::getDescription() {
    return locationDescription;
}
int Location::getLocationId() const {
    return locationId;
}
string Location::getExitDir() {
    //This essentially provides the player a menu of available directions.
    string exitDirString;
    string tempExitString;
    for (const string& eachExitDir : exitDirList) {
        tempExitString.clear();
        if (eachExitDir == "E")
            tempExitString = "E|East \t";
        else if (eachExitDir == "W")
            tempExitString = "W|West \t";
        else if (eachExitDir == "N")
            tempExitString = "N|North \t";
        else if (eachExitDir == "S")
            tempExitString = "S|South \t";
        else
            tempExitString = "Error Direction \t";

        exitDirString.append(tempExitString);
    }
    return exitDirString;
}
vector <string> Location::getExitDirList() {
    return exitDirList;
};
vector <int> Location::getNextLocationIdList() {
    return nextLocationIdList;
}
bool Location::getPlayerOnSite() const {
    return playerOnSite;
}
bool Location::getMonsterOnSite() const {
    return monsterOnSite;
}
bool Location::getItemOnSite() const {
    return itemOnSite;
}

bool Location::getItemHidden() const {
    return itemHidden;
}

bool Location::getPlayerExamined() const {
    return playerExamined;
}

string Location::getLocationMonsterName() {
    string returnMonsterName = monsterOnSite ? locationMonsterName : "Phew...Nothing's here";
    return returnMonsterName;
}
string Location::getLocationItemName() {
    string returnItemName;
    int counter = 0;
    string itemAmount;
    if (!locationAvailableItemList.empty()) {
        for (const string& eachName : locationAvailableItemList) {
            if (!locationAvailableItemNumber.empty()) { itemAmount = "[" + to_string(locationAvailableItemNumber[counter]) + "]"; }
            returnItemName.append(" " + itemAmount.append(eachName));
            counter++;
        }
    }
    else {
        returnItemName = "Nothing you could see";
    }

    return returnItemName;
}

string Location::getHiddenItemName() {
    return locationItemName;
}

bool Location::getDragonOnSite() const {
    return dragonOnSite;
}

string Location::getDetails() {
    string topLayer = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "~~~~~~~Location Information Summary~~~~~~~";
    string locationIdInfo = "\nLocation ID: " + to_string(getLocationId());
    string nameInfo = "\nLocation name: " + getName();
    string locationInfo = "\nAbout: " + getDescription();

    string exitInfo = "\nExit: " + getExitDir();
    string monsterInfo = "\nMonster: " + getLocationMonsterName();
    string itemInfo = "\nItem: " + getLocationItemName();
    string botLayer = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

    stringstream locationGeneralInfo;
    locationGeneralInfo << topLayer << locationIdInfo << nameInfo <<
        locationInfo << exitInfo << monsterInfo << itemInfo << botLayer << "\n";

    return locationGeneralInfo.str();
}
vector <Location*> Location::getLocationObjectList() {
    //Allowing the accessing to created locations by pointers.
    vector<Location*> locationObjectPointerList;
    for (Location& eachMonster : locationObjectList)
        locationObjectPointerList.emplace_back(&eachMonster);

    return locationObjectPointerList;
}

vector <string> Location::getAvailableItemList() {
    return locationAvailableItemList;
}

vector <int> Location::getAvailableItemNum() {
    return locationAvailableItemNumber;
}
//Mutators
void Location::setLocationMonsterName(std::string monsterName) {
    //Used in location activation, when a name assigned, marker becomes true.
    locationMonsterName = std::move(monsterName);
    monsterOnSite = true;
}
void Location::setLocationItemName(const string& itemName) {
    locationItemName = itemName;
    if (!getItemHidden()) {
        locationAvailableItemList.emplace_back(locationItemName);
        locationAvailableItemNumber.emplace_back(1);
    }
    itemOnSite = true;
}

void Location::setLocationItemHidden(bool check) {
    itemHidden = check;
}

void Location::setLocationPlayer(bool check) {
    playerOnSite = check;
}

void Location::setLocationDragon(bool check) {
    dragonOnSite = check;
}

void Location::setPlayerExamined(bool check) {
    playerExamined = check;
}

void Location::setItemToList(const string& itemName) {
    auto itemLocator = find(locationAvailableItemList.begin(), locationAvailableItemList.end(), itemName);
    if (itemLocator == locationAvailableItemList.end()) {
        locationAvailableItemList.emplace_back(itemName);
        locationAvailableItemNumber.emplace_back(1);
    }
    else { locationAvailableItemNumber[static_cast <int> (itemLocator - locationAvailableItemList.begin())] += 1; }

}

void Location::updateAvailableItem(vector<std::string> updateList, vector<int> updateNumberList) {
    locationAvailableItemList = std::move(updateList);
    locationAvailableItemNumber = std::move(updateNumberList);
}


//Game play function
void Location::monsterDefeated() {
    //Reset the location monster information if a monster is defeated
    locationMonsterName = "";
    monsterOnSite = false;
}