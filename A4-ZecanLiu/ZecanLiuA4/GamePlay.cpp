/**************************************************
	Project: FIT1048 Assignment 4 - Major Project B
	Project Name: Treasure Caverns of Doom
	Author: Zecan Liu
	Purpose: Main Program Definition File
	Date: 20221030
**************************************************/

#include "GamePlay.h"



int main() {

    //Not declaring srand here as the program took a different approach (Mersenne Twister pseudo-random generator) 
    //with generating random number and it is packed in a function randomIntegerFromRange
    playGame();


    return 0;
}



void playGame() {
    /*
     * This is the main function that allows the game play.
     * It can be divided into two main steps as first setting up the game and pre-game player preparation.
     * This followed by the actual game mechanism of stitch location, making selection, collecting item and
     * encountering monster.
     */
    bool endGameCheck = false;
    EndGameScene endGameScene = EndGameScene::userQuit;
    Location* activeLocation = nullptr;
    Monster* activeMonster = nullptr;
    TreasureHunter* activeTreasureHunter = nullptr;
    bool endLocationSelection = false;
    bool endMonsterSelection = false;
    bool dragonRoaming = false;

    GameDifficulty gameDifficulty = GameDifficulty::Tourist;

    string userChoice;
    string locationName;
    //Setting up a number of game parametres.
    
    displayTextData("DragonSymbol.txt");
    displayTextData("About.txt");

    system("Pause");

    vector<string> availableLocationSetUpFiles = { "Location_1.txt","Location_2.txt","Location_3.txt" };
    vector<string> availableMapFiles = { "Map_1.txt","Map_2.txt","Map_3.txt" };
    int locationSetUpSelection = randomIntFromRange("1&" + to_string(availableLocationSetUpFiles.size())) - 1;
    string locationSetUpFile = availableLocationSetUpFiles[locationSetUpSelection];
    string mapFile = availableMapFiles[locationSetUpSelection];
    //Randomly selecting a map from the three available

    cout << "\n\nInitialising the Game World >>>>>>>\n\n";
    createClass(ClassType::ITEM, "Items.txt");
    createClass(ClassType::MONSTER, "Monster.txt");
    createClass(ClassType::LOCATION, locationSetUpFile);
    createClass(ClassType::Dragon, "Dragon.txt");
    cout << "\nGame parameters loading completed...\n\n";
    //Loading and initialising the objects of the game -  player, item, monster, and location.
    system("Pause");
    help();
    system("CLS");

    //Showing the general game information first.
    if (!getConfirmation("\n\nAre you ready for the adventure?")) {
        endGameCheck = true;
        endGameScene = EndGameScene::userQuitStart;
    }
    //Displaying the game cover page and the general information. Taking player's first input as to continue game.




    if (!endGameCheck) {
        system("CLS");
        cout << "\nThe Adventure Begins Now\n";
        Player playerActive(getInput("Please entre a Player name:"));
        cout << "\n\n" << playerActive.getDetails() << endl;
        system("Pause");

        vector <TreasureHunter*> specialCharacterList;
        vector <int> specialCharacterFirstAppearList;
        /*
         * This below section is to realise the special characters, other NPCs in the caves.
         * To help elevates the diversity in game play, these NPCs are not assigned to any
         * specific location, rather they would appear at a certain amount of moves taken by the player.
         */
        specialCharacterList.emplace_back(new MasterRoshi("Roshi Roshi"));
        specialCharacterFirstAppearList.emplace_back(randomIntFromRange("7&10"));
        specialCharacterList.emplace_back(new HeroLiKui("Li Kui"));
        specialCharacterFirstAppearList.emplace_back(randomIntFromRange("14&16"));

        //Create the special characters;

        //Special character - Roaming treasure hunter 1
        int oilCostPerMove = 0;
        int startGameGem = 0;
        int startGameGold = 0;
        vector <string> addItemNameList;
        //Allowing the player to make selection of game difficulty.
        gameDifficultySelection(gameDifficulty, oilCostPerMove,
            addItemNameList, startGameGem, startGameGold, dragonRoaming);

        initialiseGameWorld(gameDifficulty);
        //Accordingly build up the game world.
        Monster* dragon = Dragon::getDragonObjectList()[0];
        cout << "\n\n    !Game World Set Up Completed! \n\n";
        cout << "\n It will cost you " << oilCostPerMove << "per move";
        system("Pause");
        system("CLS");

        cout << "\n\nNow lets get you ready and geared up\n"
            "Loading the starting item list to your bag.\n\n";
        system("Pause");

        for (const string& itemName : addItemNameList) {
            playerActive.pickItemUp(itemName);
        }
        cout << "\n\nProcess completed!\n\nThis is the current player status:\n\n";
        //Pickup the start-up gear for the player - e.g. map and lantern are the two mandatory item to start the game.
        cout << playerActive.getDetails();
        //Show the player status.

        cout << "\n\nYou are directed to a store to get ready to the adventure first... \n\n";

        system("Pause");

        vector <string> playerBagNameList = playerActive.getBagItemNameList("A");
        int lanternLocation = static_cast<int>(find(
            playerBagNameList.begin(), playerBagNameList.end(), "Lantern") - playerBagNameList.begin());
        //Find the index/location of lantern in the bag. This is to accompany the adding lantern oil functionality.
        gameStore(playerActive, lanternLocation, startGameGold, startGameGem);
        //Let the player do a bit shopping.
        cout << "\n\nOk.. Looks like you are all prepared!\nNow start your adventure.\nEntering the cave.....\n";
        system("Pause");
        system("CLS");
        
        activeLocation = Location::getLocationObjectList()[0];
        //Initializing the game with location 1 as the entry cave.
        int moveCounter = 0;
        int monsterDefeat = 0;
        int monsterEncounter = 0;
        //These are the game scoring system, counting moves, monster encountered, and monster defeated.
        int treasureHunterEncounterCount = 0;

        while (!endGameCheck) {
            system("CLS");
            //Wrapped within this while loop is the actual game play.
            if (activeLocation->getLocationId() == 1) {
                endGameCheckFunction(endGameCheck, endGameScene, EndGameScene::userWin, &playerActive);
            }
            //If the player is at the entry location, check for win condition.

            locationName = activeLocation->getName();
           
            if (activeLocation->getMonsterOnSite() || activeLocation->getDragonOnSite()) {
                //initiating the monster interaction interface if a monster is at presence in the location.
                
                cout << "\n\n\n" << activeLocation->getDetails() << endl;
                cout << "\n\n\n" << playerActive.getDetails() << "\n\n";;
                //Show the general information as entering a cave.

                monsterEncounter++;
                if (activeLocation->getDragonOnSite()) {
                    cout << "\n\nYou have encountered the Dragon!!!";
                    activeMonster = dragon;
                }
                else {
                    cout << "\n\nYou have encountered a " + activeLocation->getLocationMonsterName() << endl;
                    activeMonster = encounterMonster(activeLocation->getLocationMonsterName());
                }

                system("Pause");
                
                // Stating to the player that which monster is encountered.
                while (!endMonsterSelection) {
                    system("CLS");
                    cout << "\n\n\n" << activeMonster->getDetails() << "\n\n";

                    // Entering the monster-active player selection interface.
                    endGameCheckFunction(endGameCheck, endGameScene,
                        EndGameScene::userTrap, &playerActive,
                        -oilCostPerMove, lanternLocation);
                    //Check if the player is already trapped.
                    userChoice = playerInteractionInterface("Monster");
                    //Showing the options and take user input
                    //According to the user input perform corresponding actions.

                    if (userChoice == "a") {
                        //Initiate the combat sequence.
                        cout << "\n\nBravo Brave Soul \nLet the Battle Begin\n";
                        system("Pause");
                        combat(playerActive, activeMonster);
                        if (playerActive.getHealth() > 0) {
                            //player win
                            cout << "You won this battle\n"
                                << playerActive.getDetails();
                            monsterDefeat++;
                            playerActive.setAttribute(1, PlayerAttribute::Attack);
                            cout << "\n\n Increased your attack by 1 \n\n";
                            if (activeMonster->getIsBoss()) {
                                //In case the dragon is being taken down,
                                activeLocation->setLocationDragon(false);
                            }
                            else { activeLocation->monsterDefeated(); }

                            if (activeMonster->getCarryItem()) {
                                activeLocation->setItemToList(activeMonster->getCarryItemName());
                                // In case of a player win and monster carried an item, the item is now available
                                // in the location and could be picked up by player.
                            }
                        }
                        else {
                            cout << "Looks like you have lost this one\n";
                        }
                        endMonsterSelection = true;
                        //Either way out of a combat sequence, the monster selection interface is terminated.
                        system("Pause");

                    }

                    else if (userChoice == "f") {
                        //This is where the player selected to Flee the cave.
                        cout << "\nHeHe. Run Coward Run......" << "\n\n";
                        system("Pause");

                        if (playerActive.getDefence() >= activeMonster->getDamage()) {
                            playerActive.setAttribute(-1, PlayerAttribute::Health);
                            //even if the player defense is higher than monster damage, if player decided to run, the
                            // player must take minimum damage of 1.
                        }

                        else {
                            playerActive.setAttribute(
                                -(activeMonster->getDamage() - playerActive.getDefence()),
                                PlayerAttribute::Health);
                            //calculate the minimum damage that the monster could done on player.
                        }

                        cout << "Got hit from the back....\n";
                        leaveCurrentLocation(activeLocation, &playerActive,
                            oilCostPerMove, endLocationSelection, lanternLocation);
                        if (endLocationSelection) {
                            //if the player flee from a monster that is carrying a artefact, the artefact will return to
                            //the available pool and will be later randomly assigned to monster.
                            endMonsterSelection = true;
                            vector<string> checkArtefactList = { "Krang's Battle Axe","Krang's Chainmail",
                                                              "Boots of Speed","Elixir Maxima" };
                            if (count(checkArtefactList.begin(), checkArtefactList.end(),
                                activeMonster->getCarryItemName()) != 0) {
                                inactiveArtefactNameList.emplace_back(activeMonster->getCarryItemName());
                                remainArtefactCarrierCount += 1;
                            }
                        }
                        system("Pause");

                    }

                    else if (userChoice == "p") {
                        //The player can select to revive prior combat the monster.
                        cout << "\nRevive and Survive.... Wise move\n\n";
                        system("Pause");

                        cout << playerActive.getDetails();
                        playerActive.useItemConsumable();
                        cout << playerActive.getDetails();
                        system("Pause");

                    }

                    else if (userChoice == "m") {
                        //Showing map
                        cout << "\nshowing the Map\n\n";
                        system("Pause");
                        system("CLS");

                        displayTextData(mapFile);

                        system("Pause");

                    }
                    else if (userChoice == "h") {
                        //Showing help information.
                        cout << "\n\n Displaying Help Information \n\n";
                        displayTextData("HelpInformation.txt");
                        system("Pause");

                    }
                    else if (userChoice == "q") {
                        //Player can quit anytime.
                        endGameCheckFunction(endGameCheck, endGameScene,
                            EndGameScene::userQuit, &playerActive);
                        if (endGameCheck) { endMonsterSelection = true; }

                    }

                    endGameCheckFunction(endGameCheck, endGameScene,
                        EndGameScene::userTrap, &playerActive,
                        -oilCostPerMove, lanternLocation);
                }
                endGameCheckFunction(endGameCheck, endGameScene,
                    EndGameScene::userDie, &playerActive);

                endMonsterSelection = false;

                if (!activeLocation->getDragonOnSite())
                    activeMonster->monsterResetAfterCombat();
                else
                    activeMonster->resetSpecialFireDamage();
                //Resetting the monsters after encounter. They will not be the same when you are back.
            }

            if ((count(specialCharacterFirstAppearList.begin(),
                specialCharacterFirstAppearList.end(), moveCounter) != 0) && !endGameCheck) {
                system("CLS");
                cout << "Wait..... Is that Another People In Front?!?!\n\n";
                system("Pause");
                activeTreasureHunter = specialCharacterList[treasureHunterEncounterCount];
                treasureHunterEncounterCount++;
                activeTreasureHunter->speak();
                system("Pause");
                cout << "Oh wow, this is ...\n\n";
                activeTreasureHunter->getDetails();
                system("Pause");
                activeTreasureHunter->interaction(&playerActive);
                endGameCheckFunction(endGameCheck, endGameScene,
                    EndGameScene::userDie, &playerActive);
            }

            while (!endLocationSelection && !endGameCheck) {
                //This is the no monster interaction interface. Shown when location has no monster or wining combat.
                system("CLS");
                endGameCheckFunction(endGameCheck, endGameScene,
                    EndGameScene::userTrap, &playerActive,
                    -oilCostPerMove, lanternLocation);

                cout << "\n\n\n" << activeLocation->getDetails();
                cout << "\n\n\n" << playerActive.getDetails()<<"\n\n";
                //Show the general information as entering a cave.
               

                userChoice = playerInteractionInterface("Game");
                if (userChoice == "x") {
                    cout << "\n";
                    //Examine the location - only if the location was not examined before.
                    cout << "Examining the current location: \n";
                    system("Pause");

                    if (activeLocation->getPlayerExamined()) {
                        cout << "This location has been examined before..Nothing else to see\n";
                    }
                    else {
                        examineCurrentLocation(playerActive, activeLocation, lanternLocation);
                        activeLocation->setPlayerExamined(true);

                    }
                    system("Pause");

                }

                else if (userChoice == "l") {
                    cout << "\nLeaving this cave...\n";
                    system("Pause");

                    //Leave the location.
                    leaveCurrentLocation(activeLocation, &playerActive,
                        oilCostPerMove, endLocationSelection, lanternLocation);
                    system("Pause");

                }
                else if (userChoice == "p") {
                    cout << "\n";
                    cout << "Revive and Survive.... Wise move\n";
                    system("Pause");

                    cout << playerActive.getDetails();
                    playerActive.useItemConsumable();
                    cout << playerActive.getDetails();
                    system("Pause");

                }
                else if (userChoice == "t") {
                    cout << "\nSee if there is anything to grab....\n";
                    system("Pause");

                    //Take item from location.
                    takeItemFromLocation(playerActive, activeLocation);
                    system("Pause");

                }
                else if (userChoice == "d") {
                    cout << "\n";
                    //Drop item from the bag
                    cout << "Dropping item from the bag, sigh.....\n";
                    system("Pause");

                    playerActive.dropItem();
                    system("Pause");

                }
                else if (userChoice == "s") {
                    cout << "\n";
                    //Search the location for hidden item!
                    cout << "Lets really search this cave inside out then..\n";
                    system("Pause");

                    searchLocation(&playerActive, activeLocation);
                    system("Pause");

                }
                else if (userChoice == "m") {
                    cout << "\nShowing the map\n";
                    system("Pause");
                    system("CLS");
                    displayTextData(mapFile);
                    system("Pause");


                }
                else if (userChoice == "h") {
                    cout << "\n";
                    displayTextData("HelpInformation.txt");
                    system("Pause");

                }
                else if (userChoice == "q") {
                    cout << "\n";
                    endGameCheckFunction(endGameCheck, endGameScene,
                        EndGameScene::userQuit, &playerActive);
                    if (endGameCheck) { endLocationSelection = true; }
                    system("Pause");

                }
                endGameCheckFunction(endGameCheck, endGameScene,
                    EndGameScene::userDie, &playerActive);
                endGameCheckFunction(endGameCheck, endGameScene,
                    EndGameScene::userTrap, &playerActive,
                    -oilCostPerMove, lanternLocation);

            }
            endLocationSelection = false;

            //for each move from player, show stats, move dragon if required, and show dragon position.
            if (!endGameCheck) {
                moveCounter++;
                cout << "This is your " << to_string(moveCounter) << " move!\n\n";
            }

            if (dragonRoaming) { roamingDragon(); }

            vector <Location*> locationList = Location::getLocationObjectList();
            for (Location* eachLocation : locationList) {
                if (eachLocation->getDragonOnSite()) {
                    cout << "The dragon is in cave: " << to_string(eachLocation->getLocationId()) << " - " + eachLocation->getName() << endl;
                }
            }
            cout << "\nMade " << moveCounter << " moves\n";
            cout << "\nEncountered " << monsterEncounter << " monsters";
            cout << "\nDefeated " << monsterDefeat << " of them\n\n";
            system("Pause");
        }

        specialCharacterList.clear();
        //Clear for preventing memory leak.
    }
    
    endGameProcessor(endGameScene);
    //show end game message.
}

