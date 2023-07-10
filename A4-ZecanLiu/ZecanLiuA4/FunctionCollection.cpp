
/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Function Collection Definition File
    Date: 20221029
**************************************************/

#include "FunctionCollection.h"


string getInput(const string& preFill) {
    //Take user input function. Question as an input argument.
    string stringInput;
    int loopCount = 1;

    while (stringInput.empty()) {
        if (loopCount > 1)
            cout << "No valid input detected..\n";
        cout << preFill << " ";
        ++loopCount;
        cin.clear();
        getline(cin, stringInput);
    }
    return stringInput;
}

int randomIntFromRange(const string& range) {
    //Generate a random number from range. Range input is a string in format of "low&high"
    int lowLimit, highLimit;
    size_t locSeparator;

    if (range.find('&') != string::npos) {
        locSeparator = range.find('&');
        lowLimit = stoi(range.substr(0, locSeparator));
        highLimit = stoi(range.substr(locSeparator + 1, range.size()));
    }
    else {
        lowLimit = 1;
        highLimit = 1;
    }
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the Mersenne Twister pseudo-random generator
    uniform_int_distribution<> tempRange(lowLimit, highLimit);
    int tempInt = tempRange(gen);
    return tempInt;
}

bool getConfirmation(const string& preFill) {
    //Get Y/N selection function
    string userInput;
    string checkString = "YyNn";
    bool checkLoop = false;
    bool userSelection;
    int loopCount = 0;
    while (!checkLoop) {
        if (loopCount > 0)
            cout << "Invalid selection, please try again.\n";
        cout << preFill << "\n" << "Please select [Y/N]: ";
        cin.clear();
        getline(cin, userInput);
        loopCount++;
        if (userInput.size() == 1) {
            if (checkString.find(userInput) != string::npos) {
                checkLoop = true;
                if (userInput == "Y" || userInput == "y")
                    userSelection = true;
                else
                    userSelection = false;
            }
        }
    }
    return userSelection;
}

void displayTextData(const string& myFile) {
    /*
    This function is to display the information from the prepared .txt files.
    This is shared by both option 1 and 5 for different content for displaying.
    */

    fstream fileToRead;
    fileToRead.open(myFile, ios::in);
    //Read only mode.
    if (fileToRead.is_open()) {
        string importedText = "\n";
        string tempLineText;
        //The entire content in the .txt file is exported line by line but saved into a single string - importedText
        while (getline(fileToRead, tempLineText)) {
            importedText.append(tempLineText + "\n");
        }
        cout << importedText;
        //Print out everything at once.
        fileToRead.close();
    }
    else
        cout << "\n There is an error opening the \"About\" file\n" << endl;
}

