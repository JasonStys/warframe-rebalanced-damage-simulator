#include "DamageCalculator.hpp"
#include "ColorUtil.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

void DamageCalculator::calculateAndDisplayDamage(const Weapon& weapon, Enemy& enemy) {
    srand(time(0)); // Initialize random seed

    int totalShots = weapon.getFireRate() * weapon.getFireTime();
    int magazineSize = weapon.getMagazineSize();
    int remainingShots = magazineSize;
    double reloadSpeed = weapon.getReloadSpeed();

    map<string, double> dotDamageMap;
    map<string, int> dotDurationMap;

    for (int i = 0; i < totalShots; ++i) {
        if (remainingShots == 0) {
            cout << "Reloading for " << reloadSpeed << " seconds..." << endl;
            remainingShots = magazineSize;
        }

        vector<ProjectileDamage> projectileDamages;
        int baseMultiShot = static_cast<int>(weapon.getMultiShot());
        double fractionalMultiShot = weapon.getMultiShot() - baseMultiShot;

        for (int j = 0; j < baseMultiShot; ++j) {
            ProjectileDamage projectileDamage = calculateProjectileDamage(weapon);
            if (!projectileDamage.statusSymbols.empty()) {
                applyDamageMultiplier(enemy, projectileDamage.statusSymbols[0], projectileDamage.damage); // Apply damage multiplier based on enemy type
            }
            projectileDamages.push_back(projectileDamage);
        }

        if ((rand() % 100) < (fractionalMultiShot * 100)) {
            ProjectileDamage projectileDamage = calculateProjectileDamage(weapon);
            if (!projectileDamage.statusSymbols.empty()) {
                applyDamageMultiplier(enemy, projectileDamage.statusSymbols[0], projectileDamage.damage); // Apply damage multiplier based on enemy type
            }
            projectileDamages.push_back(projectileDamage);
        }

        displayDamage(projectileDamages, enemy);

        for (const auto& projectileDamage : projectileDamages) {
            map<string, double> currentDotDamage = calculateDOT(weapon, projectileDamage.damage, projectileDamage.statusSymbols);

            for (auto it = currentDotDamage.begin(); it != currentDotDamage.end(); ++it) {
                dotDamageMap[it->first] += it->second;

                if (it->first == "💫") { // Slash damage
                    dotDurationMap[it->first] = 6; // Slash damage lasts 6 seconds
                } else {
                    dotDurationMap[it->first] = 6; // Other DOT damage lasts 6 seconds
                }
            }
        }

        remainingShots--;

        if (i % static_cast<int>(weapon.getFireRate()) == 0) {
            displayDOTDamage(dotDamageMap, dotDurationMap, enemy);
        }

        // Stop the damage calculation if the enemy's health reaches 0
        if (enemy.health <= 0) {
            cout << "Enemy is defeated!" << endl;
            return;
        }
    }

    // Continue displaying DOT damage until all timers run out or the enemy dies
    for (int t = 0; t < 12; ++t) { // Assuming max DOT duration is 12 seconds for Slash damage
        displayDOTDamage(dotDamageMap, dotDurationMap, enemy);
        if (enemy.health <= 0) {
            cout << "Enemy is defeated!" << endl;
            return;
        }
    }
}

