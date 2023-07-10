/**************************************************
	Project: FIT1048 Assignment 4 - Major Project B
	Project Name: Treasure Caverns of Doom
	Author: Zecan Liu
	Purpose: Player Class Definition File
	Date: 20221030
**************************************************/


#include "Player.h"

//Default constructor
Player::Player() {
    /*
     *This is default constructor with default attributes to 0 and no name assigned.
     *This is not intended to be used anywhere in the code.
     */
    name = "Testing Only";
    health = 0;
    attack = 0;
    defence = 0;
    damage = 0;
    luck = 0;
    inventoryBag = {};
    inventoryBagUseLimit = {};
    bagFull = false;
    specialAttackKHH = false;
}

//The overload constructor
Player::Player(string nameInput) {
    /*
     *Generate the player object with a given name.
     *The player attributes are generated according to random number.
     */
    name = std::move(nameInput);
    //Generate the two random-based attributes using custom-made random number function.
    health = static_cast<float>(randomIntFromRange("4&12")) + 12;
    luck = static_cast<float>(randomIntFromRange("2&6")) + 6;
    //Define the other related attributes.
    attack = round(health / 6);
    defence = round(attack / 2);
    damage = round(attack / 3);
    //All attributes were defined to a double format for using rounding.
    inventoryBag = {};
    inventoryBagUseLimit = {};
    /*
     * Apart from the inventory bag which store the item pointer at its slots (each element).
     * The functionality of the bag is further explored by adding storage amount to each slot - the use limit.
     * For example, for gold, each player may store up to 6 gold in one slot. This elevates the game play experience.
     */
    bagFull = false;
    specialAttackKHH = false;
}

//Default destructor for now
Player::~Player() = default;

//The Accessor function for retrieving player information
string Player::getName() {
    return name;
}
int Player::getHealth() const {
    return int(health);
}
int Player::getLuck() const {
    return int(luck);
}
int Player::getAttack() const {
    return int(attack);
}
int Player::getDefence() const {
    return int(defence);
}
int Player::getDamage() const {
    return int(damage);
}

bool Player::getBagFull() const {
    return bagFull;
}

bool Player::getSpecialAttack() const {
    return specialAttackKHH;
}

vector <Item*> Player::getInventoryBag() {
    return inventoryBag;
}
vector <int> Player::getInventoryBagUseLimit() {
    return inventoryBagUseLimit;
}
string Player::getDetails() {
    //Display the player informationa and status
    string topLayer = "==================================================================\n"
                      "======================Player Status Summary=======================";
    string nameInfo = "\n\nName: " + getName();
    string attributeInfo = "\nHealth: " + to_string(int(getHealth())) + "\t|\tLuck: " + to_string(int(getLuck()))
        + "   \t|" + "\nAttack: " + to_string(int(getAttack())) + "\t|\tDefence: " +
        to_string(int(getDefence())) + "\t|\tDamage: " + to_string(int(getDamage()));
    string inventoryBagInfo = "\n" + getBagInformation()+"\n";
    string botLayer = "\n=================================================================";

    stringstream playerInfo;
    playerInfo << topLayer << nameInfo << attributeInfo << inventoryBagInfo << botLayer << "\n";

    return playerInfo.str();
}

string Player::getBagInformation() {
    /*
     * This is to obtain the inventory bad information;
     * Showing all available item names in the bag as one string for printing.
     */
    string returnBagString = "Inventory Bag: |";
    string tempItemString;
    int itemNum = 0;
    if (!inventoryBag.empty()) {
        for (auto item : inventoryBag) {
            itemNum++;
            tempItemString.clear();
            tempItemString = " Item#" + to_string(itemNum) + " [" +
                to_string(getInventoryBagUseLimit()[itemNum - 1]) + "] " + item->getName() + " |";
            returnBagString.append(tempItemString);
        }
    }
    else {
        returnBagString = "The bag is currently empty";
    }
    return returnBagString;
}

//Mutator functions to change player attributes

