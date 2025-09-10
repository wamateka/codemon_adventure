// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Arena3.cpp
// Assignment: Final Project
// Purpose: Battle arena class implementation - Part 3 (Damage and Battle)

#include "Arena.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <cctype>  // For toupper

using namespace std;

// Damage calculation for Codemon vs Codemon
int Arena::calculateDamage(const Codemon& attacker, const Codemon& defender) {
    if (attacker.getSkillCount() <= 0) {
        cout << "No skills available!" << endl;
        return 0;
    }

    // Get attacker's active skill
    int skillIndex = rand() % attacker.getSkillCount();
    const Skill& skill = attacker.getSkill(skillIndex);

    // Calculate base damage
    int baseDamage = skill.getBaseDamage() + attacker.getBoostAmount();

    // Apply type multiplier
    float multiplier = getTypeMultiplier(skill.getType(), defender.getType());

    // Calculate final damage
    int effectiveDamage = static_cast<int>(baseDamage * multiplier);

    // Account for defender's shield
    effectiveDamage -= defender.getShieldAmount();
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    cout << attacker.getName() << " uses " << skill.getName() 
         << " (" << skill.getType() << " type, base damage: " << skill.getBaseDamage() << ")" << endl;

    if (multiplier > 1.0f) {
        cout << "It's super effective! ";
    } else if (multiplier < 1.0f) {
        cout << "It's not very effective... ";
    }

    cout << "Dealt " << effectiveDamage << " damage!" << endl;

    return effectiveDamage;
}

// Damage calculation for Codemon vs Codemon with specific skill
int Arena::calculateDamage(const Codemon& attacker, const Codemon& defender, int skillIndex) {
    if (skillIndex < 0 || skillIndex >= attacker.getSkillCount()) {
        cout << "Invalid skill index. Using random skill instead." << endl;
        return calculateDamage(attacker, defender);
    }

    // Get the specified skill
    const Skill& skill = attacker.getSkill(skillIndex);

    // Calculate base damage
    int baseDamage = skill.getBaseDamage() + attacker.getBoostAmount();

    // Apply type multiplier
    float multiplier = getTypeMultiplier(skill.getType(), defender.getType());

    // Calculate final damage
    int effectiveDamage = static_cast<int>(baseDamage * multiplier);

    // Account for defender's shield
    effectiveDamage -= defender.getShieldAmount();
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    cout << attacker.getName() << " uses " << skill.getName() 
         << " (" << skill.getType() << " type, base damage: " << skill.getBaseDamage() << ")" << endl;

    if (multiplier > 1.0f) {
        cout << "It's super effective! ";
    } else if (multiplier < 1.0f) {
        cout << "It's not very effective... ";
    }

    cout << "Dealt " << effectiveDamage << " damage!" << endl;

    return effectiveDamage;
}

// Damage calculation for Codemon vs Snuggladon
int Arena::calculateDamage(const Codemon& attacker, const Snuggladon& defender) {
    if (attacker.getSkillCount() <= 0) {
        cout << "No skills available!" << endl;
        return 0;
    }

    // Get attacker's active skill
    int skillIndex = rand() % attacker.getSkillCount();
    const Skill& skill = attacker.getSkill(skillIndex);

    // Calculate base damage
    int baseDamage = skill.getBaseDamage() + attacker.getBoostAmount();

    // Apply type multiplier against all of Snuggladon's types
    float multiplier = getTypeMultiplier(skill.getType(), defender);

    // Calculate final damage
    int effectiveDamage = static_cast<int>(baseDamage * multiplier);

    // Account for defender's shield
    effectiveDamage -= defender.getShieldAmount();
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    cout << attacker.getName() << " uses " << skill.getName() 
         << " (" << skill.getType() << " type, base damage: " << skill.getBaseDamage() << ")" << endl;

    if (multiplier > 1.0f) {
        cout << "It's super effective! ";
    } else if (multiplier < 1.0f) {
        cout << "It's not very effective... ";
    }

    cout << "Dealt " << effectiveDamage << " damage to Snuggladon!" << endl;

    return effectiveDamage;
}

