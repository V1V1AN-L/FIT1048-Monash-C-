/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Treasure Hunter (Abstract) Class Definition  File
    Date: 20221029
**************************************************/

#include "TreasureHunter.h"

#include <utility>

//Default constructor
TreasureHunter::TreasureHunter() {
    name = "This is just a default constructor";
}

//Overload constructor 
TreasureHunter::TreasureHunter(std::string nameInput) {
    name = std::move(nameInput);
}

//Default destructor 
TreasureHunter::~TreasureHunter() = default;


//Assessor function
string TreasureHunter::getName() {
    //Get name is defined as it is the same across all sub-classes
    return name;
}