void help() {
    

    bool endHelpSession = false;
    vector <string> availableSelectionList = { "i","m","g","q" };
    string userSelection;

    while (!endHelpSession) {

        system("CLS");
        displayTextData("HelpInformation.txt");
        while (userSelection.empty()) {
            userSelection = getInput("\nPlease make a selection according to the options provided: ");
            for (char& eachChar : userSelection) {
                eachChar = tolower(eachChar);
            }
            if (count(availableSelectionList.begin(), availableSelectionList.end(), userSelection) == 0) {
                cout << "Invalid Selection, Please Retry....\n";
                userSelection.clear();
            }
        }

        if (userSelection == "i") {
            
            system("CLS");
            cout << "\n\n============================ Displaying the Item Information of the Game =================================\n"
                    "========================== These are what you gonna find through out the game ==============================\n\n"
                    "===================== Note that for consumable items, the details are only examplary =======================\n\n"
                    "================ Booster item add-ons to your attribute, they dont take up space in the bag ================\n\n";
            system("Pause");

            vector <Item*> itemList = Item::getItemObjectList();
            for (Item* eachItem : itemList) {
                cout << eachItem->getDetails() << endl;
            }
            cout << "\n\n================================ Thats all for now =====================================\n\n";
            system("Pause");
        }
        else if (userSelection == "m") {
            system("CLS");
            cout << "\n\n========================== Displaying the Monster Information of the Game ================================\n"
                    "======================= These are what you gonna encounter through out the game ============================\n\n"
                    "============== Note that these are just examples, the monsters are all different in there ==================\n\n"
                    "================ The Boss -  Drgon is a misterious one, You need to explore yourself there =================\n\n";

            system("Pause");

            vector <Monster*> monsterList = Monster::getMonsterObjectList();
            for (Monster* eachMonster : monsterList) {
                cout << eachMonster->getDetails() << endl;
            }
            cout << "\n\n================================ Thats all for now =====================================\n\n";
            system("Pause");

        }
        else if (userSelection == "g") {
            system("CLS");
            displayTextData("GamePlayInformation.txt");
            system("Pause");
        }
        else {
            cout << "\n\n Ending Session\n\n";
            endHelpSession = true;
            system("Pause");
        }
        userSelection.clear();
    }

}

void endGameCheckFunction(bool& check, EndGameScene& scene, EndGameScene control, Player* activePlayer,
    int oilCost, int latLocation) {
    /*
     * This function checks if any of the end game condition is met.
     * If any of the condition is met, the game play sequence will be automatically terminated.
     * It will then run the end game processor for the final message.
     */
    if (!check) {
        scene = control;
        switch (scene) {
        case EndGameScene::userQuit:
            check = getConfirmation("Now...\n"
                "I see you trying to quit now.\n"
                "Are you sure you just gonna run? ....\n");
            break;
        case EndGameScene::userDie:
            if (activePlayer->getHealth() <= 0) { check = true; }
            break;
        case EndGameScene::userWin:
            if (activePlayer->collectedArtefactCounter() == 5) { check = true; }
            break;
        case EndGameScene::userTrap:
            if (activePlayer->getInventoryBagUseLimit()[latLocation] < oilCost) { check = true; }
            break;
        case EndGameScene::userQuitStart:
            break;
        }
    }
}