// Damage calculation for Codemon vs Snuggladon with specific skill
int Arena::calculateDamage(const Codemon& attacker, const Snuggladon& defender, int skillIndex) {
    if (skillIndex < 0 || skillIndex >= attacker.getSkillCount()) {
        cout << "Invalid skill index. Using random skill instead." << endl;
        return calculateDamage(attacker, defender);
    }

    // Get the specified skill
    const Skill& skill = attacker.getSkill(skillIndex);

    // Calculate base damage
    int baseDamage = skill.getBaseDamage() + attacker.getBoostAmount();

    // Apply type multiplier against all of Snuggladon's types
    float multiplier = getTypeMultiplier(skill.getType(), defender);

    // Calculate final damage
    int effectiveDamage = static_cast<int>(baseDamage * multiplier);

    // Account for defender's shield
    effectiveDamage -= defender.getShieldAmount();
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    cout << attacker.getName() << " uses " << skill.getName() 
         << " (" << skill.getType() << " type, base damage: " << skill.getBaseDamage() << ")" << endl;

    if (multiplier > 1.0f) {
        cout << "It's super effective! ";
    } else if (multiplier < 1.0f) {
        cout << "It's not very effective... ";
    }

    cout << "Dealt " << effectiveDamage << " damage to Snuggladon!" << endl;

    return effectiveDamage;
}

// Damage calculation for Snuggladon vs Codemon
int Arena::calculateDamage(const Snuggladon& attacker, const Codemon& defender, bool enraged) {
    // Calculate base damage
    int baseDamage = attacker.getBaseAttack();

    // Apply enraged bonus if active
    if (enraged) {
        baseDamage = static_cast<int>(baseDamage * 1.3f); // 30% boost
    }

    // Apply type multiplier from each of Snuggladon's types
    float multiplier = getTypeMultiplier(attacker, defender.getType());

    // Calculate final damage
    int effectiveDamage = static_cast<int>(baseDamage * multiplier);

    // Account for defender's shield
    effectiveDamage -= defender.getShieldAmount();
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    if (multiplier > 1.0f) {
        cout << "It's super effective! ";
    } else if (multiplier < 1.0f) {
        cout << "It's not very effective... ";
    }

    cout << "Snuggladon dealt " << effectiveDamage << " damage!" << endl;

    return effectiveDamage;
}

