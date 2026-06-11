#ifndef DAMAGE_CALCULATOR_HPP
#define DAMAGE_CALCULATOR_HPP

#include "Weapon.hpp"
#include "Enemy.hpp"
#include <map>
#include <vector>
#include <string>

struct ProjectileDamage {
    double damage;
    std::vector<std::string> statusSymbols;
    int critCount;
};

struct StatusEffect {
    int stacks;
    int duration;
};

class DamageCalculator {
public:
    void calculateAndDisplayDamage(const Weapon& weapon, Enemy& enemy);

private:
    void displayDamage(const std::vector<ProjectileDamage>& projectileDamages, Enemy& enemy);
    void displayHealthBar(Enemy& enemy, double totalDamage);
    bool applyDamageToEnemy(Enemy& enemy, double damage);
    void applyStackingEffects(Enemy& enemy);
    void applyDamageMultiplier(Enemy& enemy, const std::string& damageType, double& damage);
    void displayDOTDamage(std::map<std::string, double>& dotDamageMap, std::map<std::string, int>& dotDurationMap, Enemy& enemy);
    std::map<std::string, double> calculateDOT(const Weapon& weapon, double damage, const std::vector<std::string>& statusSymbols);

    // Correct declaration of calculateProjectileDamage
    ProjectileDamage calculateProjectileDamage(const Weapon& weapon);

    std::map<std::string, StatusEffect> statusEffects; // To track status effects with duration and stacks
};

#endif // DAMAGE_CALCULATOR_HPP