void Player::setAttribute(int intUpdateAmount, PlayerAttribute type) {
    /*
     * This function that packs all functionality of mutators into one to help making more effective operation.
     * The function takes two arguments as the updateAmount - this is value to be added to the attribute.
     * And type - this is to tell the function which attribute to update, set to an Enum class for clarification.
     * The function layout is rather complex while utilising recursion because the attribute change due to using
     * provision is also considered/implemented to this function. This is also related to the Item definition txt file
     * in which certain definition/marker used for consumable items.
     *
     * Testing on changing each attribute is done with a dedicated test function.
     */
    string userInput;
    auto updateAmount = static_cast<float>(intUpdateAmount);
    //The user input is only required in case Multi - Potion flask
    switch (type) {
    case PlayerAttribute::Health: {
        //This is the case of using provision, identified by a -999 marker.
        if (updateAmount == -999) {
            //Generate random health restoration from 5-10.
            updateAmount = static_cast<float>(randomIntFromRange("5&10"));
        }
        //Update the corresponding attribute.
        health = health + float(updateAmount);
        break;
    }
    case PlayerAttribute::Attack: {
        attack = attack + updateAmount;
        break;
    }
    case PlayerAttribute::Damage: {
        damage = damage + updateAmount;
        break;
    }
    case PlayerAttribute::Defence: {
        defence = defence + updateAmount;
        break;
    }
    case PlayerAttribute::Luck: {
        luck = luck + updateAmount;
        break;
    }
    case PlayerAttribute::Multi: {
        /*
         * This Multi type is defined specifically for player using a Potion Flask.
         * This is defined that after selecting to use a Potion Flask, the player must select an attribute that he/she
         * intend to affect and the system will automatically generate an affect amount from the provided range.
         */
        float possibleAffectLvl[6] = { -4,-3,-2,2,3,4 };
        //Update amount is a random element of the possible amount list. Here we have 4.
        updateAmount = possibleAffectLvl[randomIntFromRange("0&5")];

        while (userInput.empty()) {
            userInput = getInput("Please made a selection from the following: \n"
                "H|Health\tA|Attack\tDa|Damage\tDe|Defence\tL|Luck \n"
                "Selection: ");
            /*
             * Ask the player to make a selection from all possible attribute - involves the use of a custom getInput
             * function. This is explained in the FunctionCollection definition file.
             */
            for (char& inputChar : userInput)
                inputChar = tolower(inputChar);
            //Converting user input all to lower case for validation purpose.
            vector <string> checkStringList = { "h","a","da","de","l" };
            //The list of valid inputs.

            if (count(checkStringList.begin(), checkStringList.end(), userInput) == 0) {
                userInput.clear();
                cout << "Invalid selection, please try again. \n";
                //If user input is not valid, clear input and ask for input again (back to the while loop).
            }
            else {
                //When a valid input is detected, set attribute accordingly.
                cout << to_string(updateAmount) << " to the selected attribute.\n";
                if (userInput == "h") {
                    setAttribute(int(updateAmount), PlayerAttribute::Health);
                    //Utilising recursion here.
                }
                if (userInput == "a") {
                    setAttribute(int(updateAmount), PlayerAttribute::Attack);
                }
                if (userInput == "da") {
                    setAttribute(int(updateAmount), PlayerAttribute::Damage);
                }
                if (userInput == "de") {
                    setAttribute(int(updateAmount), PlayerAttribute::Defence);
                }
                if (userInput == "l") {
                    setAttribute(int(updateAmount), PlayerAttribute::Luck);
                }
            }
        }
        break;
    }
    case PlayerAttribute::NA: {
        //This is the type for non-attribute-affecting item, e.g. map.
        cout << "Do nothing and you should not see this\n";
        break;
    }
    }
}

void Player::setInventoryBagUseLimit(int location, int& updateAmount) {
    //This is to update the inventory bag amount (use amount) at each bag slot.
    //For example, adding one gold to slot 1 with originally three golds stored there. Making it 4 at the end.
    inventoryBagUseLimit[location] = inventoryBagUseLimit[location] + updateAmount;
}

