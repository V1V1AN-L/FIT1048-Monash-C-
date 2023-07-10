
#ifndef FUNCTIONCOLLECTION_H
#define FUNCTIONCOLLECTION_H

/**************************************************
	Project: FIT1048 Assignment 4 - Major Project B
	Project Name: Treasure Caverns of Doom
	Author: Zecan Liu
	Purpose: Function Collection Header File
	Date: 20221030
**************************************************/

#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

/*
 * Reasons for having these functions outside the main program file is that these are handy "tools" that could be used
 * anywhere in this program, shared across class files.
 */

string getInput(const string& preFill);
//This function takes the user input (string) - for every user selection option

int randomIntFromRange(const string& range);
//This is the function used to generate a random number within a range (low$high string)

bool getConfirmation(const string& preFill);
//This is to ask the user to confirm using Y/N

void displayTextData(const string& myFile);
//Display a .txt file

#endif //FUNCTIONCOLLECTION_H
