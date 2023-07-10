
#ifndef GAMEPLAY_H
#define GAMEPLAY_H


/**************************************************
	Project: FIT1048 Assignment 4 - Major Project B
	Project Name: Treasure Caverns of Doom
	Author: Zecan Liu
	Purpose: Main Program Header File
	Date: 20221029
**************************************************/

#include <iostream>
#include <string>
#include <random>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Player.h"
#include "Item.h"
#include "EnumClasses.h"
#include "FunctionCollection.h"
#include "Monster.h"
#include "Location.h"
#include "Dragon.h"
#include "MasterRoshi.h"
#include "HeroLiKui.h"

//Defining the static variable of the all classes where applicable.

vector <Location> Location::locationObjectList;
vector <string> Location::locationNameList;

vector<string> Item::refAttributeList = { "Health","Attack","Damage","Defence","Luck","NA","Multi" };
vector<string> Item::itemNameList;
vector<Item> Item::itemObjectList;
int Item::id = 0;

vector<string> Monster::refAttributeNameList = { "Health","Attack","Damage","Defence","ItemChance" };
vector<string> Monster::monsterNameList;
vector<Monster> Monster::monsterObjectList;
int Monster::id = 0;

vector<Dragon> Dragon::dragonObjectList;

/*
 * Definition of Global Variables
 * Note that these variables are defined to assist the activation of monster for carrying artefact.
 * These variables are only used explicitly in part of the game functionality
 */

vector<string> inactiveArtefactNameList = { "Krang's Battle Axe","Krang's Chainmail","Boots of Speed","Elixir Maxima" };
int remainArtefactCarrierCount = 6;


/*
 * Here below are the game play functions that contribute to the overall game flow and mechanisms
 * These are building blocks of the game. Still incomplete - ones completed below are associated with setting up only.
 */
void playGame();
//The main game play mechanism function.
void help();
//This is help page. 
void createList(const string& myFile, vector<string>& myVector);
//This is the .txt file reader which returns the vector form of the file.
void createClass(ClassType classType, const string& fileName);
//This is a universal class builder.
void showPlayerLocation();
//A function that find/locate the active location - one with player in it.
void gameDifficultySelection(GameDifficulty& selectedDifficulty,
	int& oilCostPerMove, vector <string>& addItemNameList,
	int& startGameGem, int& startGameGold, bool& dragonRoaming);
//This is the selection function for the player to select a difficulty to play.
void initialiseLocation(const vector <int>& numberList, vector <string> nameRefList,
	ClassType classType, vector<int> hiddenChanceList = {});
//Activating locations - assigning a number of monsters or items to randomly selected locations.
void initialiseDragonLocation();
//Assigning Dragon to a location
void initialiseGameWorld(GameDifficulty gameDifficulty);
//Setting up the entire game environment.
void gameStore(Player& activePlayer, int lanternLocation, int goldAmount, int gemAmount);
//This function allows the player to purchase the starting gear.
Monster* encounterMonster(const string& monsterName);
//Activating a monster - as player enters a new cave, the monster (if there is) is activated.
void endGameCheckFunction(bool& check, EndGameScene& scene, EndGameScene control, Player* activePlayer,
	int oilCost = 0, int latLocation = 0);
//Check if an end game criteria is met.
string playerInteractionInterface(const string& interactionType);
//The interface for user to make selection in a location. Different interface at different scenario.
void leaveCurrentLocation(Location*& currentLocation, Player* activePlayer,
	int oilCost, bool& endLocationCheck, int latLocation);
//The function that allows the player to leave the current location, make a selection, and move to the next location.
void combat(Player& player, Monster* monster);
//The function that takes a monster and a player to initiates the combat sequence.
void examineCurrentLocation(Player& activePlayer, Location* activeLocation, int latLocation);
//The function that allows the player to examine a location and see if could find a item, by chance.
void takeItemFromLocation(Player& activePlayer, Location* activeLocation);
//This function allows the player to take item from the active location from the available item list. The player can
//either take all available items or select a specific item of a specific amount to put in the bag, when applicable.
void searchLocation(Player* activePlayer, Location* activeLocation);
//This is a special function for realising a special capability of the game play. Search the location would reveal the
//hidden item in that location, if there is one. This would however cost health in return.
void roamingDragon();
//Function allowing the dragon to roam around the caves.
void endGameProcessor(EndGameScene scene);
//The end game processor is to return the correct end game message given the end game scenario.

/*
 * Following are the test functions.
 * These are only for test purposes.
 */
int startGame();
void testRandomIntGenerator();
void testPlayerClass();
void testPlayerSetAttribute();
void testPlayerPickUpItem();
void testPlayerUseConsumable();
void testItemClass();
void testMonsterClass();
void testMonsterReset();
void testEncounterMonster();
void testLocationClass();
void testInitialiseLocation();
void testInitialiseGameWorld();
void testDragonClass();



#endif //GAMEPLAY_H