void Player::setBagFull(bool check) {
    bagFull = check;
}

void Player::setSpecialAttack(bool check) {
    specialAttackKHH = check;
}

//Game play functions

void Player::pickItemUp(const string& itemName) {
    /*
     * This is a function of the game play mechanism - picking up item into player's inventory bag.
     * This function is designed to pick up one item at a time.
     * If the item has an effect on player's attribute (such as a sword), the updating attribute will be done as part
     * of the picking up procedure.
     * The inventory bag is automatically updated according to the specific item being added to into the bag.
     */
    vector <Item*> currentItemList = Item::getItemObjectList();
    vector <string> currentItemNameList = Item::getItemNameList();

    //Creating the actual item object list (pointers) and a corresponding list of item names only for reference purpose.

    int itemLocator = static_cast<int>(find(currentItemNameList.begin(), currentItemNameList.end(), itemName) -
        currentItemNameList.begin());

    Item* tempItem = currentItemList[itemLocator];
    //Locate the item object using the input argument "item name" and the reference list of all possible item Names.

    cout << "Picking up " << tempItem->getName() << endl;

    if (!tempItem->getIsBooster()) {
        /*
         * As for the unique design fo the game, there are actual item and booster item - only update the player attribute
         * Boosters are not physically added into the bag.
         */
        setBagFull(false);
        vector<string> currentBagItemNameList = getBagItemNameList("A");
        itemPickUpCheckLoop(currentBagItemNameList, tempItem);
        //This a dedicated function created to check and update player bag. See details in its own function block.
    }

    if (!getBagFull() || tempItem->getIsBooster()) {
        if (tempItem->getAffectAttribute()) {
            //Check if this item affect attributes.
            if (tempItem->getIsConsumable()) {
                //Check if this item is a consumable.
                cout << "This is a consumable item, you can use it later" << endl;
            }
            else {
                //Updating the player attribute automatically.
                cout << "Updating " << Item::getRefAttributeList()[static_cast<int>(tempItem->getAffectAttributeName())] << endl;
                Player::setAttribute(tempItem->getAffectAttributeLvl(), tempItem->getAffectAttributeName());
            }
        }
        else {
            //For case the item has no impact on the attribute
            cout << "This item is now in the bag, and it doesnt not affect the current attributes." << endl;
        }
    }
    else {
        cout << "Unfortunately, the bag is full for this item. You need to make space to take more...\n";
    }
}

void Player::itemPickUpCheckLoop(vector <string> myVector, Item* tempItem) {
    /*
     * This is the function for physically adding an item into the bag
     * Mindful that the function is made complicated due to the design of inventory bag, there are so many slots for
     * items and each slot can hold a certain number of a given item. This is however different among items.
     */
    string tempItemName = tempItem->getName();

    if (inventoryBag.size() == 12) {
        // Currently, it is only set to have 12 slots in the bag
        vector<int> indices;
        int position = 0;
        int totalUseInBag = 0;
        int counter = 0;
        for (auto& eachItem : inventoryBag) {
            if (eachItem->getName() == tempItemName) {
                totalUseInBag += inventoryBagUseLimit[position];
                counter++;
            }
            position++;
        }
        if (totalUseInBag >= ((tempItem->getUseLimit()) * counter)) {
            setBagFull(true);
        }
    }

    if (!getBagFull()) {
        int itemLocation = static_cast<int>(find(myVector.begin(), myVector.end(),
            tempItemName) - myVector.begin());
        /*
         * The following is to determine whether the item is to take a new slot in the bag
         * or to update an existing slot by add one more item to that slot. This is determined by the slot amount
         * cap for that item.
         */
        if (itemLocation != myVector.size() &&
            (getInventoryBagUseLimit()[itemLocation]) < tempItem->getBagAmountCap()) {
            int updateAmount = tempItem->getUseLimit();
            setInventoryBagUseLimit(itemLocation, updateAmount);
        }
        else if (itemLocation < myVector.size()) {
            vector <string> tempSubVector(myVector.begin() + itemLocation + 1, myVector.end());
            if (static_cast<int>(find(tempSubVector.begin(), tempSubVector.end(),
                tempItemName) - tempSubVector.begin()) != tempSubVector.size()) {
                myVector[itemLocation] = myVector[itemLocation] + "*";
                itemPickUpCheckLoop(myVector, tempItem);
            }
            else {
                inventoryBag.emplace_back(tempItem);
                inventoryBagUseLimit.emplace_back(tempItem->getUseLimit());
            }
        }
        else {
            inventoryBag.emplace_back(tempItem);
            inventoryBagUseLimit.emplace_back(tempItem->getUseLimit());
        }
        tempItem->resetUseLimit();
    }

}