// Battle execution between contestant and Snuggladon
void Arena::executeBattle(Contestant& contestant, Snuggladon& snuggladon, 
                         Contestant** contestants, int contestantCount, char terrainMap[12][12]) {
    Codemon& codemon = contestant.getActiveCodemon();

    cout << "\n===== BATTLE BEGINS =====" << endl;
    cout << codemon.getName() << " vs Snuggladon!" << endl;

    // Continue battle rounds until one side is defeated
    bool battleContinues = true;
    bool retreatRequested = false;

    while (battleContinues && !retreatRequested) {
        // Random attack order for each round
        bool playerFirst = rand() % 2 == 0;

        cout << "\n----- BATTLE ROUND -----" << endl;

        // If player is human, let them choose a skill
        int skillChoice = 0;
        if (!contestant.isComputerPlayer()) {
            if (codemon.getSkillCount() <= 0) {
                cout << "Your Codemon has no skills!" << endl;
                return;
            }

            cout << "\nSnuggladon HP: " << snuggladon.getCurrentHP() << "/" << snuggladon.getMaxHP() << endl;
            cout << "Your " << codemon.getName() << " HP: " << codemon.getCurrentHP() << "/" << codemon.getMaxHP() << endl;

            cout << "\nChoose a skill to use (or 0 to retreat):" << endl;
            for (int i = 0; i < codemon.getSkillCount(); i++) {
                const Skill& skill = codemon.getSkill(i);
                cout << (i + 1) << ". " << skill.getName() << " (" << skill.getType() 
                    << ") - Damage: " << skill.getBaseDamage() << endl;
            }

            // Get valid skill choice or retreat
            bool validChoice = false;
            while (!validChoice) {
                cout << "Enter choice (0-" << codemon.getSkillCount() << "): ";
                cin >> skillChoice;

                if (skillChoice == 0) {
                    retreatRequested = true;
                    validChoice = true;
                } else if (skillChoice >= 1 && skillChoice <= codemon.getSkillCount()) {
                    validChoice = true;
                    skillChoice--; // Adjust to 0-based index
                } else {
                    cout << "Invalid choice. Try again." << endl;
                }
            }

            // Handle retreat
            if (retreatRequested) {
                cout << "You chose to retreat from battle." << endl;
                break;
            }
        } else {
            // AI chooses a random skill
            if (codemon.getSkillCount() > 0) {
                skillChoice = rand() % codemon.getSkillCount();
            } else {
                cout << "AI Codemon has no skills!" << endl;
                return;
            }
        }

        // Choose Snuggladon's skill based on priority
        int snuggladonSkillChoice = -1;

        // Get the number of adjacent enemies
        int adjacentEnemies = countAdjacentEnemies(snuggladon, contestants, contestantCount);

        // Priority 1: Survival - use Ancient Renewal if HP is low
        if (snuggladon.getCurrentHP() <= snuggladon.getMaxHP() * 0.35) {
            snuggladonSkillChoice = Snuggladon::ANCIENT_RENEWAL;
        }
        // Priority 2: Area Threat - use Cataclysm Strike if available and multiple enemies
        else if (adjacentEnemies >= 2 && snuggladon.canUseCataclysm()) {
            snuggladonSkillChoice = Snuggladon::CATACLYSM_STRIKE;
        }
        // Priority 3: Buff Up - use Primal Fury to increase damage
        else if (!snuggladon.isEnraged()) {
            snuggladonSkillChoice = Snuggladon::PRIMAL_FURY;
        }
        // Priority 4: Defense - use Stonehide Armor
        else if (snuggladon.getShieldAmount() == 0) {
            snuggladonSkillChoice = Snuggladon::STONEHIDE_ARMOR;
        }
        // Priority 5: Attack - use Savage Bite
        else {
            snuggladonSkillChoice = Snuggladon::SAVAGE_BITE;
        }

        // Ensure not using same skill twice in a row
        if (snuggladonSkillChoice == snuggladon.getLastUsedSkill()) {
            // Find a different skill
            for (int i = 0; i < 5; i++) {
                if (i != snuggladonSkillChoice && i != snuggladon.getLastUsedSkill()) {
                    // For Cataclysm Strike, check if it's available
                    if (i == Snuggladon::CATACLYSM_STRIKE && !snuggladon.canUseCataclysm()) {
                        continue;
                    }
                    snuggladonSkillChoice = i;
                    break;
                }
            }
        }

        // Execute battle round with random attack order
        if (playerFirst) {
            // Contestant attacks first
            cout << "\nContestant " << contestant.getName() << "'s " << codemon.getName() 
                << " attacks first!" << endl;

            // Calculate and apply damage to Snuggladon using the chosen skill
            int damage = calculateDamage(codemon, snuggladon, skillChoice);
            snuggladon.takeDamage(damage);

            // Use up boost if active
            if (codemon.getBoostAmount() > 0) {
                codemon.useBoost();
            }

            // Check if Snuggladon is defeated
            if (snuggladon.isDefeated()) {
                cout << "Snuggladon has been defeated!" << endl;
                battleContinues = false;
                continue; // Skip Snuggladon's turn
            }

            // Snuggladon's counter-attack
            cout << "\nSnuggladon counter-attacks!" << endl;
            cout << snuggladon.useSkill(snuggladonSkillChoice, adjacentEnemies > 1) << endl;

            // Calculate and apply damage to Codemon if using an attack skill
            if (snuggladonSkillChoice == Snuggladon::SAVAGE_BITE || 
                snuggladonSkillChoice == Snuggladon::CATACLYSM_STRIKE) {
                int damage = calculateDamage(snuggladon, codemon, snuggladon.isEnraged());
                codemon.takeDamage(damage);
            }

            // Use up shield if active
            if (codemon.getShieldAmount() > 0) {
                codemon.useShield();
            }
        } else {
            // Snuggladon attacks first
            cout << "\nSnuggladon attacks first!" << endl;
            cout << snuggladon.useSkill(snuggladonSkillChoice, adjacentEnemies > 1) << endl;

            // Calculate and apply damage to Codemon if using an attack skill
            if (snuggladonSkillChoice == Snuggladon::SAVAGE_BITE || 
                snuggladonSkillChoice == Snuggladon::CATACLYSM_STRIKE) {
                int damage = calculateDamage(snuggladon, codemon, snuggladon.isEnraged());
                codemon.takeDamage(damage);
            }

            // Use up shield if active
            if (codemon.getShieldAmount() > 0) {
                codemon.useShield();
            }

            // Check if Codemon is defeated
            if (codemon.isFainted()) {
                cout << codemon.getName() << " has been defeated!" << endl;
                battleContinues = false;
                continue; // Skip contestant's turn
            }

            // Contestant's counter-attack
            cout << "\nContestant " << contestant.getName() << "'s " << codemon.getName() 
                << " counter-attacks!" << endl;

            // Calculate and apply damage to Snuggladon using the chosen skill
            int damage = calculateDamage(codemon, snuggladon, skillChoice);
            snuggladon.takeDamage(damage);

            // Use up boost if active
            if (codemon.getBoostAmount() > 0) {
                codemon.useBoost();
            }
        }

        // Check if either side is defeated after the round
        if (codemon.isFainted()) {
            cout << codemon.getName() << " has been defeated!" << endl;
            battleContinues = false;
        }

        if (snuggladon.isDefeated()) {
            cout << "Snuggladon has been defeated!" << endl;
            battleContinues = false;
        }

        // Print round results if battle continues
        if (battleContinues) {
            cout << "\nRound results:" << endl;
            cout << codemon.getName() << ": " << codemon.getCurrentHP() << "/" << codemon.getMaxHP() << " HP" << endl;
            cout << "Snuggladon: " << snuggladon.getCurrentHP() << "/" << snuggladon.getMaxHP() << " HP" << endl;

            // Ask if human player wants to continue or retreat
            if (!contestant.isComputerPlayer()) {
                char continueChoice;
                cout << "Continue battle? (Y/N): ";
                cin >> continueChoice;

                if (toupper(continueChoice) != 'Y') {
                    cout << "You chose to retreat from battle." << endl;
                    retreatRequested = true;
                }
            }
        }
    }

    // Final battle summary
    cout << "\n===== BATTLE ENDED =====" << endl;
    cout << codemon.getName() << ": " << codemon.getCurrentHP() << "/" << codemon.getMaxHP() << " HP" << endl;
    cout << "Snuggladon: " << snuggladon.getCurrentHP() << "/" << snuggladon.getMaxHP() << " HP" << endl;

    // Handle defeated Codemon - have contestant switch to a new one
    if (codemon.isFainted()) {
        cout << "\n" << contestant.getName() << " must deploy a new Codemon!" << endl;

        // Try to switch to the next available Codemon
        if (contestant.switchToNextCodemon()) {
            cout << contestant.getName() << " has deployed " << contestant.getActiveCodemon().getName() << "!" << endl;

            // Randomly place the new Codemon on the battlefield
            randomlyPlaceContestant(contestant, terrainMap);
            cout << "New Codemon placed at position (" << contestant.getCurrentRow() 
                 << ", " << contestant.getCurrentCol() << ")" << endl;
        } else {
            // No more Codemons available
            contestant.decrementRemainingCodemons();
            cout << contestant.getName() << " has been eliminated from the battle!" << endl;
        }
    }
}

// Check if enemy is in range
bool Arena::isEnemyInRange(const Contestant& contestant, const Snuggladon& snuggladon) {
    int contestantRow = contestant.getCurrentRow();
    int contestantCol = contestant.getCurrentCol();
    int snuggladonRow = snuggladon.getCurrentRow();
    int snuggladonCol = snuggladon.getCurrentCol();

    // Check if Snuggladon is in any of the 8 adjacent tiles
    return (abs(contestantRow - snuggladonRow) <= 1 && abs(contestantCol - snuggladonCol) <= 1);
}

// Count adjacent enemies for Snuggladon
int Arena::countAdjacentEnemies(const Snuggladon& snuggladon, Contestant** contestants, int contestantCount) {
    int count = 0;
    int snuggladonRow = snuggladon.getCurrentRow();
    int snuggladonCol = snuggladon.getCurrentCol();

    for (int i = 0; i < contestantCount; i++) {
        if (!contestants[i]->isDefeated()) {
            int contestantRow = contestants[i]->getCurrentRow();
            int contestantCol = contestants[i]->getCurrentCol();

            if (abs(contestantRow - snuggladonRow) <= 1 && abs(contestantCol - snuggladonCol) <= 1) {
                count++;
            }
        }
    }

    return count;
}