void endGameProcessor(EndGameScene scene) {
    /*
     * THhe end game processor is to provide the correct message as the game approaches an end.
     * The corresponding end game scene is taken as an input argument.
     */
    switch (scene) {
    case EndGameScene::userQuitStart:

        cout << "=================================================================\n\n"
                "=========Hopefully you will be Better Prepared Next Time=========\n\n"
                "============Now Run for Your Life! When you still can!===========\n\n"
                "=================================================================\n\n";
        break;
    case EndGameScene::userQuit:

        cout << "=================================================================\n\n"
            "==========================  Pity....~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
            "=========Hopefully you will be Better Prepared Next Time=========\n\n"
            "===================Now you should better Run!====================\n\n"
            "=================================================================\n\n";
        break;
    case EndGameScene::userDie:
        cout << "=================================================================\n\n"
            "===================Well.....This is the End======================\n\n"
            "============Wish you better luck on the other side===============\n\n"
            "=================================================================\n\n";
        break;
    case EndGameScene::userWin:
        cout << "=================================================================\n\n"
            "=========================CONGRATULATIONS=========================\n\n"
            "=========YOU HAVE MADE IT! YOU ARE THE DRAGON SLAYER NOW!========\n\n"
            "=================================================================\n\n";
        break;
    case EndGameScene::userTrap:
        cout << "=================================================================\n\n"
            "=====================Oh NO you are trapped=======================\n\n"
            "====================This is it for you then======================\n\n"
            "=================================================================\n\n";
        break;
    }
}

void gameStore(Player& playerActive, int lanternLocation, int goldAmount, int gemAmount) {
    /*
     * This is the function that enables the pre-game store.
     * The available funds are the gold and gem amount.
     */
    int currentGoldAmount = goldAmount;
    int currentGemAmount = gemAmount;

    string shopHeader = "========================================================================\n"
        "                       Welcome to the shop                              \n"
        "    Get Ready for Your Adventure Ahead, This is Your Only Chance        \n"
        "========================================================================\n";

    vector <string> shopItemList = { "Sword","Armour","Elite Sword","Elite Armour","Health Potion",
                                  "Lantern oil - 30","Provision","Potion Flask",
                                  "Shards of Sword","Shards of Armour","Shards of Elite Sword","Shards of Elite Armour" };
    vector <int> shopItemPriceList = { 6,6,12,12,6,4,3,3,4,4,6,6 };
    vector <int> shopItemCategory = { 1,1,1,1,1,2,2,2,2,2,2,2 };
    //The categories are basically dividing gem-purchasable and gold-purchasable items.

    int lanternOilUnit = 30;
    //lantern oil are sold here in unit of 30 uses.

    vector <string> shopCodeList;
    string completeListItemString;
    int counterShards = 0;
    int counterElites = 0;
    int counter = 0;
    /*
     * The following is to generate the selection menu. Showing the selection code|item name and the corresponding price.
     * The selection code are still based on the first two letters, but for those has the same first two letters, further
     * distinguishable numbering is added.
     */
    for (string eachName : shopItemList) {
        string tempCode;
        if (eachName.substr(0, 6) == "Shards") {
            counterShards++;
            tempCode = eachName.substr(0, 2).append(to_string(counterShards));
        }
        else if (eachName.substr(0, 5) == "Elite") {
            counterElites++;
            tempCode = eachName.substr(0, 2).append(to_string(counterElites));
        }
        else {
            tempCode = eachName.substr(0, 2);
        }
        for (char& eachChar : tempCode) {
            eachChar = tolower(eachChar);
        }
        shopCodeList.emplace_back(tempCode);
        string tempPrice = to_string(shopItemPriceList[counter]);
        if (shopItemCategory[counter] == 1) { tempPrice.append(" Gems"); }
        else { tempPrice.append(" Golds"); }

        eachName.append("[" + tempPrice + "]");

        completeListItemString.append(tempCode.append("|" + eachName + "       "));
        counter++;
        if (counter % 2 == 0) { completeListItemString.append("\n"); }

    }
    string currentBalance;
    string userSelection;
    bool continueShop = true;
    bool goodPurchase = false;

    while (continueShop) {
        //showing the balance while allowing the player to make a selection.
        system("CLS");
        userSelection.clear();
        currentBalance = to_string(currentGemAmount) + " Gems    " + to_string(currentGoldAmount) + " Golds    \n";
        cout << shopHeader << "\n" << "Current Balance: " << currentBalance << "\n" << completeListItemString << endl;
       
        cout << "\n" << playerActive.getDetails() << "\n\n";
        
        while (userSelection.empty()) {
            userSelection = getInput("Which item you want to buy?");
            for (char& eachChar : userSelection) {
                eachChar = tolower(eachChar);
            }
            if (count(shopCodeList.begin(), shopCodeList.end(), userSelection) == 0) {
                cout << "Invalid Selection, Please Retry....\n";
                userSelection.clear();
            }
        }

        //in the following, update the player bag and player attribute according to the selection.
        int tempItemLocator = static_cast<int>(find(
            shopCodeList.begin(), shopCodeList.end(), userSelection) - shopCodeList.begin());

        if (shopItemCategory[tempItemLocator] == 1) {
            goodPurchase = (currentGemAmount >= shopItemPriceList[tempItemLocator]);
            if (goodPurchase) { currentGemAmount -= shopItemPriceList[tempItemLocator]; }
        }
        else {
            goodPurchase = (currentGoldAmount >= shopItemPriceList[tempItemLocator]);
            if (goodPurchase) { currentGoldAmount -= shopItemPriceList[tempItemLocator]; }
        }

        if (goodPurchase) {
            if (userSelection != "la") {
                cout << endl;
                playerActive.pickItemUp(shopItemList[tempItemLocator]);
            }
            else {
                cout << "\n\nSmart.. refilling that lantern is a must!\n\n";
                playerActive.setInventoryBagUseLimit(lanternLocation, lanternOilUnit);
            }
        }
        else {
            cout << "Insufficient Fund... Maybe next time\n";
        }

        cout << playerActive.getDetails();
        continueShop = getConfirmation("Continue shopping?");
    }

    //picking up the remaining gold and gem after spending in the store.
    cout << "\n\nPicking up the left Gold and Gem.... If there are any left....\n\n";
    if (currentGoldAmount > 0) {
        for (int goldRemain = 0; goldRemain < currentGoldAmount; goldRemain++) {
            playerActive.pickItemUp("Gold");
        }
    }
    if (currentGemAmount > 0) {
        for (int gemRemain = 0; gemRemain < currentGoldAmount; gemRemain++) {
            playerActive.pickItemUp("Gem");
        }
    }
    cout << "\n\n============================================================================\n\n"
        "Thank you for visiting the store, hopefully you now have everything you need\n\n"
        "============================================================================\n\n";
}

string playerInteractionInterface(const string& interactionType) {
    /*
     * This is the main interfaces of the game.
     * Note that there are two interfaces for case of encountering a monster or a safe cave condition.
     * User selection is limited when facing a monster, need to deal with the monster first.
     */
    vector<string> optionReferenceList;
    if (interactionType == "Monster") {
        optionReferenceList = { "a", "f", "p", "m", "h", "q" };
        cout << "============================================================\n"
            "             A|Attack    F|Flee     P|Provision            \n"
            "             M|Map       H|Help     Q|Quit                 \n"
            "============================================================\n";
    }
    else
    {
        optionReferenceList = { "x", "l", "p", "t", "d", "s", "m", "h", "q" };
        cout << "============================================================\n"
            "    X|Examine   L|Leave   P|Provision   T|Take   D|Drop     \n"
            "         S|Search      M|Map     H|Help     Q|Quit          \n"
            "============================================================\n";
    }

    string userInput;
    while (userInput.empty()) {
        userInput = getInput("Please make you selection: ");
        for (char& inputChar : userInput)
            inputChar = tolower(inputChar);

        if (count(optionReferenceList.begin(), optionReferenceList.end(), userInput) == 0) {
            userInput.clear();
            cout << "Please provide a Valid Input.\n";
        }
    }
    return userInput;
}

void gameDifficultySelection(GameDifficulty& selectedDifficulty,
    /*
     * This is the game functionality that allows the player to choose a game difficulty level.
     * It is currently set to have 4 different game levels, each has a different game setup.
     */
    int& oilCostPerMove, vector <string>& addItemNameList,
    int& startGameGem, int& startGameGold, bool& dragonRoaming) {

    vector <string> availableDifficultyList = { "t","a","m","h" };
    cout << "\n==============================================================\n"
            "====================Available Difficulties====================\n\n"
            "                 t|I just want to take a tour               \n\n"
            "          a|Bring it on, but just on a average level        \n\n"
            "             m|Try me, I am a real master on this           \n\n"
            "                     h|Bring me to hell                     \n\n"
            "==============================================================\n";

    string userInput;
    while (userInput.empty()) {
        userInput = getInput("Please make you selection: ");
        for (char& inputChar : userInput)
            inputChar = tolower(inputChar);

        if (count(availableDifficultyList.begin(), availableDifficultyList.end(), userInput) == 0) {
            userInput.clear();
            cout << "Please provide a Valid Input.\n";
        }
    }

    int userInputInt = static_cast <int> (
        find(availableDifficultyList.begin(), availableDifficultyList.end(), userInput)
        - availableDifficultyList.begin());
    selectedDifficulty = static_cast<GameDifficulty>(userInputInt);


    switch (selectedDifficulty) {
        /*
         * In here the different difficulty changes the starting status of a player, the oil cost per move, the initial
         * fund for spend in the game store and whether the dragon roams around in the caves.
         */
    case GameDifficulty::Tourist:
        cout << "\n\nOK, Just a chill walk around then\n\n";
        oilCostPerMove = -1;
        addItemNameList = { "Map","Lantern","Shards of Elite Sword","Shards of Elite Armour","Health Potion" };
        startGameGem = randomIntFromRange("30&40");
        startGameGold = randomIntFromRange("30&40");
        dragonRoaming = false;
        break;
    case GameDifficulty::Average:
        cout << "\n\n OK, Enjoy the journey, should be fund \n\n";
        oilCostPerMove = -2;
        startGameGem = randomIntFromRange("12&20");
        startGameGold = randomIntFromRange("18&22");
        dragonRoaming = false;
        break;
    case GameDifficulty::Master:
        cout << "\n\n Wowo, It's gonna be a exciting one \n\n";
        oilCostPerMove = -3;
        addItemNameList = { "Map","Lantern" };
        startGameGem = randomIntFromRange("12&20");
        startGameGold = randomIntFromRange("13&18");
        dragonRoaming = true;
        break;
    case GameDifficulty::Hell:
        cout << "\n\n Well, you are clearly delusional \n\n";
        oilCostPerMove = -4;
        addItemNameList = { "Map","Lantern" };
        startGameGem = randomIntFromRange("6&12");
        startGameGold = randomIntFromRange("10&16");
        dragonRoaming = true;
        break;
    }
}