void Player::dropItem() {
    /*
     * This is the function that allows the player to drop item from the bag.
     * It takes user input for selection of the item to drop in the bag, and it also takes an user input amount for
     * how many of that item to drop. This is particularly for case of gold and gem, allowing player to drop a certain
     * number of a selected item.
     */
    string itemName = getUserSelectionFromBag("Please make you selection: ", "Drop");
    //Showing all items in the bag that could be dropped. Map and lantern are not allowed to be dropped.

    vector <Item*> currentItemList = Item::getItemObjectList();
    vector <string> currentItemNameList = Item::getItemNameList();
    //Creating the actual item object list (pointers) and a corresponding list of item names only for reference purpose.

    int itemLocator = static_cast<int>(find(currentItemNameList.begin(),
        currentItemNameList.end(), itemName) - currentItemNameList.begin());
    Item* tempItem = currentItemList[itemLocator];
    //Get pointer to that actual item that player wants to drop

    vector<string> currentBagItemNameList = getBagItemNameList("A");

    auto itemLocation = find(currentBagItemNameList.begin(),
        currentBagItemNameList.end(), itemName);
    vector <int> tempItemBagLocation;
    //This part is to find all occurrence of that item in the bag. For example: gold on slot 1,3, and 5.
    while (itemLocation != currentBagItemNameList.end()) {
        tempItemBagLocation.emplace_back(static_cast<int>(itemLocation - currentBagItemNameList.begin()));
        //cout<<to_string(static_cast<int>(itemLocation-currentBagItemNameList.begin()))<<endl;
        *itemLocation = *itemLocation + "*";
        itemLocation = find(currentBagItemNameList.begin(),
            currentBagItemNameList.end(), itemName);
    }

    int bagItemSumUses = 0;
    for (int location : tempItemBagLocation) {
        if (tempItem->getIsConsumable()) {
            bagItemSumUses++;
        }
        else {
            bagItemSumUses += getInventoryBagUseLimit()[location];
        }
        

    }
    //This is to find how many of that item the player has in the bag. Again, at the current circumstance is mostly
    //applicable to gold gem and consumables.
    cout << "There are " << to_string(bagItemSumUses) << " in the bag that could be dropped" << endl;
    if (tempItem->getIsConsumable()) {
        cout << "Note this consumable item you can not drop by each use,"
            " available amount is simply how many shown in bag\n";
    }

    bool checkInput;
    int inputDropAmount = 0;

    while (inputDropAmount == 0) {
        //Ask the player how many to drop, if there are more than one of the item in the bag.
        checkInput = true;
        string userInput = getInput("Enter the amount to drop: ");
        for (char eachChar : userInput) {
            if (!isdigit(eachChar)) { checkInput = false; }
        }
        if (checkInput) {
            inputDropAmount = stoi(userInput);
            if (inputDropAmount > bagItemSumUses) {
                cout << "Input over the available amount!" << endl;
                inputDropAmount = 0;
            }
        }
        userInput.clear();
    }

    int numberToDelete = tempItem->getIsConsumable() ? inputDropAmount : inputDropAmount / (tempItem->getBagAmountCap());
    //for provisions and other consumables, each bag location hold on unit of the consumable which may contain several
    //uses. The program at current stage only allows to drop in unit of these consumable items.

    if (numberToDelete > tempItemBagLocation.size()) { numberToDelete = int(tempItemBagLocation.size()); }
    if (numberToDelete > 0) {
        for (int deleteNumber = 0; deleteNumber < numberToDelete; deleteNumber++) {
            //Update the inventory bag and the remaining item use amount as follows.

            inventoryBag.erase(inventoryBag.begin() + (tempItemBagLocation[deleteNumber] - deleteNumber));
            inventoryBagUseLimit.erase(inventoryBagUseLimit.begin() + (tempItemBagLocation[deleteNumber] - deleteNumber));

            if (tempItem->getAffectAttribute() && !tempItem->getIsConsumable()) {
                // Update the player attribute as the item is dropped, if applicable.
                setAttribute(-(tempItem->getAffectAttributeLvl()), tempItem->getAffectAttributeName());
            }
        }
        if (inputDropAmount % (tempItem->getBagAmountCap()) > 0) {
            tempItemBagLocation.erase(tempItemBagLocation.begin(), tempItemBagLocation.begin() + numberToDelete - 1);
            inventoryBagUseLimit[tempItemBagLocation[0] - numberToDelete + 1] -= (inputDropAmount % (tempItem->getBagAmountCap()));

            if (inventoryBagUseLimit[tempItemBagLocation[0] - numberToDelete + 1] == 0) {
                inventoryBag.erase(inventoryBag.begin() + (tempItemBagLocation[0] - numberToDelete + 1));
                inventoryBagUseLimit.erase(inventoryBagUseLimit.begin() + (tempItemBagLocation[0] - numberToDelete + 1));
            }
        }
    }
    else {
        inventoryBagUseLimit[tempItemBagLocation[0]] -= (inputDropAmount % (tempItem->getBagAmountCap()));
        if (inventoryBagUseLimit[tempItemBagLocation[0] ] == 0) {
            inventoryBag.erase(inventoryBag.begin() + (tempItemBagLocation[0]));
            inventoryBagUseLimit.erase(inventoryBagUseLimit.begin() + (tempItemBagLocation[0]));
        }
    }
    
    
    cout << getBagInformation() << endl;
}

