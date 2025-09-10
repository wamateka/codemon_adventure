// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Snuggladon.h
// Assignment: Final Project
// Purpose: Snuggladon (boss) class definition

#ifndef SNUGGLADON_H
#define SNUGGLADON_H

#include <string>
using namespace std;

class Snuggladon {
public:
    // Skill type enum
    enum SkillType {
        ANCIENT_RENEWAL,
        PRIMAL_FURY,
        STONEHIDE_ARMOR,
        CATACLYSM_STRIKE,
        SAVAGE_BITE
    };

    // Constructor
    Snuggladon(int totalContestants);

    // Getters
    int getMaxHP() const { return maxHP; }
    int getCurrentHP() const { return currentHP; }
    int getBaseAttack() const { return baseAttack; }
    int getTypeCount() const { return typeCount; }
    string getType(int index) const;
    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }
    bool isEnraged() const { return enraged; }
    int getShieldAmount() const { return shieldAmount; }
    SkillType getLastUsedSkill() const { return lastUsedSkill; }

    // Position setters
    void setPosition(int row, int col) {
        currentRow = row;
        currentCol = col;
    }

    // Core mechanics
    void takeDamage(int damage);
    bool canUseCataclysm() const;
    string useSkill(int skillIndex, bool adjacentEnemyCount);
    string getSkillName(int skillIndex) const;
    string getSkillDescription(int skillIndex) const;

    // Types management
    void addType(const string& type);
    bool hasType(const string& type) const;
    string getTypesAsString() const;

    // Status
    bool isDefeated() const { return currentHP <= 0; }
    string getStatusEffects() const;

private:
    int maxHP;
    int currentHP;
    int baseAttack;

    // Fixed-size array for types with counter
    string types[11]; // Max 11 possible types
    int typeCount;

    SkillType lastUsedSkill;
    bool skillsUsedSinceLastCataclysm[4]; // Tracks if all 4 other skills have been used

    // Status effects
    bool enraged; // Primal Fury effect
    int shieldAmount; // Stonehide Armor effect

    int currentRow;
    int currentCol;
};

#endif // SNUGGLADON_H