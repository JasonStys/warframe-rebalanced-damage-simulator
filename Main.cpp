#include <iostream>
#include <limits>
#include "Weapon.hpp"
#include "DamageCalculator.hpp"
#include "Enemy.hpp"

using namespace std;

void printMenu() {
    cout << "\n1. Fire weapon with current values" << endl;
    cout << "2. Input new values" << endl;
    cout << "3. Input enemy values" << endl;
    cout << "4. Quit" << endl;
}

int main() {
    int choice;
    Weapon weapon;
    Enemy enemy;
    DamageCalculator damageCalculator;

    // Get initial inputs from the user
    weapon.getInput();
    enemy.getInput();

    do {
        damageCalculator.calculateAndDisplayDamage(weapon, enemy);
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Check if the input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Improper value, try again." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                damageCalculator.calculateAndDisplayDamage(weapon, enemy);
                break;
            case 2:
                weapon.getInput();
                break;
            case 3:
                enemy.getInput();
                break;
            case 4:
                cout << "Quitting the program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