vector <string> Player::getBagItemNameList(const string& category) {
    /*
     * This is a function that extract the item names in the bag and store into a vector list.
     * It can be set to return name list by type, as consumable, non-consumable, or All.
     */
    vector <string> stringItemNameList;
    int itemNum = 0;
    for (auto item : inventoryBag) {
        if (category == "C") {
            if (item->getIsConsumable()) {
                itemNum++;
                stringItemNameList.emplace_back(item->getName());
            }
        }
        else if (category == "NC") {
            if (!item->getIsConsumable()) {
                itemNum++;
                stringItemNameList.emplace_back(item->getName());
            }
        }
        else if (category == "A") {
            itemNum++;
            stringItemNameList.emplace_back(item->getName());
        }
        else if (category == "Drop") {
            if (item->getName() != "Map" && item->getName() != "Lantern") {
                itemNum++;
                stringItemNameList.emplace_back(item->getName());
            }
        }
        else {
            stringItemNameList.emplace_back("Error");
        }
    }
    return stringItemNameList;
}


void Player::useItemConsumable() {
    /*
     * This is the game play function that allows player to use consumable.
     * The available use will be updated and if all are consumed, the consumable will be removed from the bag.
     */
    if (getBagItemNameList("C").empty()) {
        cout << "\n\nThere is nothing you can use......\n\n";
    }
    else {
        string itemName = getUserSelectionFromBag("Please make you selection: ", "C");
        //Acquire the consumable item name here.
        vector <string> bagAllItemNameList = getBagItemNameList("A");
        int itemLocator = static_cast<int>(find(bagAllItemNameList.begin(), bagAllItemNameList.end(), itemName) -
            bagAllItemNameList.begin());
        Item*& tempConsumableItem = inventoryBag[itemLocator];
        //find the actual consumable item as a pointer from the inventory bag.
        int currentUseLimit = inventoryBagUseLimit[itemLocator];
        if (currentUseLimit > 0) {
            //Use the consumable, update the attribute and update the use limit.

            cout << to_string(currentUseLimit) << " available" << endl;
            setAttribute(tempConsumableItem->getAffectAttributeLvl(), tempConsumableItem->getAffectAttributeName());
            currentUseLimit = currentUseLimit - 1;
            inventoryBagUseLimit[itemLocator] = currentUseLimit;
            cout << "There are now " << to_string(currentUseLimit) << " available" << endl;

            if (currentUseLimit == 0) {
                inventoryBag.erase(inventoryBag.begin() + itemLocator);
                inventoryBagUseLimit.erase(inventoryBagUseLimit.begin() + itemLocator);
                //If none left, remove from the bag.
            }
        }
    }
}

