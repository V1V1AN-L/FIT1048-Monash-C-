/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Master Roshi Class Definition File
    Date: 20221030
**************************************************/

#include "MasterRoshi.h"

#include <utility>

// Constructor and Destructor functions same as that of the base class.
MasterRoshi::MasterRoshi() :TreasureHunter() {};
MasterRoshi::MasterRoshi(std::string nameInput) : TreasureHunter(std::move(nameInput)) {};
MasterRoshi::~MasterRoshi() = default;

void MasterRoshi::getDetails() {
    /*
    * This is the stat of Master Roshi NPC
    * Only given its certain way of interactiona and no other functionality in the game, this is currently being hard coded
    * Mindful it could adapt the same class structure as that of player class for further development of the game. 
    */
    cout << "\n============================================================================\n"
        "Name: Master Roshi                                                          \n"
        "Health: unknown                Attack: unknown              Defence: unknown\n"
        "Carrying item: A big drinking bottle - smells like alcohol..                \n"
        "Description: An bold old guy wondering around in the caves in his slippers..\n"
        "             Seems to be too chill to be in this underground monster world..\n"
        "============================================================================\n\n";
}

void MasterRoshi::speak() {
    //The unique message as sent out by master Roshi when interact with the player
    cout << "HO OH HO OH OH!\n"
        "Finally there is someone else I could speak to now!!!\n"
        "I have been so bored in these damn caves.............\n";
}

void MasterRoshi::interaction(Player* activePlayer) {
    /*
    * Here below is the designed interaction between the master Roshi and the player. 
    * Note that to elevate the game play experience, the interaction was made to a small game between the NPC and the player. 
    * This avoid the repeated experience of combating a NPC, which is essentially same as facing any of the monsters. 
    */
    cout << "Looks like you are also hunting for treasure here huh?\n"
        "But...... You look weak.......\n";

    if (getConfirmation("\nI am bored anyway, would you like to play a game with me?")) {
        cout << "Great! Lets play a simple gambling game, you may get rewarded if you win!\n"
            "It's a simple game, we both roll three dices and see who gets the biggest!\n";

        cout << "\n\nOk...... Let me do this first then.\n Warn you that I rarely loose..\n";

        int playerScore = 0;
        int roshiScore = 0;
        int roundCheck = 0;
        for (int round = 0; round < 3; round++) {
            roundCheck++;
            int tempRoshiScore = randomIntFromRange("1&6");
            roshiScore += tempRoshiScore;
            cout << "\n\nMaster Roshi scored " << tempRoshiScore << " for this round!\n";
            if (getConfirmation("Now it's your turn, roll?")) {
                int tempPlayerScore = randomIntFromRange("1&6");
                cout << "You scored " << tempPlayerScore << " for this round!\n";
                playerScore += tempPlayerScore;
            }
            else {
                break;
            }
        }

        if (roundCheck == 3) {
            cout << "The final score is: \n"
                "Master Roshi: " + to_string(roshiScore) + "\n"
                "You: " + to_string(playerScore) + "\n";

            system("Pause");
            if (playerScore > roshiScore) {
                //If winning the game, the player would gain a special attack capability. The player could choose to use this attack once only later when facing any of the monsters. 
                cout << "AHHHHHH... Didn't expect you to be this good...\n"
                    "Well I will have to award you now\n"
                    "Let me teach you this one, this is my special attack, called Kame Hame Ha\n";
                
                activePlayer->setSpecialAttack(true);
                system("Pause");
                cout << "\n\nBe careful though, given your strength, you will only be perform this attack once\n"
                    "before you exhaust yourself..\n"
                    "But anyways, good luck young soul.. I'm going to find some monsters now and have some fun\n";
                system("Pause");
                cout << "System message: You have gained the special attack Kame Hame Ha - instant damage of 10!\n"
                    "Use limit: 1";
            }
            else if (playerScore < roshiScore) {
                cout << "See, I told you I am good.\n"
                    "Well good luck with you adventure young soul.\n"
                    "Try not to die in here and I may see you out there\n";
            }
            else if (playerScore == roshiScore) {
                cout << "Look like it's a tight game here.\n"
                    "What are the odds hey....\n"
                    "Well at least what I can offer you is this\n"
                    "Drink this and it will help you regain some strength\n"
                    "Good bye my friend!\n";
                system("Pause");
                activePlayer->setAttribute(5, PlayerAttribute::Health);
                cout << "System message: Your health increased by 5!\n";
            }
        }
        else {
            cout << "Dare you to trick me like that!!\n"
                "You asked for this then, don't blame me....\n"
                "Ha Me Ha Me Daaaaa!\n";
            system("Pause");
            activePlayer->setAttribute(-10, PlayerAttribute::Health);
            cout << "System message: You took a damage of 10!\n";
        }
    }
    else {
        cout << "Boring\n"
            "Now leave me alone before I kill you for fun!\n"
            "This is just a little punishment for now...\n";
        system("Pause");
        activePlayer->setAttribute(-2, PlayerAttribute::Health);
        cout << "System message: You took a damage of 2!\n";
    }
    system("Pause");
}