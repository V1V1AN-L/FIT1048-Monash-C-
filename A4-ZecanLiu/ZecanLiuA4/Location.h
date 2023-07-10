
#ifndef LOCATION_H
#define LOCATION_H

/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Location Class Header File
    Date: 20221029
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

class Location {
private:
    /*
     * Location object attribute are designed to store not only the location information such as name and description.
     * but also the path information and monster/player/item information if applicable for this location.
     * All location information are according to the map and stored in a txt file which could be imported.
     */
    int locationId;
    //ID - 1st being the entrance.
    string name;
    vector<int> nextLocationIdList;
    //This vector stores the three connected location IDs.
    vector<string> exitDirList;
    //This vector stores the three connected location directions in same position as their ID list.
    string locationDescription;

    //The following are game control attributes associated with a location.
    //As name suggest these parameters help identifying location identities, e.g. if a item is on site.
    bool playerOnSite;
    bool monsterOnSite;
    bool itemOnSite;
    //This is different from the item a player could be found from examine. This is pre-stored item at a given location.
    //Could only be found through the search function.
    bool itemHidden;
    //The preset Item at a location could be either hidden or exposed at a preset chance.
    bool playerExamined;
    bool dragonOnSite;

    string locationItemName;
    string locationMonsterName;
    /*
     * For item and monster in the location, only their names are stored in the location object.
     * This is to avoid excessive duplication and copying of same objects across locations.
     * When a player is in one location, this will be the active location and corresponding item/monster will be activated.
     */

    vector<string> locationAvailableItemList;
    vector<int> locationAvailableItemNumber;


    static  vector <Location> locationObjectList;
    static  vector <string> locationNameList;

    //Static attributes to store the created location objects and their names as reference.
public:
    //Default constructor
    Location();
    //Overload constructor
    explicit Location(vector<string> locationStringList);
    //Default destructor
    ~Location();

    //Assessor functions
    string getName();
    string getDescription();
    bool getPlayerOnSite() const;
    bool getMonsterOnSite() const;
    bool getItemOnSite() const;
    bool getItemHidden() const;
    bool getPlayerExamined() const;
    bool getDragonOnSite() const;
    int getLocationId() const;
    string getExitDir();
    vector <string> getExitDirList();
    vector <int> getNextLocationIdList();
    string getLocationMonsterName();
    string getLocationItemName();
    string getHiddenItemName();

    vector<string> getAvailableItemList();
    vector<int> getAvailableItemNum();
    string getDetails();
    static vector <Location*> getLocationObjectList();

    //Mutators
    void setLocationMonsterName(string monsterName);
    void setLocationItemName(const string& itemName);
    void setLocationItemHidden(bool check);
    void setLocationPlayer(bool check);
    void setLocationDragon(bool check);

    void setPlayerExamined(bool check);
    void setItemToList(const string& itemName);

    void updateAvailableItem(vector <string> updateList, vector <int> updateNumberList);

    //GamePlay
    void monsterDefeated();
protected:
};


#endif //LOCATION_H