void roamingDragon() {
    /*
     * This is the extra functionality that allows the dragon to be moved between caves following the available path
     * the dragon's movement is only activated when game difficulty is set to master or hell level.
     * The dragon's path chosen for each move is purely random.
     */
    vector <Location*> locationList = Location::getLocationObjectList();
    Location* currentDragonLocation=nullptr;
    for (Location* eachLocation : locationList) {
        if (eachLocation->getDragonOnSite()) {
            currentDragonLocation = eachLocation;
            currentDragonLocation->setLocationDragon(false);
            //leave the current dragon location.
        }
    }
    vector<int> nextAvailableLocationIdList = currentDragonLocation->getNextLocationIdList();
    int nextDragonLocationID =
        nextAvailableLocationIdList[randomIntFromRange
        ("0&" + to_string(nextAvailableLocationIdList.size() - 1))];

    locationList[nextDragonLocationID - 1]->setLocationDragon(true);
    //move to the next location (random)
}

void combat(Player& player, Monster* monster) {
    /*
     * This is the combat function for realising the combat mechanism between the player and any monster.
     * The function takes the player object and monster object pointer in as arguments.
     * The player object is passed by reference as to update the player health realtime.
     */
    bool combatContinue = true;
    int combatCheckPlayer;
    int combatCheckMonster;
    int combatDamage;

    if (monster->getIsBoss()) {
        //In the case that the monster facing is the dragon, it will activate this block of function which allows
        //the special fire attack from the dragon before the normal combat sequence.
        cout << "Watch out, the dragon is spitting fire!!\n";
        int specialDamage = monster->getDamageSpFire() - player.getDefence();
        if (specialDamage < 0) { specialDamage = 0; }
        player.setAttribute(-specialDamage, PlayerAttribute::Health);
        //The player m,ust take this damage.
        cout << "Took " << to_string(specialDamage) << " damage straight away.\n";
        if (player.getHealth() <= 0) { combatContinue = false; }
        //In case the player dies just from this special attack.
        system("Pause");
    }

    if (player.getSpecialAttack()) {
        if (getConfirmation("Do you want to use the special attack Kame Hame Ha??")) {
            cout << "Ka Me Ka Me Ha!!!\n";
            monster->setAttribute(-10, MonsterAttribute::Health);
            if (monster->getHealth() <= 0) { combatContinue = false; }
            cout << "Made a instant 10 damage from the Kame Kame Ha!\n";
            player.setSpecialAttack(false);
        }
        system("Pause");
    }

    while (combatContinue) {
        
        if (player.getAttack() + 10 < monster->getAttack() + 2) {
            combatCheckPlayer = player.getAttack() + randomIntFromRange("2&10");
            combatCheckMonster = player.getAttack() +7 + randomIntFromRange("2&10");
            //In case there is no chance for the player at all
        }
        else
        {
            combatCheckPlayer = player.getAttack() + randomIntFromRange("2&10");
            combatCheckMonster = monster->getAttack() + randomIntFromRange("2&10");
        }

        
        //Initiate the combat logic sequence as instructed in the assignment brief.

        if (combatCheckPlayer > combatCheckMonster) {
            combatDamage = player.getDamage() - monster->getDefence();
            if (combatDamage <= 0) { combatDamage = 1; }
            //In special case of player damage = monster defence, the monster will take 1 damage anyway.
            monster->setAttribute(-combatDamage, MonsterAttribute::Health);
            cout << "Good Work !! Managed to attack the Monster!!\nMade " << combatDamage << " damage this round!\n";
        }
        if (combatCheckPlayer < combatCheckMonster) {
            combatDamage = monster->getDamage() - player.getDefence();
            if (combatDamage < 0) { combatDamage = 1; }
            //In special case of player damage = monster defence, the player will take 1 damage as well.
            player.setAttribute(-combatDamage, PlayerAttribute::Health);
            cout << "Shoot !! Got Caught!!\nTaken " << combatDamage << " damage this round!\n";
        }
        if ((player.getHealth() <= 0) || (monster->getHealth() <= 0)) { combatContinue = false; }
    }
}

void leaveCurrentLocation(Location*& currentLocation, Player* activePlayer,
    int oilCost, bool& endLocationCheck, int latLocation) {
    /*
     * This is the function that allows the player to make a way out of a cave.
     * The function is called either as the player decides to leave the location or the player is fleeing from a monster.
     * The function provides the available path according to the current/active location and ask for player's direction
     * input (E W N S). Upon user confirmation, it will shift the active location to the corresponding one on the selected
     * path - achieving the player moving mechanism of the game.
     */
    cout << "These are the available paths: \n"
        << currentLocation->getExitDir() << endl;
    string useSelectPath;
    vector <string> checkStringList = currentLocation->getExitDirList();
    bool leaveLocation = true;

    while (useSelectPath.empty()) {
        useSelectPath = getInput("Please select your path to the next location");
        for (char& inputChar : useSelectPath)
            inputChar = toupper(inputChar);
        //Converting user input all to upper case for validation purpose.
        if (count(checkStringList.begin(), checkStringList.end(), useSelectPath) == 0) {
            useSelectPath.clear();
            cout << "Invalid selection, please try again. \n";
            //If user input is not valid, clear input and ask for input again (back to the while loop).
        }
        else {
            if (!getConfirmation("Are you sure?"))
                //ask the player to confirm leaving.
                if (!getConfirmation("Make another selection?")) { leaveLocation = false; }
            //if player decided not to leave, allow the player to make another selection or back to the location.
                else { useSelectPath.clear(); }
            else {
                cout << "Heading down in the " + useSelectPath + " direction.." << endl;
                currentLocation->setLocationPlayer(false);
            }
        }
    }
    if (leaveLocation) {
        //if confirmed to leave, proceed with the switching of active location. Update player attribute on lantern oil.
        vector <int> nextLocationIdList = currentLocation->getNextLocationIdList();
        endLocationCheck = true;
        activePlayer->setInventoryBagUseLimit(latLocation, oilCost);
        endLocationCheck = true;
        int nextLocationID = currentLocation->getNextLocationIdList()[static_cast<int>(
            find(checkStringList.begin(), checkStringList.end(), useSelectPath) + 1 -
            checkStringList.begin()) - 1];
        cout << "Heading towards cave#" << nextLocationID << "\n\n";
        currentLocation = Location::getLocationObjectList()[nextLocationID - 1];
        currentLocation->setLocationPlayer(true);
    }
}

void examineCurrentLocation(Player& activePlayer, Location* activeLocation, int latLocation) {
    /*
     * This is the function that realise the game functionality of examine a location
     * Depending on random chance the player could find gold gem or provision through this function.
     * Each examine would cause the player two lantern oil.
     */
    string examineItemName;
    vector<string> availableItemList;
    int examineChance = randomIntFromRange("1&100");
    
    if (examineChance <= 20) {
        availableItemList = { "Provision" };
        examineItemName = availableItemList[randomIntFromRange("1&" + to_string(availableItemList.size())) - 1];
    }
    else if (examineChance >= 70) {
        availableItemList = { "Gold","Gem" };
        examineItemName = availableItemList[randomIntFromRange("1&" + to_string(availableItemList.size())) - 1];
    }

    if (!examineItemName.empty()) {
        cout << "\n\nYou have found a " + examineItemName << endl;
        if (getConfirmation("Do you wan to take this one into your bag?")) {
            activePlayer.pickItemUp(examineItemName);
        }
        else {
            cout << "\nOk.. Save it for later then.\n";
            activeLocation->setItemToList(examineItemName);
        }
    }
    else {
        cout << "\n\nWell maybe better luck next time..\n";
    }
    int examineCost = -2;
    activePlayer.setInventoryBagUseLimit(latLocation, examineCost);
}

void searchLocation(Player* activePlayer, Location* activeLocation) {
    /*
     * This is the custom/extension functionality of the game
     * In addition to the as required examination of location that a player could peform, the player could also
     * search the location. This will return, potentially, the hidden item in the given location. However, the search
     * action would cause the player 1-2 health in return.
     */
    int deductHealth = randomIntFromRange("1&2");
    cout << "Losing " << to_string(deductHealth) << " health in return..\n";
    activePlayer->setAttribute(-deductHealth, PlayerAttribute::Health);
    if (activeLocation->getItemOnSite() && activeLocation->getItemHidden()) {
        cout << "Looks like the luck is with you this time...\n";
        activeLocation->setLocationItemHidden(false);
        string tempItemName = activeLocation->getHiddenItemName();
        activeLocation->setItemToList(tempItemName);
        cout << "You have found a " << tempItemName << endl;
    }
    else { cout << "There is nothing here.... Sigh....\n"; }
}

