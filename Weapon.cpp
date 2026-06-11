#include "Weapon.hpp"
#include <iostream>
#include <limits>

using namespace std;

Weapon::Weapon()
    : fireTime(1),
      fireRate(1.0),
      magazineSize(1),
      reloadSpeed(1.0),
      multiShot(1.0),
      criticalChance(0.0),
      criticalMultiplier(1.0),
      statusChance(0.0) {
    initializeDamageTypes();
}

void Weapon::initializeDamageTypes() {
    damageTypes = {
        {"Impact", 0.0, "🔨"},
        {"Puncture", 0.0, "🏹"},
        {"Slash", 0.0, "💫"},
        {"Heat", 0.0, "🔥"},
        {"Cold", 0.0, "❄️"},
        {"Electric", 0.0, "⚡"},
        {"Toxin", 0.0, "☠"},
        {"Blast", 0.0, "💥"},
        {"Corrosive", 0.0, "⚗️"},
        {"Gas", 0.0, "♨️"},
        {"Magnetic", 0.0, "🎧"},
        {"Radiation", 0.0, "☢"},
        {"Viral", 0.0, "☣"}
    };
}

static void clearBadInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Weapon::getInput() {
    cout << "\nEnter weapon values." << endl;
    cout << "Fire time in seconds: ";
    while (!(cin >> fireTime) || fireTime <= 0) {
        cout << "Enter a positive whole number for fire time: ";
        clearBadInput();
    }

    cout << "Fire rate shots per second: ";
    while (!(cin >> fireRate) || fireRate <= 0) {
        cout << "Enter a positive number for fire rate: ";
        clearBadInput();
    }

    cout << "Magazine size: ";
    while (!(cin >> magazineSize) || magazineSize <= 0) {
        cout << "Enter a positive whole number for magazine size: ";
        clearBadInput();
    }

    cout << "Reload speed in seconds: ";
    while (!(cin >> reloadSpeed) || reloadSpeed < 0) {
        cout << "Enter a nonnegative number for reload speed: ";
        clearBadInput();
    }

    cout << "Multishot value. Example 1.5 means one guaranteed projectile and a 50 percent chance for another: ";
    while (!(cin >> multiShot) || multiShot <= 0) {
        cout << "Enter a positive number for multishot: ";
        clearBadInput();
    }

    cout << "Critical chance percentage. Values above 100 can roll multiple critical tiers: ";
    while (!(cin >> criticalChance) || criticalChance < 0) {
        cout << "Enter a nonnegative number for critical chance: ";
        clearBadInput();
    }

    cout << "Critical multiplier: ";
    while (!(cin >> criticalMultiplier) || criticalMultiplier < 1.0) {
        cout << "Enter a number greater than or equal to 1 for critical multiplier: ";
        clearBadInput();
    }

    cout << "Status chance percentage. Values above 100 can create multiple status procs: ";
    while (!(cin >> statusChance) || statusChance < 0) {
        cout << "Enter a nonnegative number for status chance: ";
        clearBadInput();
    }

    cout << "\nEnter damage values. Use 0 for damage types the weapon does not have." << endl;
    for (auto& damageType : damageTypes) {
        cout << damageType.name << " damage " << damageType.symbol << ": ";
        while (!(cin >> damageType.value) || damageType.value < 0) {
            cout << "Enter a nonnegative damage value: ";
            clearBadInput();
        }
    }
}

double Weapon::getFireRate() const { return fireRate; }
int Weapon::getMagazineSize() const { return magazineSize; }
double Weapon::getReloadSpeed() const { return reloadSpeed; }
double Weapon::getMultiShot() const { return multiShot; }
double Weapon::getCriticalChance() const { return criticalChance; }
double Weapon::getCriticalMultiplier() const { return criticalMultiplier; }
double Weapon::getStatusChance() const { return statusChance; }
int Weapon::getFireTime() const { return fireTime; }
const vector<DamageType>& Weapon::getDamageTypes() const { return damageTypes; }