ProjectileDamage DamageCalculator::calculateProjectileDamage(const Weapon& weapon) {
    double totalDamage = 0;
    vector<string> statusSymbols;

    double remainingStatusChance = weapon.getStatusChance();
    vector<pair<double, string>> damageProbabilities;

    double totalWeaponDamage = 0;
    for (const auto& damageType : weapon.getDamageTypes()) {
        totalWeaponDamage += damageType.value;
    }

    for (const auto& damageType : weapon.getDamageTypes()) {
        double probability = (damageType.value / totalWeaponDamage) * 100;
        damageProbabilities.push_back(make_pair(probability, damageType.symbol));
    }

    // Track procs per status effect
    map<string, double> proccedDamage;
    map<string, int> proccedCount;

    double statusRolls = remainingStatusChance / 100;
    int fullProcs = static_cast<int>(statusRolls);
    double fractionalProc = statusRolls - fullProcs;

    // Track Cold damage procs
    int coldProcCount = 0;
    double additionalCritMultiplier = 0.0;

    for (int i = 0; i < fullProcs; ++i) {
        double roll = (rand() % 100) + 1;

        double cumulativeProbability = 0;
        for (const auto& damageProbability : damageProbabilities) {
            cumulativeProbability += damageProbability.first;

            if (roll <= cumulativeProbability) {
                proccedDamage[damageProbability.second] += damageProbability.first / 100 * totalWeaponDamage;
                proccedCount[damageProbability.second]++;
                statusSymbols.push_back(damageProbability.second);

                // Check for Cold damage and adjust critical multiplier
                if (damageProbability.second == "❄️") {
                    coldProcCount++;
                }

                break;
            }
        }
    }

    if ((rand() % 100) < (fractionalProc * 100)) {
        double roll = (rand() % 100) + 1;
        double cumulativeProbability = 0;
        for (const auto& damageProbability : damageProbabilities) {
            cumulativeProbability += damageProbability.first;

            if (roll <= cumulativeProbability) {
                proccedDamage[damageProbability.second] += damageProbability.first / 100 * totalWeaponDamage;
                proccedCount[damageProbability.second]++;
                statusSymbols.push_back(damageProbability.second);

                // Check for Cold damage and adjust critical multiplier
                if (damageProbability.second == "❄️") {
                    coldProcCount++;
                }

                break;
            }
        }
    }

    // Calculate additional crit multiplier based on Cold procs
    if (coldProcCount > 0) {
        additionalCritMultiplier = 0.1 + (coldProcCount - 1) * 0.05;
        additionalCritMultiplier = min(additionalCritMultiplier, 0.5); // Cap at +0.5
    }

    // Sum up the damage for each proc'd effect
    for (const auto& proc : proccedDamage) {
        totalDamage += proc.second * proccedCount[proc.first];
    }

    // Apply critical multipliers
    double critChance = weapon.getCriticalChance();
    double critMultiplier = weapon.getCriticalMultiplier() + additionalCritMultiplier; // Add the additional crit multiplier from Cold procs
    int critCount = 0;
    while (critChance > 0) {
        double roll = (rand() % 100) + 1;
        if (roll <= critChance) {
            totalDamage *= critMultiplier;
            critCount++;
        }
        critChance -= 100;
    }

    return {totalDamage, statusSymbols, critCount};
}

void DamageCalculator::displayDamage(const vector<ProjectileDamage>& projectileDamages, Enemy& enemy) {
    double totalDamage = 0;

    for (const auto& projectileDamage : projectileDamages) {
        totalDamage += projectileDamage.damage;

        double damage = projectileDamage.damage;
        const vector<string>& statusSymbols = projectileDamage.statusSymbols;
        int critCount = projectileDamage.critCount;

        ostringstream oss;
        for (const auto& symbol : statusSymbols) {
            oss << symbol;
        }

        if (damage == static_cast<int>(damage)) {
            oss << static_cast<int>(damage);
        } else {
            oss << fixed << setprecision(2) << damage;
        }

        // Set color based on critCount
        if (critCount == 0) {
            ColorUtil::setColor(ColorUtil::LIGHT_GRAY);
        } else if (critCount == 1) {
            ColorUtil::setColor(ColorUtil::YELLOW);
        } else if (critCount == 2) {
            ColorUtil::setColor(ColorUtil::ORANGE);
        } else {
            ColorUtil::setColor(ColorUtil::RED);
        }

        cout << oss.str() << " ";

        // Reset color after output
        ColorUtil::resetColor();
    }

    cout << endl;
    displayHealthBar(enemy, totalDamage);

    // Stop the damage calculation if the enemy's health reaches 0
    if (enemy.health <= 0) {
        cout << "Enemy is defeated!" << endl;
        return;
    }
}

void DamageCalculator::displayHealthBar(Enemy& enemy, double totalDamage) {
    if (applyDamageToEnemy(enemy, totalDamage)) {
        // Display the health bar only if the enemy is still alive

        cout << "Health Bar:" << endl;

        // Overguard bar
        if (enemy.hasOverguard) {
            ColorUtil::setColor(ColorUtil::LIGHT_GRAY);
            cout << "[";
            int overguardBlocks = static_cast<int>((enemy.overguard / (enemy.health * 0.5)) * 20);
            for (int i = 0; i < overguardBlocks; ++i) cout << "#";
            for (int i = 0; i < 20 - overguardBlocks; ++i) cout << "-";
            cout << "] Overguard: " << enemy.overguard << endl;
            ColorUtil::resetColor();
        }

        // Shield bar
        ColorUtil::setColor(ColorUtil::BLUE);
        cout << "[";
        int shieldBlocks = static_cast<int>((enemy.shield / (enemy.shield + 1)) * 20);
        for (int i = 0; i < shieldBlocks; ++i) cout << "#";
        for (int i = 0; i < 20 - shieldBlocks; ++i) cout << "-";
        cout << "] Shield: " << enemy.shield << endl;
        ColorUtil::resetColor();

        // Health bar
        if (enemy.armor > 0) {
            ColorUtil::setColor(ColorUtil::YELLOW);
        } else {
            ColorUtil::setColor(ColorUtil::RED);
        }

        cout << "[";
        int healthBlocks = static_cast<int>((enemy.health / (enemy.health + 1)) * 20);
        for (int i = 0; i < healthBlocks; ++i) cout << "#";
        for (int i = 0; i < 20 - healthBlocks; ++i) cout << "-";
        cout << "] Health: " << enemy.health << endl;
        ColorUtil::resetColor();
    }
}

