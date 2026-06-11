#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <vector>
#include <string>

struct DamageType {
    std::string name;
    double value;
    std::string symbol;
};

class Weapon {
public:
    Weapon();
    void getInput();
    double getFireRate() const;
    int getMagazineSize() const;
    double getReloadSpeed() const;
    double getMultiShot() const;
    double getCriticalChance() const;
    double getCriticalMultiplier() const;
    double getStatusChance() const;
    int getFireTime() const;  // Add this function to retrieve fireTime
    const std::vector<DamageType>& getDamageTypes() const;

private:
    int fireTime;
    double fireRate;
    int magazineSize;
    double reloadSpeed;
    double multiShot;
    double criticalChance;
    double criticalMultiplier;
    double statusChance;
    std::vector<DamageType> damageTypes;

    void initializeDamageTypes();
};

#endif // WEAPON_HPP
