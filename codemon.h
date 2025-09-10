// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Codemon.h
// Assignment: Final Project
// Purpose: Codemon class definition with expanded features

#ifndef CODEMON_H
#define CODEMON_H

#include <iostream>
#include <string>
using namespace std;

class Skill {
private:
    string name;
    string type;
    string description;
    int baseDamage;

public:
    // Constructors
    Skill();
    Skill(const string& n, const string& t, int dmg, const string& desc);

    // Getters
    string getName() const { return name; }
    string getType() const { return type; }
    string getDescription() const { return description; }
    int getBaseDamage() const { return baseDamage; }

    // Setters
    void setName(const string& n) { name = n; }
    void setType(const string& t) { type = t; }
    void setDescription(const string& desc) { description = desc; }
    void setBaseDamage(int dmg) { baseDamage = dmg; }
};

class Codemon {
private:
    string name;
    string type;
    string description;
    int level;
    int currentHP;
    int maxHP;
    Skill skills[5]; // Maximum 5 skills per Codemon
    int skillCount;
    bool fainted;

    // Status effects
    int boostAmount;
    int shieldAmount;

public:
    // Constructors
    Codemon();
    Codemon(const string& n, const string& t, const string& desc, int lvl, int hp);

    // Big Four (for proper memory management)
    Codemon(const Codemon& other); // Copy constructor
    Codemon& operator=(const Codemon& other); // Assignment operator
    ~Codemon(); // Destructor

    // Getters
    string getName() const { return name; }
    string getType() const { return type; }
    string getDescription() const { return description; }
    int getLevel() const { return level; }
    int getCurrentHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getSkillCount() const { return skillCount; }
    const Skill& getSkill(int index) const { return skills[index]; }
    bool isFainted() const { return fainted; }
    int getBoostAmount() const { return boostAmount; }
    int getShieldAmount() const { return shieldAmount; }

    // Setters
    void setName(const string& n) { name = n; }
    void setType(const string& t) { type = t; }
    void setDescription(const string& desc) { description = desc; }
    void setLevel(int lvl) { level = lvl; }
    void setCurrentHP(int hp);
    void setMaxHP(int hp) { maxHP = hp; }
    void setBoostAmount(int amount) { boostAmount = amount; }
    void setShieldAmount(int amount) { shieldAmount = amount; }

    // Skill management
    bool addSkill(const Skill& skill);
    void resetStatusEffects();

    // Overloaded operators
    bool operator==(const Codemon& other) const;
    bool operator!=(const Codemon& other) const;
    Codemon operator-(int damage);
    Codemon& operator-=(int damage);
    friend ostream& operator<<(ostream& os, const Codemon& codemon);

    // Battle methods
    void takeDamage(int damage);
    void heal(int amount);
    void applyBoost(int amount);
    void applyShield(int amount);
    void useBoost();
    void useShield();
    void resetFainted() { fainted = (currentHP <= 0); }
};

#endif // CODEMON_H