bool DamageCalculator::applyDamageToEnemy(Enemy& enemy, double damage) {
    double damageAfterArmor = damage * (1 - (enemy.armor / (enemy.armor + 300.0)));

    // Overguard
    if (enemy.hasOverguard && enemy.overguard > 0) {
        enemy.overguard -= damageAfterArmor;
        if (enemy.overguard < 0) {
            damageAfterArmor = -enemy.overguard;
            enemy.overguard = 0;
        } else {
            damageAfterArmor = 0;
        }
    } else {
        // If no overguard, reduce shields first
        if (enemy.shield > 0) {
            enemy.shield -= damageAfterArmor;
            if (enemy.shield < 0) {
                damageAfterArmor = -enemy.shield;
                enemy.shield = 0;
            } else {
                damageAfterArmor = 0;
            }
        }

        // If shields are depleted, reduce health and apply stacking effects
        if (enemy.shield == 0) {
            enemy.health -= damageAfterArmor;
            if (enemy.health < 0) enemy.health = 0;
            applyStackingEffects(enemy);
        }
    }

    // Return false if enemy health reaches 0
    return enemy.health > 0;
}

void DamageCalculator::applyStackingEffects(Enemy& enemy) {
    double totalArmorReduction = 0;
    double totalShieldReduction = 0;

    for (auto& effect : statusEffects) {
        if (effect.second.duration > 0) {
            if (effect.first == "🔨") { // Impact
                totalArmorReduction += 0.08 * effect.second.stacks; // Reduce void armor by 8% per stack
            } else if (effect.first == "🏹") { // Puncture
                if (enemy.armorType == "ferrite" || enemy.armorType == "prime" || enemy.armorType == "alloy" || enemy.armorType == "adaptive") {
                    totalArmorReduction += 0.07 * effect.second.stacks; // Reduce ferrite, prime, alloy, and adaptive armor by 7% per stack
                }
            } else if (effect.first == "❄️") { // Cold
                totalArmorReduction += 0.05 * effect.second.stacks; // Reduce void armor by 5% per stack
            } else if (effect.first == "🎧") { // Magnetic
                totalShieldReduction += 0.09 * effect.second.stacks; // Reduce shields by 9% per stack
            } else if (effect.first == "⚗️") { // Corrosive
                if (enemy.armorType == "ferrite" || enemy.armorType == "prime" || enemy.armorType == "fossilized") {
                    totalArmorReduction += 0.08 * effect.second.stacks; // Reduce ferrite, prime, and fossilized armor by 8% per stack
                }
            } else if (effect.first == "☢️") { // Radiation
                if (enemy.armorType == "alloy" || enemy.armorType == "adaptive") {
                    totalArmorReduction += 0.08 * effect.second.stacks; // Reduce alloy and adaptive armor by 8% per stack
                }
            }
            effect.second.duration--;
        }
    }

    // Apply armor reduction
    enemy.armor -= enemy.armor * totalArmorReduction;
    if (enemy.armor < 0) enemy.armor = 0;

    // Apply shield reduction (only if no overguard)
    if (enemy.overguard <= 0) {
        enemy.shield -= enemy.shield * totalShieldReduction;
        if (enemy.shield < 0) enemy.shield = 0;
    }
}

void DamageCalculator::applyDamageMultiplier(Enemy& enemy, const string& damageType, double& damage) {
    // Define the multipliers based on table
    static const map<string, map<string, double>> damageMultipliers = {
        {"🔨", {{"ferrite", 0.75}, {"alloy", 0.5}, {"proto", -0.5}, {"fossilized", 0.5}, {"indifferent", -0.5}, {"orkin", -0.75}, {"prime", -0.25}}},
        {"🏹", {{"ferrite", 0.5}, {"alloy", 0.75}, {"proto", -0.5}, {"fossilized", 0.75}, {"adaptive", -0.5}, {"orkin", -0.5}, {"prime", -0.5}}},
        {"💫", {{"corpo", 0.5}, {"biomechanical", 0.75}, {"fossilized", -0.5}, {"void", -0.5}}},
        {"🔥", {{"biomechanical", 0.5}, {"fossilized", 0.75}, {"void", -0.5}, {"orkin", -0.75}}},
        {"❄️", {{"ferrite", 0.15}, {"fossilized", -0.5}, {"adaptive", 0.5}, {"prime", 0.25}}},
        {"⚡", {{"proto", 0.75}, {"orkin", -0.5}}},
        {"☠", {{"biomechanical", -0.75}, {"fossilized", -0.5}, {"indifferent", -0.5}, {"void", -0.75}, {"orkin", -0.75}}},
        {"💥", {{"biomechanical", -0.5}, {"adaptive", 0.5}, {"fossilized", -0.5}}},
        {"⚗️", {{"ferrite", 0.25}, {"fossilized", 0.75}}},
        {"♨️", {{"fossilized", -0.5}}},
        {"🎧", {{"proto", 0.75}, {"sentient", -0.75}}},
        {"☢", {{"alloy", 0.75}, {"adaptive", 0.75}, {"void", 0.5}}},
        {"☣", {{"biomechanical", -0.5}, {"fossilized", -0.75}, {"void", -0.75}}}
    };

    // Apply the appropriate multiplier
    if (damageMultipliers.count(damageType) > 0) {
        const auto& multipliers = damageMultipliers.at(damageType);
        if (multipliers.count(enemy.armorType) > 0) {
            damage *= (1.0 + multipliers.at(enemy.armorType));
        }
    }
}

