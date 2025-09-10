// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Snuggladon.cpp
// Assignment: Final Project
// Purpose: Snuggladon (boss) class implementation

#include "Snuggladon.h"
#include <cstdlib>
#include <sstream>

// Constructor
Snuggladon::Snuggladon(int totalContestants) {
    // Calculate stats based on contestant count
    maxHP = 1500 + 200 * totalContestants;
    currentHP = maxHP;
    baseAttack = 150 + 20 * (totalContestants - 3);

    // Initialize position
    currentRow = 5;
    currentCol = 5;

    // Initialize types
    typeCount = 0;

    // Initialize skill tracking
    lastUsedSkill = SAVAGE_BITE; // Start with any skill
    for (int i = 0; i < 4; i++) {
        skillsUsedSinceLastCataclysm[i] = false;
    }

    // Initialize status effects
    enraged = false;
    shieldAmount = 0;
}

// Get type at specific index
string Snuggladon::getType(int index) const {
    if (index >= 0 && index < typeCount) {
        return types[index];
    }
    return "Unknown";
}

// Combat mechanics
void Snuggladon::takeDamage(int damage) {
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
}

bool Snuggladon::canUseCataclysm() const {
    // Check if all other skills have been used
    for (int i = 0; i < 4; i++) {
        if (!skillsUsedSinceLastCataclysm[i]) {
            return false;
        }
    }
    return true;
}

string Snuggladon::useSkill(int skillIndex, bool multipleAdjacentEnemies) {
    // Can't use same skill twice in a row
    if (skillIndex == lastUsedSkill) {
        return "Cannot use the same skill twice in a row!";
    }

    // For Cataclysm, check if all other skills have been used
    if (skillIndex == CATACLYSM_STRIKE && !canUseCataclysm()) {
        return "Cannot use Cataclysm Strike until all other skills have been used!";
    }

    string result;

    // Apply skill effects
    switch (skillIndex) {
        case ANCIENT_RENEWAL:
            // Heal 25% of max HP
            currentHP += maxHP / 4;
            if (currentHP > maxHP) {
                currentHP = maxHP;
            }
            result = "Snuggladon uses Ancient Renewal and heals for " + 
                     to_string(maxHP / 4) + " HP!";

            // Mark this skill as used
            skillsUsedSinceLastCataclysm[0] = true;
            break;

        case PRIMAL_FURY:
            // Increase attack by 30%
            enraged = true;
            result = "Snuggladon uses Primal Fury and becomes enraged (+30% attack)!";

            // Mark this skill as used
            skillsUsedSinceLastCataclysm[1] = true;
            break;

        case STONEHIDE_ARMOR:
            // Apply shield
            shieldAmount = 50;
            result = "Snuggladon uses Stonehide Armor and gains 50 damage absorption!";

            // Mark this skill as used
            skillsUsedSinceLastCataclysm[2] = true;
            break;

        case CATACLYSM_STRIKE:
            // Area attack - damage calculated by caller
            result = "Snuggladon uses Cataclysm Strike";

            // If multiple adjacent enemies, mention it
            if (multipleAdjacentEnemies) {
                result += ", hitting all adjacent targets!";
            } else {
                result += " on the target!";
            }

            // Reset all skill usage tracking
            for (int i = 0; i < 4; i++) {
                skillsUsedSinceLastCataclysm[i] = false;
            }
            break;

        case SAVAGE_BITE:
            // Single target attack - damage calculated by caller
            result = "Snuggladon uses Savage Bite on a single target!";

            // Mark this skill as used
            skillsUsedSinceLastCataclysm[3] = true;
            break;
    }

    // Use up enraged effect after any attack
    if ((skillIndex == CATACLYSM_STRIKE || skillIndex == SAVAGE_BITE) && enraged) {
        enraged = false;
    }

    // Remember last used skill
    lastUsedSkill = static_cast<SkillType>(skillIndex);

    return result;
}

string Snuggladon::getSkillName(int skillIndex) const {
    switch (skillIndex) {
        case ANCIENT_RENEWAL: return "Ancient Renewal";
        case PRIMAL_FURY: return "Primal Fury";
        case STONEHIDE_ARMOR: return "Stonehide Armor";
        case CATACLYSM_STRIKE: return "Cataclysm Strike";
        case SAVAGE_BITE: return "Savage Bite";
        default: return "Unknown Skill";
    }
}

string Snuggladon::getSkillDescription(int skillIndex) const {
    switch (skillIndex) {
        case ANCIENT_RENEWAL: 
            return "Restores 25% of Snuggladon's maximum HP.";
        case PRIMAL_FURY: 
            return "Increases attack power by +30% for the next attack.";
        case STONEHIDE_ARMOR: 
            return "Absorbs 50 points of incoming damage.";
        case CATACLYSM_STRIKE: 
            return "Deals 100% Snuggladon's base attack to all adjacent targets.";
        case SAVAGE_BITE: 
            return "Deals 100% of Snuggladon's base attack power as damage to a single target.";
        default: 
            return "Unknown Skill";
    }
}

// Type management
void Snuggladon::addType(const string& type) {
    // Check if we have room for more types
    if (typeCount >= 11) {
        return; // Can't add more types
    }

    // Check if type already exists
    for (int i = 0; i < typeCount; i++) {
        if (types[i] == type) {
            return; // Type already exists
        }
    }

    // Add the new type
    types[typeCount] = type;
    typeCount++;
}

bool Snuggladon::hasType(const string& type) const {
    for (int i = 0; i < typeCount; i++) {
        if (types[i] == type) {
            return true;
        }
    }
    return false;
}

string Snuggladon::getTypesAsString() const {
    if (typeCount == 0) {
        return "None";
    }

    stringstream ss;
    for (int i = 0; i < typeCount; i++) {
        ss << types[i];
        if (i < typeCount - 1) {
            ss << ", ";
        }
    }

    return ss.str();
}

string Snuggladon::getStatusEffects() const {
    stringstream ss;

    if (enraged) {
        ss << "Enraged (+30% attack) ";
    }

    if (shieldAmount > 0) {
        ss << "Shielded (" << shieldAmount << " damage absorption) ";
    }

    string result = ss.str();
    if (result.empty()) {
        return "None";
    }

    return result;
}