string Player::getUserSelectionFromBag(const string& preFilledQuestion, const string& itemType) {
    /*
     * This is a function for displaying the available items (selection code|item name) according to needed type
     * - Consumable/Non-consumable or all items. It allows the user to make an input/selection and it automatically
     * validates that input against the displayed items (valid code list).
     */
    string stringNames = "\n\nThese are the items to choose from:\n\n";
    vector<string> itemNameList = getBagItemNameList(itemType);
    vector<string> nameCodeList;
    vector<string> uniqueItemNameList;
    int eliteCount = 0;
    for (const string& nameString : itemNameList) {
        //Iterate through consumable item name list and extract the first two character as the item code for selection.
        string tempNameString = "     " + nameString.substr(0, 2) + "|" + nameString;
        string tempCodeString = nameString.substr(0, 2);
        
        for (char& tempChar : tempCodeString) {
            tempChar = tolower(tempChar);
            //Convert the first two letters to lower case for the ease of validation later.
        }
        if (nameString == "Elite Sword") { tempCodeString = "el1"; }
        else if(nameString == "Elite Armour") { tempCodeString = "el2"; }
        //These two has the same code otherwise - need to make smarter version later. 
        if (find(nameCodeList.begin(), nameCodeList.end(), tempCodeString) == nameCodeList.end()) {
            //This is to avoid duplication of available selections. For example, if there are two provisions.
            nameCodeList.emplace_back(tempCodeString);
            stringNames.append(tempNameString);
            uniqueItemNameList.emplace_back(nameString);
        }
        tempNameString.clear();
        tempCodeString.clear();
    }
    cout << stringNames << endl;
    string userSelection;
    int userSelectionInt;
    while (userSelection.empty()) {
        userSelection = getInput(preFilledQuestion);
        //Take the player selection. And validate it in the following.
        for (char& tempInputChar : userSelection) {
            tempInputChar = tolower(tempInputChar);
        }
        if (nameCodeList.end() != find(nameCodeList.begin(), nameCodeList.end(), userSelection)) {
            //Check if the user input matches to one of the available items.
            userSelectionInt = static_cast<int>(find(nameCodeList.begin(), nameCodeList.end(), userSelection) - nameCodeList.begin());
            //If that's the case then extract the location of the selection item as in the consumable name list.
        }
        else {
            userSelection.clear();
            cout << "Please check your selection and retry.\n";
        }
    }
    string itemName = uniqueItemNameList[userSelectionInt];

    return itemName;
}

int Player::collectedArtefactCounter() {
    /*
     * This is for the check wining of game.
     * Calculate the number of artefacts being collected by the player.
     * In this game setup, it is preset that there can be 5 and only 5 artefacts that a player can collect.
     */
    int artefactCount = 0;
    for (auto eachItem : inventoryBag) {
        if (eachItem->getType() == "Artefact") { artefactCount++; }
    }
    return artefactCount;
}