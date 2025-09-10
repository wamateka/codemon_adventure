// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Codemon.cpp
// Assignment: Final Project
// Purpose: Codemon class implementation with expanded features

#include "Codemon.h"

// Skill implementations
Skill::Skill() {
    name = "";
    type = "";
    description = "";
    baseDamage = 0;
}

Skill::Skill(const string& n, const string& t, int dmg, const string& desc) {
    name = n;
    type = t;
    baseDamage = dmg;
    description = desc;
}

// Codemon implementations
Codemon::Codemon() {
    name = "";
    type = "";
    description = "";
    level = 0;
    currentHP = 0;
    maxHP = 0;
    skillCount = 0;
    fainted = false;
    boostAmount = 0;
    shieldAmount = 0;
}

Codemon::Codemon(const string& n, const string& t, const string& desc, int lvl, int hp) {
    name = n;
    type = t;
    description = desc;
    level = lvl;
    maxHP = hp;
    currentHP = hp;
    skillCount = 0;
    fainted = false;
    boostAmount = 0;
    shieldAmount = 0;
}

// Copy constructor
Codemon::Codemon(const Codemon& other) {
    name = other.name;
    type = other.type;
    description = other.description;
    level = other.level;
    currentHP = other.currentHP;
    maxHP = other.maxHP;
    skillCount = other.skillCount;
    fainted = other.fainted;
    boostAmount = other.boostAmount;
    shieldAmount = other.shieldAmount;

    // Copy skills
    for (int i = 0; i < skillCount; i++) {
        skills[i] = other.skills[i];
    }
}

// Assignment operator
Codemon& Codemon::operator=(const Codemon& other) {
    if (this != &other) {
        name = other.name;
        type = other.type;
        description = other.description;
        level = other.level;
        currentHP = other.currentHP;
        maxHP = other.maxHP;
        skillCount = other.skillCount;
        fainted = other.fainted;
        boostAmount = other.boostAmount;
        shieldAmount = other.shieldAmount;

        // Copy skills
        for (int i = 0; i < skillCount; i++) {
            skills[i] = other.skills[i];
        }
    }
    return *this;
}

// Destructor
Codemon::~Codemon() {
    // No dynamic memory to deallocate
}

void Codemon::setCurrentHP(int hp) {
    currentHP = hp;
    if (currentHP < 0) {
        currentHP = 0;
    }
    if (currentHP > maxHP) {
        currentHP = maxHP;
    }
    fainted = (currentHP <= 0);
}

bool Codemon::addSkill(const Skill& skill) {
    if (skillCount < 5) {
        skills[skillCount] = skill;
        skillCount++;
        return true;
    }
    return false;
}

void Codemon::resetStatusEffects() {
    boostAmount = 0;
    shieldAmount = 0;
}

// Equality operators
bool Codemon::operator==(const Codemon& other) const {
    return (name == other.name && type == other.type && description == other.description);
}

bool Codemon::operator!=(const Codemon& other) const {
    return !(*this == other);
}

// Operator overloads for damage
Codemon Codemon::operator-(int damage) {
    Codemon temp = *this;
    temp.takeDamage(damage);
    return temp;
}

Codemon& Codemon::operator-=(int damage) {
    takeDamage(damage);
    return *this;
}

// Output operator - fixed to use getter methods
ostream& operator<<(ostream& os, const Codemon& codemon) {
    os << "Type: " << codemon.getType() << endl;
    os << "Level: " << codemon.getLevel() << endl;
    os << "HP: " << codemon.getCurrentHP() << "/" << codemon.getMaxHP();

    if (codemon.getBoostAmount() > 0) {
        os << endl << "Status: Attack Boosted (+" << codemon.getBoostAmount() << ")";
    }

    if (codemon.getShieldAmount() > 0) {
        os << endl << "Status: Shielded (" << codemon.getShieldAmount() << " damage absorption)";
    }

    return os;
}

void Codemon::takeDamage(int damage) {
    // Apply shield if available
    if (shieldAmount > 0) {
        if (damage <= shieldAmount) {
            // Shield absorbs all damage
            shieldAmount -= damage;
            damage = 0;
        } else {
            // Shield absorbs part of the damage
            damage -= shieldAmount;
            shieldAmount = 0;
        }
    }

    currentHP -= damage;
    if (currentHP < 0) {
        currentHP = 0;
    }
    fainted = (currentHP <= 0);
}

void Codemon::heal(int amount) {
    currentHP += amount;
    if (currentHP > maxHP) {
        currentHP = maxHP;
    }
}

void Codemon::applyBoost(int amount) {
    boostAmount = amount; // Not stackable, replaces existing boost
}

void Codemon::applyShield(int amount) {
    shieldAmount = amount; // Not stackable, replaces existing shield
}

void Codemon::useBoost() {
    boostAmount = 0;
}

void Codemon::useShield() {
    shieldAmount = 0;
}