void takeItemFromLocation(Player& activePlayer, Location* activeLocation) {
    /*
     * This is the function allowing the player to take any item that is available in the active location.
     * The function first identify if there are any item in the location that could be picked up.
     * If there is ask the player to select which one to pick up, the player could shortcut and select all.
     * If there are more than one of a item in the location, the function allows the player to pick up a certain amount.
     */
    vector <string> availableItemList = activeLocation->getAvailableItemList();
    vector <int> availableItemNumList = activeLocation->getAvailableItemNum();
    bool itemToPick = !(activeLocation->getLocationItemName() == "Nothing you could see");
    //Use the location item name as a identifier to determine if there is any item for the player to pick up.

    vector<string> validSelectionList;
    string stringNames;
    if (itemToPick) {
        /*
         * The following is to create the selection prompt and ask for player input. Validation is included.
         * The first two letters of the item is used as a selection code. All player input convert to lower case.
         */
        cout << "Here are the items that you can pick up:\n"
            << activeLocation->getLocationItemName() << endl;
        for (const string& eachName : availableItemList) {
            string tempCodeString = eachName.substr(0, 2);
            string tempString = "     " + eachName.substr(0, 2).append("|" + eachName);
            for (char& tempChar : tempCodeString) {
                tempChar = tolower(tempChar);
                //Convert the first two letters to lower case for the ease of validation later.
            }

            validSelectionList.emplace_back(tempCodeString);
            stringNames.append(tempString);

            tempString.clear();
            tempCodeString.clear();
        }

        validSelectionList.emplace_back("al");
        stringNames.append("     Al|All");
        //Have the option to type in al for taking all items in the active location.

        cout << "Now.... Please make you selection according to the following:\n" + stringNames << endl;

        string userSelection;
        int userSelectionInt;

        while (userSelection.empty()) {
            userSelection = getInput("Your selection: ");
            //Take the player selection.
            for (char& tempInputChar : userSelection) {
                tempInputChar = tolower(tempInputChar);
            }
            if (validSelectionList.end() != find(
                validSelectionList.begin(), validSelectionList.end(), userSelection)) {
                //Check if the user input matches to one of the available items.
                if (userSelection != "al") {
                    userSelectionInt = static_cast<int>(find(validSelectionList.begin(), validSelectionList.end(),
                        userSelection) - validSelectionList.begin());
                }
                else { userSelectionInt = -1; }

                //If that's the case then extract the location of the selection item as in the consumable name list.
            }
            else {
                userSelection.clear();
                cout << "Please check your selection and retry.\n";
            }
        }
        string selectedItemName = (userSelectionInt != -1) ? availableItemList[userSelectionInt] : "All";
        int allowableItemNumber = (userSelectionInt != -1) ? availableItemNumList[userSelectionInt] : 0;
        //Switch the setup between cases if a certain item is selected or the player wants to pick up all items.

        if (selectedItemName == "All") {
            // if all selected, picking up all items and update the player attribute if applicable.
            // Also checked is whether the player's bag is full.
            for (const string& eachName : availableItemList) {
                if (activePlayer.getBagFull()) { break; }
                int tempItemIndex = static_cast<int>(find(
                    availableItemList.begin(), availableItemList.end(), eachName)
                    - availableItemList.begin());
                int tempAllowableNumber = availableItemNumList[tempItemIndex];
                for (int numberCount = 0; numberCount < tempAllowableNumber; numberCount++) {
                    activePlayer.pickItemUp(eachName);
                    if (activePlayer.getBagFull()) { break; }
                    availableItemNumList[tempItemIndex] -= 1;
                }
                availableItemList.erase(availableItemList.begin() + tempItemIndex);
                availableItemNumList.erase(availableItemNumList.begin() + tempItemIndex);
            }
        }
        else {
            //if a specific item is being selected, proceed to picking up the item only. If there is more than 1 ask
            //the player how many to pick up. Also, the inventory bag is checked realtime in case it is full.
            int numSelection;
            if (allowableItemNumber > 1) {
                //deciding how many to pick up in this section.
                string numSelectionString;
                while (numSelectionString.empty()) {
                    numSelectionString = getInput("How many to pick up?");
                    bool check = true;
                    for (char eachChar : numSelectionString)
                        if (isdigit(eachChar) == false)
                            check = false;
                    if (check) {
                        numSelection = stoi(numSelectionString);
                        if (numSelection > allowableItemNumber) {
                            cout << "Exceeded the available amount! Please re-entre.\n";
                            numSelectionString.clear();
                        }
                    }
                    else {
                        cout << "Invalid input. Please re-entre.\n";
                        numSelectionString.clear();
                    }
                }
            }
            else { numSelection = allowableItemNumber; }

            for (int numberCount = 0; numberCount < numSelection; numberCount++) {
                //Performing the actual picking up item here.
                activePlayer.pickItemUp(selectedItemName);
                if (activePlayer.getBagFull()) { break; }
                availableItemNumList[userSelectionInt] -= 1;
                if (availableItemNumList[userSelectionInt] == 0) {
                    availableItemList.erase(availableItemList.begin() + userSelectionInt);
                    availableItemNumList.erase(availableItemNumList.begin() + userSelectionInt);
                }
            }
        }
        activeLocation->updateAvailableItem(availableItemList, availableItemNumList);
    }
    else {
        cout << "Nothing here to pick\n";
    }

}


void createList(const string& myFile, vector<string>& myVector) {
    /*
     * This function opens a file under file name "myFile" - contains the attribute data for each class object.
     * Storing each line as a single string into a vector - myVector.
     * This is the first step of building class object - importing the data.
     */
    fstream fileToRead;
    fileToRead.open(myFile, ios::in);
    if (fileToRead.is_open()) {
        string lineText;
        while (!fileToRead.eof()) {
            getline(fileToRead, lineText);
            myVector.push_back(lineText);
        }
        fileToRead.close();
    }
    else
        cout << "There is an error opening the file, please check" << endl;
}

void createClass(ClassType classType, const string& fileName) {
    /*
     * This is one main/essential function for the game - the universal class object creation tool.
     * With data of different classes all store in .txt file in the same manner, the same unpacking method could be used.
     * Then with the Enum Class defining the possible class types, a switch statement is used to change between
     * different constructors.
     */
    vector<string> tempStringVector;
    createList(fileName, tempStringVector);

    int numCount = 0;
    //First is to further decompose one line of data (one object) as a single string into a vector of data.
    for (auto tempString : tempStringVector) {
        numCount++;
        size_t indexText;
        vector<string> tempTokenList;
        const string delimiter = ";";
        //The same delimiter is used across all class definitions.
        while ((indexText = tempString.find(delimiter)) != string::npos) {
            tempTokenList.push_back(tempString.substr(0, indexText));
            tempString.erase(0, indexText + 1);
        }

        switch (classType) {
            /*
             * Switching between different cases to call different overload constructors. Play class is exempted.
             * This is because there is only one player.
             */
        case ClassType::ITEM: {
            Item newItem(tempTokenList);
            if (numCount == 1) { cout << "Fetching Items >>>>>> "; }

            break;
        }
        case ClassType::MONSTER: {
            Monster newMonster(tempTokenList);
            if (numCount == 1) { cout << "Cultivating Monsters >>>>>> "; }
            break;
        }
        case ClassType::LOCATION: {
            Location newLocation(tempTokenList);
            if (numCount == 1) { cout << "Building Game Locations >>>>>> "; }
            break;
        }
        case ClassType::Dragon: {
            //See overload constructor definition for the Dragon class
            Dragon newDragon({ tempTokenList.begin(),tempTokenList.end() - 1 },
                { tempTokenList[tempTokenList.size() - 1] });
            if (numCount == 1) { cout << "Cultivating Ultimate Monster >>>>>> "; }
            break;
        }
        default: {
            cout << "You should not see this message" << endl;
            break;
        }

        }
        tempString.clear();
        tempTokenList.clear();
    }
    cout << "Process Completed" << endl;
}

void showPlayerLocation() {
    //Function that loop through available locations to find the one with player in it - active location.
    for (Location* eachLocation : Location::getLocationObjectList())
        if (eachLocation->getPlayerOnSite())
            cout << eachLocation->getDetails() << endl;
}


void initialiseLocation(const vector <int>& numberList, vector <string> nameRefList,
    ClassType classType, vector<int> hiddenChanceList) {
    /*
     * This is the activation function for locations.
     * There are in total 20 locations/caves. When first created, none of them are assigned with a monster nor item.
     * This function takes the provided assignment details: number of each item/monster, the corresponding name.
     * and for items only, the corresponding hidden chance.
     *
     * Note that this function is packaged into the initialiseGameWorld function.
     */

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the Mersenne Twister pseudo-random generator

    vector <Location*> locationList = Location::getLocationObjectList();
    //Firstly have all location object pointers stored in a temporary vector.

    vector <int> locationIDList;
    for (Location* eachLocation : locationList)
        locationIDList.emplace_back(eachLocation->getLocationId());
    locationIDList.erase(locationIDList.begin());
    //Get a list of all created location IDs - {1,2,3,4,5,6...}
    shuffle(locationIDList.begin(), locationIDList.end(), gen);
    //use shuffle to randomly change the order of vector elements.
    int totalNumber = 0;
    for (int eachNumber : numberList)
        //Find the total number of item/monster to add, this will be the same as how many locations to be processed.
        totalNumber = totalNumber + eachNumber;

    vector <int> selectedLocationIDList = { locationIDList.begin(),locationIDList.begin() + totalNumber };

    //This is the selected location ID list, in random order.
    Location* tempLocation;
    int tempLocationID;
    int countCategory = 0;
    int checkCount = 0;
    for (int eachOne : numberList) {
        /*
         * This is the algorithm to go through the selected location list and add corresponding information to it.
         * For example, with 7 locations in total, the first 4 location add gold as item and the next 3 add gem.
         */
        for (int counter = 0; counter < eachOne; counter++) {
            checkCount++;
            tempLocationID = selectedLocationIDList[0];
            tempLocation = locationList[tempLocationID - 1];
            switch (classType) {
            case ClassType::MONSTER: {
                tempLocation->setLocationMonsterName(nameRefList[countCategory]);
                break;
            }
            case ClassType::ITEM: {
                if (randomIntFromRange("1&100") <= hiddenChanceList[countCategory])
                    tempLocation->setLocationItemHidden(true);
                tempLocation->setLocationItemName(nameRefList[countCategory]);
                break;
            }
                                //The following two types of location and dragon are not useful here.
            case ClassType::LOCATION: {
                cout << "You show not see this. There must be an error";
            }
            case ClassType::Dragon: {
                cout << "You show not see this as well. There must be an error";
            }
            }
            selectedLocationIDList.erase(selectedLocationIDList.begin());
        }
        countCategory++;
    }
}

