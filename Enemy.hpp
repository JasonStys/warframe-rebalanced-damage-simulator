#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <string>

class Enemy {
public:
    Enemy();
    void getInput();

    double health;
    double shield;
    double armor;
    double overguard;
    bool hasOverguard;
    std::string healthType;
    std::string armorType;
    std::string shieldType;
    std::string faction;
    std::string unitType;
};

#endif // ENEMY_HPP