void DamageCalculator::displayDOTDamage(map<string, double>& dotDamageMap, map<string, int>& dotDurationMap, Enemy& enemy) {
    bool hasDOT = false;
    double viralDOT = 0;
    bool gasDOTActive = false;

    // Calculate the current viral DOT to add to other DOTs
    if (dotDamageMap.find("☣") != dotDamageMap.end()) {
        viralDOT = dotDamageMap["☣"];
    }

    // Check if Gas DOT is active
    if (dotDamageMap.find("♨️") != dotDamageMap.end()) {
        gasDOTActive = dotDamageMap["♨️"] > 0;
    }

    for (auto it = dotDamageMap.begin(); it != dotDamageMap.end(); ++it) {
        if (it->second > 0) {
            hasDOT = true;

            // Add viral DOT to all other DOTs
            if (it->first != "☣") {
                it->second += viralDOT;
            }

            // Apply Gas DOT behavior: Trigger non-Gas status effects during Gas DOT
            if (gasDOTActive && it->first != "♨️") {
                double additionalGasDOT = 0.5 * it->second; // 50% of its damage
                dotDamageMap["♨️"] += additionalGasDOT; // Add this to Gas DOT
            }

            ColorUtil::setColor(ColorUtil::LIGHT_GRAY);
            cout << it->first << it->second << " ";

            double dotDamage = it->second;
            if (!applyDamageToEnemy(enemy, dotDamage)) {
                cout << "Enemy is defeated!" << endl;
                return;
            }

            displayHealthBar(enemy, 0);  // Display health bar with no additional damage

            dotDurationMap[it->first]--;
            if (dotDurationMap[it->first] <= 0) {
                it->second = 0;
            } else {
                it->second = max(0.0, it->second - (it->second * 0.1)); // Simulate DOT decay
            }
        }
    }

    if (hasDOT) {
        cout << endl;
    }

    ColorUtil::resetColor();
}

map<string, double> DamageCalculator::calculateDOT(const Weapon& weapon, double damage, const vector<string>& statusSymbols) {
    map<string, double> dotDamageMap;

    for (const auto& statusSymbol : statusSymbols) {
        for (const auto& damageType : weapon.getDamageTypes()) {
            if (damageType.symbol == statusSymbol) {
                if (damageType.name == "Slash" || damageType.name == "Heat" || damageType.name == "Electric" || damageType.name == "Toxin") {
                    dotDamageMap[damageType.symbol] += 0.50 * damage; // DOT damage for Heat, Electric, Toxin
                } else if (damageType.name == "Viral") {
                    dotDamageMap[damageType.symbol] += 0.35 * damage; // DOT damage for Viral
                } else if (damageType.name == "Blast") {
                    dotDamageMap[damageType.symbol] += 0.30 * damage; // Delayed damage for Blast
                } else if (damageType.name == "Gas") {
                    dotDamageMap[damageType.symbol] += 0.50 * damage; // DOT for Gas
                }

                // Handle stacking and timer for status effects
                if (damageType.name == "Impact" || damageType.name == "Puncture" || damageType.name == "Cold" ||
                    damageType.name == "Magnetic" || damageType.name == "Corrosive" || damageType.name == "Radiation") {
                    if (statusEffects[damageType.symbol].duration > 0) {
                        statusEffects[damageType.symbol].stacks++;
                        if (statusEffects[damageType.symbol].stacks > 10) {
                            statusEffects[damageType.symbol].stacks = 10; // Cap stacks at 10
                        }
                    } else {
                        statusEffects[damageType.symbol] = {1, 10}; // Start with 1 stack and 10 second duration
                    }
                }
            }
        }
    }

    return dotDamageMap;
}