void initialiseDragonLocation() {
    /*
     * This function  is to have the dragon assigned to a location.
     * This location is initially selected to be a empty cave with no monster in it.
     * However, depending on the game difficulty that the player selected, the dragon could be roaming in the caves.
     */
    vector <Location*> locationList = Location::getLocationObjectList();
    //Firstly have all location object pointers stored in a temporary vector.

    vector <int> locationAvailableIDList;
    //Find a location that doesn't have a monster in.

    for (Location* eachLocation : locationList)
        if ((!eachLocation->getMonsterOnSite()) && (eachLocation->getLocationId() != 1)) {
            locationAvailableIDList.emplace_back(eachLocation->getLocationId());
        }
    //Find all non-entry location IDs that doesn't gave a monster yet.

    Location* selectedLocation = locationList[locationAvailableIDList[
        randomIntFromRange("1&" + to_string(locationAvailableIDList.size())) - 1] - 1];

    cout << "\n\nDragon is assigned to location ID #" << 
        to_string(selectedLocation->getLocationId()) << "\n\n";
    //From the list find a random location as the selected dragon location.
    selectedLocation->setLocationDragon(true);

}


void initialiseGameWorld(GameDifficulty gameDifficulty) {
    /*
     * This is the critical function for the game as it activates the game world.
     * The function takes in the player-selected game difficulty and setup the game accordingly.
     * The game is set up randomly - not one play could be the same as a previous play of game.
     */
    vector <string> monsterNameRefList = { "Goblin","Hobgoblin","Ogre","Troll" };
    //These are the monsters (names) that could be assigned into locations.
    vector <string> itemNameRefList =
    { "Shards of Sword","Shards of Armour","Shards of Elite Sword","Shards of Elite Armour" };
    //These are the items that could be assigned into locations.

    vector <int> monsterNumberList;
    //How many of the monsters for each monster type are to be added.
    vector <int> itemNumberList;
    //How many items for each item type are to be added.
    vector <int> itemHiddenChance;
    //Whats is the chance that the item is hidden once added to a location.


    switch (gameDifficulty) {
        //Switching the game setup parametre according to the game difficulty.
    case GameDifficulty::Tourist:
        monsterNumberList = {8,2,2,2};
        itemNumberList = {5,5,4,4};
        itemHiddenChance = {20,20,20,20};
        remainArtefactCarrierCount = 4;
        break;
    case GameDifficulty::Average:
        monsterNumberList = {6,4,3,3};
        itemNumberList = {5,5,3,3};
        itemHiddenChance = {80,80,90,90};
        remainArtefactCarrierCount = 6;

        break;
    case GameDifficulty::Master:
        monsterNumberList = {5,5,4,4};
        itemNumberList = {4,4,3,3};
        itemHiddenChance = {90,90,95,95};
        remainArtefactCarrierCount = 8;

        break;
    case GameDifficulty::Hell:
        monsterNumberList = {3,4,6,5};
        itemNumberList = {3,3,2,2};
        itemHiddenChance = {99,99,99,99};
        remainArtefactCarrierCount = 11;

        break;
    }


    initialiseLocation(monsterNumberList, monsterNameRefList, ClassType::MONSTER);
    cout << "Finished summoning monsters!" << endl;
    initialiseDragonLocation();

    /*
     * The following part is optional but allows a artefact to be actually place in a location, instead of being carried.
     * These are all not required by the assignment but could add extra fun to the game.
     * There is a 5% chance that an artefact is not carried but in a location.
     * There is a 0% chance that two artefacts are not carried but in a locatioin - this could be changed later.
     */
    int artefactInLocationCheck = randomIntFromRange("1&100");
    int numArtefactInLocation = 0;
    int selectedArtefactIndex = 0;
    string artefactSelectRange = "0&";
    if (artefactInLocationCheck > 95) { numArtefactInLocation = 1; }
    else if (artefactInLocationCheck == 0) { numArtefactInLocation = 2; }
    if (numArtefactInLocation > 0) {
        for (int artefactCount = 0; artefactCount < numArtefactInLocation; artefactCount++) {
            artefactSelectRange = "0&";

            cout << to_string(inactiveArtefactNameList.size() - 1) << endl;
            artefactSelectRange.append(to_string(inactiveArtefactNameList.size() - 1));
            selectedArtefactIndex = randomIntFromRange(artefactSelectRange);
            itemNameRefList.emplace_back(inactiveArtefactNameList[selectedArtefactIndex]);
            inactiveArtefactNameList.erase(inactiveArtefactNameList.begin() + selectedArtefactIndex);

            itemNumberList.emplace_back(1);
            itemHiddenChance.emplace_back(3);
        }
    }

    initialiseLocation(itemNumberList, itemNameRefList,
        ClassType::ITEM, itemHiddenChance);
    cout << "Finished setting up the caves!" << endl;
}

Monster* encounterMonster(const string& monsterName) {
    /*
     * This is the function that activates a monster by deciding whether it has an item on it, and if yes which
     * item it has. The concept of activation is that for each location object it does not actually hold a monster in it
     * as the location become active (with player in it), the location monster is activated by the name and randomly
     * deciding whether it holds an item.
     */
    vector <string> monsterNameList = Monster::getMonsterNameList();
    int monsterIndex;
    monsterIndex = static_cast<int>(find(monsterNameList.begin(), monsterNameList.end(), monsterName)
        - monsterNameList.begin());
    Monster* tempMonster = Monster::getMonsterObjectList()[monsterIndex];
    //Firstly have the monster object ready. Search by the name

    /*
     * The task in the following is to classify whether the monster is a standard or could be artefact-carrying.
     * This is because throughout the game play there could 4 and only 4 artefacts being carried by Troll or Ogre.
     * This the where the global variables are used to track what artefacts are left to be picked up.
     */
    vector <string> availableItemNameList;
    bool canCarryArtefact = (monsterName == "Ogre" || monsterName == "Troll");
    if (canCarryArtefact) {
        remainArtefactCarrierCount -= 1;
    }

    int randomChance;
    if (canCarryArtefact && (!inactiveArtefactNameList.empty())) {
        availableItemNameList = inactiveArtefactNameList;
        //If the monster is Ogre or Troll and there are artefacts remaining to be carried. The selection would be form
        //the available artefact list (global variable.)
        randomChance = inactiveArtefactNameList.size() == remainArtefactCarrierCount ?
            1 : randomIntFromRange("1&100");
        //if the remaining artefact-carrying monster number is the same as remaining artefact number, must carry then.
    }
    else {
        availableItemNameList = { "Gem","Gold","Potion Flask" };
        //otherwise, carrying from a standard item list.
        randomChance = randomIntFromRange("1&100");
    }

    if (randomChance <= tempMonster->getItemChance()) {
        //Deciding whether the monster carries an item. If so, randomly select a item from the available list.
        stringstream s2;
        s2 << to_string(0) << "&" << to_string(availableItemNameList.size() - 1);
        int randomItemIndex = randomIntFromRange(s2.str());

        tempMonster->setCarryItemName(availableItemNameList[randomItemIndex]);
        //Assigning a random item to the monster.

        if (canCarryArtefact && (!inactiveArtefactNameList.empty())) {
            inactiveArtefactNameList.erase(inactiveArtefactNameList.begin() + randomItemIndex);
        }
        tempMonster->setCarryItem(true);
    }
    else {
        tempMonster->setCarryItemName("This one has no item");
        tempMonster->setCarryItem(false);
    }

    return tempMonster;
    //Returning the active monster into the game for player to interact with.
}



// ****************************Following are testing functions. Not for assessment.**************************************

void testRandomIntGenerator() {
    cout << "\n********************TEST STARTED**********************\n\n"
        << "For the first time testing, the range is set to [2-4]" << endl
        << "The generated number is " << to_string(randomIntFromRange("2&4")) << endl
        << "For the first time testing, the range is set to [12324-12399]" << endl
        << "The generated number is " << to_string(randomIntFromRange("12324&12399")) << endl
        << "\n********************TEST ENDED************************\n";
}

void testPlayerClass() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test the Player CLass~~~~~~~~~~~~\n"
        "~~~~~~~~~~~First is to build a default player~~~~~~~~~~\n";
    Player defaultPlayer;
    cout << defaultPlayer.getDetails() << endl;
    system("Pause");
    cout << "\n~~~~~~~~~~~Next is to build a active player~~~~~~~~~~\n"
        "~~~~~~~~~~~First to take the name input~~~~~~~~~~~~~~\n";

    string nameInput = getInput("Please entre a Player name:");
    Player playerActive(nameInput);
    cout << "~~~~~~~~~~~Then show the player details~~~~~~~~~~~~~~\n"
        << playerActive.getDetails() << endl;
    system("Pause");
    cout << "\n~~~~~~~~~~~Test individual assessor functions~~~~~~~~\n"
        "~~~~~~~~~~~Show Name~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "Name is: " << playerActive.getName() << endl
        << "~~~~~~~~~~~Show Health~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "Health is: " << to_string(playerActive.getHealth()) << endl
        << "~~~~~~~~~~~Show Damage~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "Damage is: " << to_string(playerActive.getDamage()) << endl
        << "~~~~~~~~~~~Show Bag~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "Bag includes: " << playerActive.getBagInformation() << endl
        << "\n********************TEST ENDED************************\n";
}

