#include "Enemy.hpp"
#include <iostream>
#include <limits>

using namespace std;

Enemy::Enemy()
    : health(100.0),
      shield(0.0),
      armor(0.0),
      overguard(0.0),
      hasOverguard(false),
      healthType("clone"),
      armorType("ferrite"),
      shieldType("na"),
      faction("grineer"),
      unitType("basic") {}

static void clearBadEnemyInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Enemy::getInput() {
    cout << "\nEnter enemy values." << endl;

    cout << "Health: ";
    while (!(cin >> health) || health <= 0) {
        cout << "Enter a positive health value: ";
        clearBadEnemyInput();
    }

    cout << "Health type. Example clone, corpo, robotic, infested, biomechanical, indifferent, nekro: ";
    cin >> healthType;

    cout << "Armor: ";
    while (!(cin >> armor) || armor < 0) {
        cout << "Enter a nonnegative armor value: ";
        clearBadEnemyInput();
    }

    cout << "Armor type. Example ferrite, alloy, adaptive, fossilized, void, prime, na: ";
    cin >> armorType;

    cout << "Shield: ";
    while (!(cin >> shield) || shield < 0) {
        cout << "Enter a nonnegative shield value: ";
        clearBadEnemyInput();
    }

    cout << "Shield type. Example proto, sentient, orkin, na: ";
    cin >> shieldType;

    char overguardChoice;
    cout << "Does the enemy have overguard? y/n: ";
    cin >> overguardChoice;
    hasOverguard = overguardChoice == 'y' || overguardChoice == 'Y';

    if (hasOverguard) {
        cout << "Overguard value: ";
        while (!(cin >> overguard) || overguard < 0) {
            cout << "Enter a nonnegative overguard value: ";
            clearBadEnemyInput();
        }
    } else {
        overguard = 0.0;
    }
}
