
/**************************************************
    Project: FIT1048 Assignment 4 - Major Project B
    Project Name: Treasure Caverns of Doom
    Author: Zecan Liu
    Purpose: Hero LiKui Class Definition File
    Date: 20221030
**************************************************/


#include "HeroLiKui.h"

#include <utility>

HeroLiKui::HeroLiKui() :TreasureHunter() {};
HeroLiKui::HeroLiKui(std::string nameInput) : TreasureHunter(std::move(nameInput)) {};
HeroLiKui::~HeroLiKui() = default;


void HeroLiKui::getDetails() {
    cout << "\n============================================================================\n"
        "Name: Hero Li Kui                                                          \n"
        "Health: 999                Attack: 999              Defence: 999\n"
        "Carrying item: A bunch of monster heads. There is even a dragon head there! \n"
        "Description: THe warrior from the east. The dragon slayer. The monster hunter.\n"
        "============================================================================\n\n";
}

void HeroLiKui::speak() {
    cout << "Ai Ya Ya Ya Ya!\n"
        "Look who I found. Another hunter!\n"
        "I am tired from killing all those monsters..Let's have a little break!\n";
}

void HeroLiKui::interaction(Player* activePlayer) {
    cout << "\n\nThese monsters are too weak for me to have some fun with..\n"
        "Would you help me warming up my body? \n"
        "I won't use full power of course, as you don't stand a chance that way.\n";
    if (getConfirmation("\n\nProceed? This guy look scary though...")) {
        cout << "\n\nOk then, I will hit you three times. You win if you manage to "
            "keep the damage less than 5, that is if you are strong enough and lucky enough\n\n";

        cout << "System message: Your defence + your luck + random number between 1-3 is your final defence\n\n";
       
        system("Pause");

        int tempKuiDamage;
        int tempPlayerDefence;
        int tempDamage;
        int totalDamage = 0;
        int roundCount = 0;
        for (int round = 0; round < 3; round++) {
            roundCount++;

            cout << "\n\nRound " + to_string(roundCount) << endl;
            tempKuiDamage = randomIntFromRange("10&20");
            cout << "Li Kui threw a axe! Made a damage of " << tempKuiDamage << "!\n";
            tempPlayerDefence = activePlayer->getDefence() + activePlayer->getLuck() + randomIntFromRange("1&3");
            cout << "You try to block the attack, manage to have a defence of " << tempPlayerDefence << "!\n";
            tempDamage = tempKuiDamage < tempPlayerDefence ? 0 : tempKuiDamage - tempPlayerDefence;
            cout << "Took a actual damage of " << tempDamage << " this round!\n\n";
            totalDamage += tempDamage;
            system("Pause");

        }
        cout << "The total damage taken is " << totalDamage << "!\n";
        if (totalDamage < 5) {
            cout << "Tough and Lucky! Ok young fella, these are yours now\n"
                "Good luck!\n";
            system("Pause");

            if (getConfirmation("Pick up the item?")) {
                activePlayer->pickItemUp("Kui's Twin Axes");
                activePlayer->getDetails();
            }
            else {
                cout << "\n\nPity! Those could really help you with your journey ahead.\n";
            }
            system("Pause");

        }
        else {
            cout << "\n\nHaHaHa, You knew you don't stand a chance.\n"
                "Try harder next time!!!\n"
                "Let me now find more dragons to play with\n";
            system("Pause");
        }
    }
    else {
        cout << "\n\nDare you deny me young soul!\n"
            "Just a little punishment for you then..\n"
            "Do Not Let Me See You Again.....\n";
        system("Pause");
        cout << "System Message: Kui threw a axe, and hit you!\n"
            "You are hurt and both your armour and weapon are damaged...\n";
        activePlayer->setAttribute(-8, PlayerAttribute::Health);
        activePlayer->setAttribute(-2, PlayerAttribute::Damage);
        activePlayer->setAttribute(-2, PlayerAttribute::Defence);
        cout<<activePlayer->getDetails();
        system("Pause");

    }
}