void testPlayerSetAttribute() {
    cout << "\n********************TEST STARTED**********************\n\n";
    cout << "~~~~~~~~~~~Testing the player set attribute function~~\n"
        "~~~Creating a default player and change the attribute~\n"
        "~~~~~Health->Attack->Damage->Defence->Luck->Multi~~~~~\n";
    system("Pause");
    cout << endl;
    Player playerTest;
    cout << playerTest.getDetails() << endl
        << "\nChanging health.\n";
    playerTest.setAttribute(-1, PlayerAttribute::Health);
    cout << playerTest.getDetails() << endl
        << "\nChanging attack.\n";
    playerTest.setAttribute(-1, PlayerAttribute::Attack);
    cout << playerTest.getDetails() << endl
        << "\nChanging damage.\n";
    playerTest.setAttribute(-1, PlayerAttribute::Damage);
    cout << playerTest.getDetails() << endl
        << "\nChanging defence.\n";
    playerTest.setAttribute(-1, PlayerAttribute::Defence);
    cout << playerTest.getDetails() << endl
        << "\nChanging luck.\n";
    playerTest.setAttribute(-1, PlayerAttribute::Luck);
    cout << playerTest.getDetails() << endl
        << "\nChanging Multi.\n";
    playerTest.setAttribute(-1, PlayerAttribute::Multi);
    cout << playerTest.getDetails() << endl
        << "\nChanging NA.\n";
    playerTest.setAttribute(-1, PlayerAttribute::NA);
    cout << playerTest.getDetails() << endl
        << "\n********************TEST ENDED************************\n";
}

void testPlayerPickUpItem() {
    cout << "\n********************TEST STARTED**********************\n\n"
        << "~~~~~~~~~~Testing picking up items into the bag~~~~~~~~~\n"
        "~~~~~~~~~~Create a default player first~~~~~~~~~~~~~~~~~\n";
    Player playerTest;
    cout << playerTest.getDetails() << endl
        << playerTest.getBagInformation() << endl;
    system("Pause");

    cout << "\n~~~~~~~~~~Create all items using the txt file~~~~~~~~~~\n";
    createClass(ClassType::ITEM, "Items.txt");

    cout << "\n~~~~~~~~~~Picking up items one at a time now~~~~~~~~~~~\n"
        << "~~~~~~~~~~Test the player to pick up a Map~~~~~~~~~~~~~\n";
    playerTest.pickItemUp("Map");
    cout << playerTest.getBagInformation() << endl;

    system("Pause");

    cout << "\n~~~~~~~~~~Test the player to pick up a Sword~~~~~~~~~~~\n";
    playerTest.pickItemUp("Sword");
    cout << playerTest.getBagInformation() << endl
        << "~~~~~~~~~~Auto-updated player attribute~~~~~~~~~~~~~~~~\n"
        << playerTest.getDetails();
    system("Pause");

    cout << "\n~~~~~~~~~~Test the player to pick up a Sword again~~~~~\n";
    playerTest.pickItemUp("Sword");
    cout << playerTest.getBagInformation() << endl
        << "~~~~~~~~~~Auto-updated player attribute~~~~~~~~~~~~~~~~\n"
        << playerTest.getDetails();
    system("Pause");

    cout << "\n~~~~~~~~~~Test the player to pick up a Potion Flask~~~~\n";
    playerTest.pickItemUp("Potion Flask");
    cout << playerTest.getBagInformation() << endl;
    system("Pause");

    cout << "\n~~~~~~~~Test the player to pick up a Potion Flask Again\n";
    playerTest.pickItemUp("Potion Flask");
    cout << playerTest.getBagInformation() << endl;
    system("Pause");

    cout << "\n~~~~~~~~Test the player to pick up a Gold 14 times~~~~~~\n";
    for (int count = 0; count < 12; count++) {
        playerTest.pickItemUp("Gold");
        cout << playerTest.getBagInformation() << endl;
    }

    cout << "\n~~~~~~~~~~Test the player to pick up a Sword again~~~~~\n";
    playerTest.pickItemUp("Sword");
    cout << playerTest.getBagInformation() << endl
        << "~~~~~~~~~~Auto-updated player attribute~~~~~~~~~~~~~~~~\n"
        << playerTest.getDetails();
    system("Pause");

    cout << "\n~~~~~~~~Test the player to pick up a Gold 4 times~~~~~~\n";
    for (int count = 0; count < 4; count++) {
        playerTest.pickItemUp("Gold");
        cout << playerTest.getBagInformation() << endl;
    }

    cout << "~~~~~~~~~Show the second item in the bag~~~~~~~~~~~~~~~\n"
        << playerTest.getInventoryBag()[1]->getDetails() << endl
        << "\n********************TEST ENDED************************\n";

    playerTest.dropItem();
}

void testPlayerUseConsumable() {
    cout << "\n********************TEST STARTED**********************\n\n"
        << "~~~~~~~~~Testing the player use consumable item~~~~~~~~\n"
        "~~~~~~~~~This is done by creating a default player~~~~~\n";
    Player playerTest;
    cout << playerTest.getDetails();
    system("Pause");
    cout << "\n~~~~~~~~~~Create all items using the txt file~~~~~~~~~~\n";

    createClass(ClassType::ITEM, "Items.txt");
    system("Pause");

    cout << "~Adding Map, Sword, Provision, and Potion Flask to bag~\n";

    vector <string> addItemNameList = { "Map","Sword","Provision","Potion Flask" };
    for (const string& itemName : addItemNameList)
        playerTest.pickItemUp(itemName);
    cout << "\n~~~~~~~~~~~Confirmed items added~~~~~~~~~~~~~~~~~~~~~~~\n"
        << playerTest.getDetails();
    system("Pause");

    cout << "\n~Now we are showing consumable item name from the bag~\n";
    string stringNames = "These are the available consumable item in the bag:\n";
    for (const string& nameString : playerTest.getBagItemNameList("C")) {
        string tempString = "\t" + nameString.substr(0, 2) + "|" + nameString;
        stringNames.append(tempString);
        tempString.clear();
    }
    cout << stringNames << "\n\n";

    cout << "~~~Now we are testing use a consumable item from the bag~\n";
    system("Pause");

    while (getConfirmation("Use consumable?")) {
        playerTest.useItemConsumable();
        cout << playerTest.getDetails() << endl;
    }
    cout << playerTest.getBagInformation() << "\n\n";

    cout << "\n********************TEST ENDED************************\n";
}

void testItemClass() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test the Item CLass~~~~~~~~~~~\n"
        "~~~~~~~~~~~First is to build a default item~~~~~~~~~\n";
    Item defaultItem;
    cout << defaultItem.getDetails();
    system("Pause");

    cout << "\n~~~~~~~~~~Now to test importing items from txt file~\n";
    createClass(ClassType::ITEM, "Items.txt");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    system("Pause");


    cout << "\n~~~~~~~~~~Show item information one by one~~~~~~~~~~\n";
    for (auto& item : Item::getItemObjectList()) {
        cout << "Item #" << to_string(item->getItemId()) << endl;
        cout << item->getDetails() << endl;
    }
    system("Pause");

    cout << "~~~~~~~~~~Now to test some of the assessor functions~\n";
    cout << "~~~~~~~~~~Take lamp as the demonstration item~~~~~~~~\n";
    Item* tempItem = Item::getItemObjectList()[1];
    cout << tempItem->getDetails() << endl;
    cout << "~~~~~~~~~~Show name~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempItem->getName() << endl;
    cout << "~~~~~~~~~~Show type~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempItem->getType() << endl;
    cout << "~~~~~~~~~~Show use type~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempItem->getUseType() << endl;
    cout << "~~~~~~~~~~Show use limit~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << to_string(tempItem->getUseLimit()) << endl;
    cout << "\n~~~~~~~~~~Now to test the mutator functions~~~~~~~~~~\n";
    cout << "~~~~~~~~~~Change use limit~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    tempItem->setUseLimit(-10);
    cout << "~~~~~~~~~~show updated use limit~~~~~~~~~~~~~~~~~~~~~\n";
    cout << to_string(tempItem->getUseLimit()) << endl;


    cout << "\n********************TEST ENDED************************\n";
}

void testMonsterClass() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test the Monster CLass~~~~~~~~~~~\n"
        "~~~~~~~~~~~First is to build a default item~~~~~~~~~\n";

    Monster defaultMonster;
    cout << defaultMonster.getDetails();
    system("Pause");

    cout << "\n~~~~~~~~~~Now to test importing items from txt file~\n";
    createClass(ClassType::MONSTER, "Monster.txt");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    system("Pause");


    cout << "\n~~~~~~~~~~Now to show the monster information~~~~~\n";
    for (Monster* eachMonster : Monster::getMonsterObjectList())
        cout << eachMonster->getDetails() << endl;
    system("Pause");


    cout << "~~~~~~~~~~Now to test some of the assessor functions~\n";
    cout << "~~~~~~~~~~Take Goblin as the demonstration monster~~~\n";
    Monster* tempMonster = Monster::getMonsterObjectList()[0];
    cout << tempMonster->getDetails() << endl;
    cout << "~~~~~~~~~~Show name~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempMonster->getName() << endl;
    cout << "~~~~~~~~~~Show level~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << to_string(tempMonster->getLevel()) << endl;
    cout << "~~~~~~~~~~Show health~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << to_string(tempMonster->getHealth()) << endl;
    cout << "~~~~~~~~~~Show damage~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << to_string(tempMonster->getDamage()) << endl;
    cout << "~~~~~~~~~~Show carried item~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempMonster->getCarryItemName() << endl;
    cout << "\n~~~~~~~~~~Now to test the mutator functions~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~Monster before changes~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempMonster->getDetails() << endl;
    cout << "~~~~~~~~~~Decrease health/attack/damage by 1~~~~~~~~~~\n";
    tempMonster->setAttribute(-1, MonsterAttribute::Health);
    tempMonster->setAttribute(-1, MonsterAttribute::Attack);
    tempMonster->setAttribute(-1, MonsterAttribute::Damage);
    cout << "~~~~~~~~~~Show updated Goblin~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << tempMonster->getDetails() << endl;


    cout << "\n********************TEST ENDED************************\n";
}

void testMonsterReset() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to resetting a monster~~~~~~~~~~~\n"
        "~~~~~~~~~~~First is to build a Goblin~~~~~~~~~~~~~~~\n\n";

    vector <string> testMonsterInfoList;
    createList("Monster_test.txt", testMonsterInfoList);
    size_t indexText;
    string tempString = testMonsterInfoList[0];
    vector<string> tempTokenList;
    const string delimiter = ";";
    while ((indexText = tempString.find(delimiter)) != string::npos) {
        tempTokenList.push_back(tempString.substr(0, indexText));
        //cout << tempTokenList.back() << endl;
        tempString.erase(0, indexText + 1);
    }
    Monster monsterTest(tempTokenList);

    cout << "\n~~~~~~~~~~~Show original Goblin~~~~~~~~~~~~~~~~~~~~~\n";
    cout << monsterTest.getDetails() << endl;
    cout << "~~~~~~~~~~~Resetting the Goblin~~~~~~~~~~~~~~~~~~~~~\n";
    monsterTest.monsterResetAfterCombat();
    cout << "~~~~~~~~~~~Now show the refreshed the Goblin~~~~~~~~\n";
    cout << monsterTest.getDetails() << endl;

    cout << "\n********************TEST ENDED************************\n";

}

void testEncounterMonster() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test the monster activation~~~~~\n"
        "~~~~~~~~~~~Upon player entering a location~~~~~~~~~~~\n\n";

    cout << "~~~~~~~~~~~Testing the Goblin~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~Original Goblin~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    createClass(ClassType::MONSTER, "Monster.txt");
    cout << Monster::getMonsterObjectList()[0]->getDetails() << endl;
    system("Pause");

    cout << "~~~~~~~~~~~Activating Goblin~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Monster* monster1 = encounterMonster("Goblin");
    cout << monster1->getDetails() << endl;
    system("Pause");

    cout << "~~~~~~~~~~~Resetting Goblin~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    monster1->monsterResetAfterCombat();
    cout << monster1->getDetails() << endl;
    system("Pause");


    cout << "~~~~~~~~~~~Testing the Ogre~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~Original Ogre~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << Monster::getMonsterObjectList()[1]->getDetails() << endl;
    system("Pause");

    cout << "~~~~~~~~~~~Activating Ogre~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    Monster* monster2 = encounterMonster("Ogre");
    cout << monster2->getDetails() << endl;
    system("Pause");

    cout << "~~~~~~~~~~~Resetting Ogre~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    monster2->monsterResetAfterCombat();
    cout << monster2->getDetails() << endl;

    cout << "\n********************TEST ENDED************************\n";

}


void testLocationClass() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test the location CLass~~~~~~~~~\n"
        "~~~~~~~~~~~First is to build a default location~~~~~~~\n";
    Location defaultLocation;
    cout << "~~~~~~~~~~~Show location details~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << defaultLocation.getDetails();
    system("Pause");


    cout << "\n~~~~~~~~~~~Now to test building every location object~\n";
    createClass(ClassType::LOCATION, "Location.txt");
    for (Location* eachLocation : Location::getLocationObjectList())
        cout << eachLocation->getDetails();
    system("Pause");


    cout << "\n~~~~~~~~~Test two assessor functions for demonstration~~\n";
    cout << "~~~~~~~~~~~Take the entry location as test case~~~~~~~~~\n";
    Location* testLocation = Location::getLocationObjectList()[0];
    cout << "~~~~~~~~~~~Show name~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << testLocation->getName() << endl;
    cout << "~~~~~~~~~~~Show description~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << testLocation->getDescription() << endl;

    cout << "\n~~~~~~~~~Test two mutator functions~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "~~~~~~~~~~~Set Monster~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    testLocation->setLocationMonsterName("Goblin");
    if (testLocation->getMonsterOnSite())
        cout << testLocation->getLocationMonsterName() << endl;
    cout << "~~~~~~~~~~~Set Item~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    testLocation->setLocationItemName("Gold");
    if (testLocation->getItemOnSite())
        cout << testLocation->getLocationItemName() << endl;

    cout << "\n********************TEST ENDED************************\n";

}


void testInitialiseLocation() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test initialising locations~~~~~\n"
        "~~~~~~~~~~~First is to build a all location~~~~~~~~~~~\n";

    //createClass(ClassType::LOCATION, "Location.txt");
    system("Pause");


    cout << "~~~~~~~~~~~Assigning 15 monsters to random locations~~\n"
        "~~~~~~~~~~~6Gob 4Hob 3Og 2Tr~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    vector <int> monsterNumberList = { 6,4,3,2 };
    vector <string> monsterNameRefList = { "Goblin","Hobgoblin","Ogre","Troll" };
    initialiseLocation(monsterNumberList, monsterNameRefList, ClassType::MONSTER);
    system("Pause");

    cout << "~~~~~~~~~~~Assigning 14 items to random locations~~~~~\n"
        "~~~~~~~~~~~5Gem 5Gold 4Artefacts~~~~~~~~~~~~~~~~~~~~~~\n";
    vector <int> itemNumberList = { 5,5,1,1,1,1 };
    vector <string> itemNameRefList = { "Gem","Gold","Krang's Battle Axe","Krang's Chainmail","Boots of Speed",
                                        "Elixir Maxima" };
    system("Pause");

    initialiseLocation(itemNumberList, itemNameRefList, ClassType::ITEM);
    cout << "~~~~~~~~~~~Show all locations~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "~~~~~~~~~~~With now randomly allocated item/monsters~~\n";
    vector <Location*> locationList = Location::getLocationObjectList();
    cout << "\nFollowing are the locations information" << endl;
    int itemCount = 0;
    int monsterCount = 0;
    for (Location* eachLocation : locationList) {
        cout << "\n" << eachLocation->getDetails();
        if (eachLocation->getPlayerOnSite()) {
            cout << "The current location" << endl;
        }
        if (eachLocation->getMonsterOnSite()) {
            cout << "The encountered monster is: " << eachLocation->getLocationMonsterName() << endl;
            monsterCount++;
        }
        if (eachLocation->getItemOnSite()) {
            cout << "The available item is: " << eachLocation->getLocationItemName() << endl;
            itemCount++;
        }
    }
    system("Pause");

    cout << "\nIn summary, there are " << to_string(monsterCount) <<
        " monsters and " << to_string(itemCount) <<
        " items located in random locations" << endl;

    cout << "\n\nYou current location information is as below: \n";
    showPlayerLocation();
    cout << "\n********************TEST ENDED************************\n";
}


void testInitialiseGameWorld() {
    createClass(ClassType::LOCATION, "Location.txt");
    createClass(ClassType::MONSTER, "Monster.txt");
    GameDifficulty gameSet = GameDifficulty::Tourist;
    initialiseGameWorld(gameSet);
    cout << "~~~~~~~~~~~Show all locations~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        "~~~~~~~~~~~With now randomly allocated item/monsters~~\n";
    vector <Location*> locationList = Location::getLocationObjectList();
    cout << "\nFollowing are the locations information" << endl;
    int itemCount = 0;
    int monsterCount = 0;
    Monster* tempMonster;
    for (Location* eachLocation : locationList) {
        cout << "\n" << eachLocation->getDetails();
        if (eachLocation->getPlayerOnSite()) {
            cout << "The current location" << endl;
        }
        if (eachLocation->getMonsterOnSite()) {
            cout << "The encountered monster is: " << eachLocation->getLocationMonsterName() << endl;
            monsterCount++;
            tempMonster = encounterMonster(eachLocation->getLocationMonsterName());
            cout << tempMonster->getDetails() << endl;
            tempMonster->monsterResetAfterCombat();
        }
        if (eachLocation->getItemOnSite()) {
            cout << "The available item is: " << eachLocation->getHiddenItemName() << endl;
            if (eachLocation->getItemHidden()) {
                cout << "This item is hidden in the location" << endl;
            }
            itemCount++;
        }
    }
    system("Pause");

    cout << "\nIn summary, there are " << to_string(monsterCount) <<
        " monsters and " << to_string(itemCount) <<
        " items located in random locations" << endl;

    cout << "\n\nYou current location information is as below: \n";
    showPlayerLocation();
}

void testDragonClass() {
    cout << "\n********************TEST STARTED**********************\n\n"
        "~~~~~~~~~~~This is to test building a dragon~~~~~~~~~~\n";
    createClass(ClassType::Dragon, "Dragon.txt");
    cout << Dragon::getDragonObjectList()[0]->getDetails() << endl;
    cout << "The special attack of fire damage is: " <<
        to_string(Dragon::getDragonObjectList()[0]->getDamageSpFire()) << endl;
    cout << "\n********************TEST ENDED************************\n";
}

int startGame() {
    /*
    * This is the function to display game information at the start - description and instruction on how to play.
    * For now, for testing stage of prototypes, this is used to display testing instructions.
    */

    displayTextData("DragonSymbol.txt");
    system("Pause");
    cout << "			Displaying General Information About The Game\n\n\n";
    displayTextData("About.txt");
    system("Pause");
    system("CLS");

    cout << "=============This is the test session for the game Treature Cavern of Dragon================================\n\n"
        << "=============Each class and setting up function will be tested==============================================\n"
        << "=============The game will be tested in sections due to the design of class objects and storage=============\n\n\n";
    cout << "=============You have below options=========================================================================\n"
        "   1|PlayerClass   2|ItemClass   3|MonsterClass   4|LocationClass  \n";

    string userInput;
    int userInputInt = 0;
    vector <string> checkStringList = { "1","2","3","4","5" };
    //The list of valid inputs.
    while (userInput.empty()) {
        userInput = getInput("Please select which section you would like to test: ");
        if (count(checkStringList.begin(), checkStringList.end(), userInput) == 0) {
            userInput.clear();
            cout << "Invalid selection, please try again. \n";
            //If user input is not valid, clear input and ask for input again (back to the while loop).
        }
        else
            userInputInt = stoi(userInput);
    }

    return userInputInt;
}
