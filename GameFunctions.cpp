// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: GameFunctions.cpp
// Assignment: Final Project
// Purpose: Implementation of game functions for Codémons Rebellion

#include "Arena.h"
#include "Codemon.h"
#include "Contestant.h"
#include "Item.h"
#include "Snuggladon.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <cmath>

using namespace std;

// External global variables (declared in main.cpp)
extern char terrainMap[12][12];
extern char visibleMap[12][12];
extern char itemMap[12][12];

// Function declaration for selectActiveCodemon (must be before it's used)
void selectActiveCodemon(Contestant& contestant);

// Load Items from file
void loadItemsFromFile(Item* itemPool, int& itemCount, const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    itemCount = 0;

    while (getline(file, line) && line != "(End of items.txt)") {
        // Parse line: name,effectType,effectAmount,description
        stringstream ss(line);
        string name, effectType, effectAmountStr, description;

        getline(ss, name, ',');
        getline(ss, effectType, ',');
        getline(ss, effectAmountStr, ',');
        getline(ss, description);

        // Convert effectAmountStr to integer
        int effectAmount = stoi(effectAmountStr);

        // Create and add item to pool
        itemPool[itemCount] = Item(name, effectType, effectAmount, description);
        itemCount++;
    }

    file.close();
}

// Setup Snuggladon with random types
void setupSnuggladon(Snuggladon& snuggladon, int totalContestants) {
    // Array of possible types
    string possibleTypes[] = {
        "Fire", "Water", "Grass", "Electric", "Ice", 
        "Rock", "Normal", "Psychic", "Dark", "Steel", "Fairy"
    };

    // Create a copy of possible types to mark used ones
    bool typeUsed[11] = {false};

    // Decide how many types Snuggladon will have (1-5)
    int maxTypeCount = 5;
    int typesToAssign = 1 + rand() % maxTypeCount;

    // Assign random types
    for (int i = 0; i < typesToAssign; i++) {
        // Find an unused type
        int typeIndex;
        do {
            typeIndex = rand() % 11;
        } while (typeUsed[typeIndex]);

        // Mark as used and add to Snuggladon
        typeUsed[typeIndex] = true;
        snuggladon.addType(possibleTypes[typeIndex]);
    }

    cout << "Snuggladon has been created!" << endl;
    cout << "Types: " << snuggladon.getTypesAsString() << endl;
    cout << "Max HP: " << snuggladon.getMaxHP() << endl;
    cout << "Base Attack: " << snuggladon.getBaseAttack() << endl;
}

// Get valid integer input within a range
int getValidIntInput(int min, int max, const string& prompt) {
    int input;
    bool validInput = false;

    do {
        cout << prompt;

        if (cin >> input) {
            if (input >= min && input <= max) {
                validInput = true;
            } else {
                cout << "Error: Input must be between " << min << " and " << max << ". Try again." << endl;
            }
        } else {
            cin.clear(); // Clear error flag
            cout << "Error: Invalid input. Please enter a number." << endl;
        }

        // Clear input buffer
        char c;
        while ((c = cin.get()) != '\n' && c != EOF);

    } while (!validInput);

    return input;
}

// Get valid character input from a set of valid characters
char getValidCharInput(const string& validChars, const string& prompt) {
    char input;
    bool validInput = false;

    do {
        cout << prompt;

        if (cin >> input) {
            input = toupper(input); // Convert to uppercase for comparison

            // Check if the input is in the set of valid characters
            bool found = false;
            for (size_t i = 0; i < validChars.length(); i++) {
                if (input == toupper(validChars[i])) {
                    found = true;
                    break;
                }
            }

            if (found) {
                validInput = true;
            } else {
                cout << "Error: Invalid choice. Please try again." << endl;
            }
        } else {
            cin.clear(); // Clear error flag
            cout << "Error: Invalid input. Please enter a character." << endl;
        }

        // Clear input buffer
        char c;
        while ((c = cin.get()) != '\n' && c != EOF);

    } while (!validInput);

    return input;
}

// Min function
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Select active Codemon for human player
void selectActiveCodemon(Contestant& contestant) {
    cout << "\nSelect your active Codemon:" << endl;

    for (int i = 0; i < contestant.getTeamSize(); i++) {
        cout << (i + 1) << ". " << contestant[i].getName() << " (" << contestant[i].getType() 
             << ") - HP: " << contestant[i].getCurrentHP() << "/" << contestant[i].getMaxHP() << endl;
    }

    int choice = getValidIntInput(1, contestant.getTeamSize(), "Enter choice (1-" + to_string(contestant.getTeamSize()) + "): ");
    contestant.setActiveCodemon(choice - 1);

    cout << contestant[choice - 1].getName() << " will lead the battle!" << endl;
}

// Setup a contestant with Codemons and skills
void setupContestant(Contestant& contestant, Codemon* codemonPool, int codemonCount, 
                    Skill* skillPool, int skillCount, bool isHuman) {
    cout << "\nSetting up team for " << contestant.getName() << endl;

    // For each Codemon in the team
    for (int i = 0; i < contestant.getTeamSize(); i++) {
        if (isHuman) {
            // Ask human player if they want to create custom Codemon or use random
            cout << "Codemon " << (i + 1) << ":" << endl;
            cout << "1. Create custom Codemon" << endl;
            cout << "2. Get random Codemon" << endl;
            int choice = getValidIntInput(1, 2, "Enter your choice (1-2): ");

            if (choice == 1) {
                // Create custom Codemon
                string name, type, description;
                int level, hp;

                cout << "Enter Codemon name: ";
                cin >> name;

                // Get valid type
                string validTypes[] = {"Fire", "Water", "Grass", "Electric", "Ice", 
                                      "Rock", "Normal", "Psychic", "Dark", "Steel", "Fairy"};

                cout << "Available types:" << endl;
                for (int j = 0; j < 11; j++) {
                    cout << (j + 1) << ". " << validTypes[j] << endl;
                }

                int typeChoice = getValidIntInput(1, 11, "Choose type (1-11): ");
                type = validTypes[typeChoice - 1];

                cin.ignore(); // Clear newline
                cout << "Enter description: ";
                getline(cin, description);

                level = getValidIntInput(1, 20, "Enter level (1-20): ");
                hp = getValidIntInput(200, 500, "Enter HP (200-500): ");

                Codemon customCodemon(name, type, description, level, hp);
                contestant.addCodemon(i, customCodemon);

                // Add skills
                cout << "\nAssigning skills to " << name << " (" << type << " type):" << endl;
                cout << "1. Create custom skills" << endl;
                cout << "2. Get random skills" << endl;
                choice = getValidIntInput(1, 2, "Enter your choice (1-2): ");

                if (choice == 1) {
                    // Custom skills
                    int numSkills = getValidIntInput(1, 5, "How many skills (1-5)? ");

                    for (int j = 0; j < numSkills; j++) {
                        string skillName, skillDesc;
                        int damage;

                        cout << "Skill " << (j + 1) << ":" << endl;
                        cout << "Enter skill name: ";
                        cin.ignore();
                        getline(cin, skillName);

                        damage = getValidIntInput(1, 50, "Enter damage (1-50): ");

                        cout << "Enter description: ";
                        cin.ignore();
                        getline(cin, skillDesc);

                        Skill customSkill(skillName, type, damage, skillDesc);
                        contestant[i].addSkill(customSkill);
                    }
                } else {
                    // Random skills of matching type
                    // Collect matching skills
                    int matchingSkills[skillCount];
                    int matchingCount = 0;

                    for (int j = 0; j < skillCount; j++) {
                        if (skillPool[j].getType() == type) {
                            matchingSkills[matchingCount] = j;
                            matchingCount++;
                        }
                    }

                    // Assign up to 5 random skills
                    int numSkills = min(5, matchingCount);
                    int assignedSkills = 0;

                    // Avoid duplicate skills by marking used ones
                    bool usedSkills[skillCount] = {false};

                    while (assignedSkills < numSkills) {
                        // Get a random skill index from matching skills
                        int randIndex = rand() % matchingCount;
                        int skillIndex = matchingSkills[randIndex];

                        if (!usedSkills[skillIndex]) {
                            contestant[i].addSkill(skillPool[skillIndex]);
                            usedSkills[skillIndex] = true;
                            assignedSkills++;
                        }
                    }
                }
            } else {
                // Random Codemon
                int randomIndex = rand() % codemonCount;
                contestant.addCodemon(i, codemonPool[randomIndex]);

                // Add random skills of matching type
                string codemonType = contestant[i].getType();

                // Collect matching skills
                int matchingSkills[skillCount];
                int matchingCount = 0;

                for (int j = 0; j < skillCount; j++) {
                    if (skillPool[j].getType() == codemonType) {
                        matchingSkills[matchingCount] = j;
                        matchingCount++;
                    }
                }

                // Assign up to 5 random skills
                int numSkills = min(5, matchingCount);
                int assignedSkills = 0;

                // Avoid duplicate skills by marking used ones
                bool usedSkills[skillCount] = {false};

                while (assignedSkills < numSkills) {
                    // Get a random skill index from matching skills
                    int randIndex = rand() % matchingCount;
                    int skillIndex = matchingSkills[randIndex];

                    if (!usedSkills[skillIndex]) {
                        contestant[i].addSkill(skillPool[skillIndex]);
                        usedSkills[skillIndex] = true;
                        assignedSkills++;
                    }
                }
            }
        } else {
            // AI contestant gets random Codemon
            int randomIndex = rand() % codemonCount;
            contestant.addCodemon(i, codemonPool[randomIndex]);

            // Add random skills of matching type
            string codemonType = contestant[i].getType();

            // Collect matching skills
            int matchingSkills[skillCount];
            int matchingCount = 0;

            for (int j = 0; j < skillCount; j++) {
                if (skillPool[j].getType() == codemonType) {
                    matchingSkills[matchingCount] = j;
                    matchingCount++;
                }
            }

            // Assign up to 5 random skills
            int numSkills = min(5, matchingCount);
            int assignedSkills = 0;

            // Avoid duplicate skills by marking used ones
            bool usedSkills[skillCount] = {false};

            while (assignedSkills < numSkills && matchingCount > 0) {
                // Get a random skill index from matching skills
                int randIndex = rand() % matchingCount;
                int skillIndex = matchingSkills[randIndex];

                if (!usedSkills[skillIndex]) {
                    contestant[i].addSkill(skillPool[skillIndex]);
                    usedSkills[skillIndex] = true;
                    assignedSkills++;
                }
            }
        }
    }

    // Select active Codemon for human player
    if (isHuman) {
        selectActiveCodemon(contestant);
    } else {
        // AI randomly selects an active Codemon
        contestant.setActiveCodemon(rand() % contestant.getTeamSize());
    }
}

// Initialize the game
void initializeGame(Arena& arena, Contestant** contestants, int contestantCount, 
                   Snuggladon& snuggladon, Codemon* codemonPool, int codemonCount, 
                   Skill* skillPool, int skillCount, Item* itemPool, int itemCount) {
    // Initialize terrain map
    arena.initializeTerrainMap(terrainMap);
    arena.initializeVisibleMap(visibleMap);
    arena.initializeItemMap(itemMap);

    // Calculate number of items to place (20% of grid cells)
    int gridSize = 12;
    int totalCells = gridSize * gridSize;
    int itemsToPlace = (totalCells * 20 + 99) / 100; // Round up 20%

    // Distribute items on the battlefield
    arena.distributeItems(itemMap, itemPool, itemCount, itemsToPlace);

    // Initialize the shared item queue
    int initialQueueCapacity = contestantCount * 2;
    for (int i = 0; i < initialQueueCapacity; i++) {
        // Add random items to the queue
        int randomItemIndex = rand() % itemCount;
        Contestant::addItem(itemPool[randomItemIndex]);
    }

    // Place Snuggladon randomly
    int row, col;
    do {
        row = rand() % gridSize;
        col = rand() % gridSize;
    } while (false); // No occupied check needed for initial placement

    snuggladon.setPosition(row, col);

    // Place each contestant's active Codemon randomly
    for (int i = 0; i < contestantCount; i++) {
        bool placed = false;
        while (!placed) {
            row = rand() % gridSize;
            col = rand() % gridSize;

            // Check if position is already occupied by Snuggladon or another contestant
            bool occupied = false;
            if (row == snuggladon.getCurrentRow() && col == snuggladon.getCurrentCol()) {
                occupied = true;
            }

            for (int j = 0; j < i; j++) {
                if (row == contestants[j]->getCurrentRow() && col == contestants[j]->getCurrentCol()) {
                    occupied = true;
                    break;
                }
            }

            if (!occupied) {
                contestants[i]->setPosition(row, col);
                placed = true;
            }
        }
    }

    // Initial scouting for all contestants
    for (int i = 0; i < contestantCount; i++) {
        // Update visible map for this contestant
        // This would normally happen in printVisibleMap, but we need to do it explicitly for initialization
        int contestantRow = contestants[i]->getCurrentRow();
        int contestantCol = contestants[i]->getCurrentCol();

        // Check if Snuggladon is visible from this position
        for (int r = contestantRow - 1; r <= contestantRow + 1; r++) {
            for (int c = contestantCol - 1; c <= contestantCol + 1; c++) {
                if (r >= 0 && r < gridSize && c >= 0 && c < gridSize) {
                    if (r == snuggladon.getCurrentRow() && c == snuggladon.getCurrentCol()) {
                        // Snuggladon is visible, update last known position
                        contestants[i]->setLastKnownSnuggladonPosition(r, c);
                    }
                }
            }
        }
    }

    cout << "\nGame initialized! The battle for Codémonia begins!" << endl;
}

// Player's turn
void playerTurn(Arena& arena, Contestant& player, Contestant** contestants, int contestantCount,
               Snuggladon& snuggladon, Item* itemPool, int itemCount, int turnCount) {
    cout << "\n===== " << player.getName() << "'s Turn =====" << endl;

    // Print the current visible map
    player.printVisibleMap();

    // 1. Movement phase
    cout << "\nMovement Phase:" << endl;
    cout << "Current position: (" << player.getCurrentRow() << ", " << player.getCurrentCol() << ")" << endl;
    cout << "Movement options:" << endl;
    cout << "Q (↖) W (↑) E (↗)" << endl;
    cout << "A (←)    D (→)" << endl;
    cout << "Z (↙) S (↓) C (↘)" << endl;
    cout << "X (stay in place)" << endl;

    char moveChoice = getValidCharInput("QWEASDZXC", "Enter your move: ");

    int newRow = player.getCurrentRow();
    int newCol = player.getCurrentCol();

    switch (moveChoice) {
        case 'Q': newRow--; newCol--; break; // Up-left
        case 'W': newRow--; break;           // Up
        case 'E': newRow--; newCol++; break; // Up-right
        case 'A': newCol--; break;           // Left
        case 'D': newCol++; break;           // Right
        case 'Z': newRow++; newCol--; break; // Down-left
        case 'S': newRow++; break;           // Down
        case 'C': newRow++; newCol++; break; // Down-right
        case 'X': break;                     // Stay
    }

    // Check if move is valid
    bool validMove = true;

    // Check boundaries
    if (newRow < 0 || newRow >= 12 || newCol < 0 || newCol >= 12) {
        cout << "Cannot move outside the battlefield!" << endl;
        validMove = false;
    }

    // Check for occupied tile
    if (validMove && moveChoice != 'X') {
        // Check if occupied by Snuggladon
        if (newRow == snuggladon.getCurrentRow() && newCol == snuggladon.getCurrentCol()) {
            cout << "Tile is occupied by Snuggladon!" << endl;
            validMove = false;
        }

        // Check if occupied by another contestant
        for (int i = 0; i < contestantCount; i++) {
            if (contestants[i] != &player && 
                newRow == contestants[i]->getCurrentRow() && 
                newCol == contestants[i]->getCurrentCol()) {
                cout << "Tile is occupied by " << contestants[i]->getName() << "!" << endl;
                validMove = false;
                break;
            }
        }
    }

    // If move is valid, update position
    if (validMove && moveChoice != 'X') {
        player.setPosition(newRow, newCol);
        cout << "Moved to position (" << newRow << ", " << newCol << ")" << endl;

        // Check if there's an item on this tile
        if (itemMap[newRow][newCol] == 'I') {
            // Generate a random item to add to the inventory
            int randomItemIndex = rand() % itemCount;
            Contestant::addItem(itemPool[randomItemIndex]);

            // Remove item from the map
            itemMap[newRow][newCol] = ' ';
        }
    } else if (moveChoice == 'X') {
        cout << "Stayed in place." << endl;
    }

    // 2. Scouting phase (automatically done when printing the visible map)
    cout << "\nScouting Phase:" << endl;

    // Update visible map based on current position
    int playerRow = player.getCurrentRow();
    int playerCol = player.getCurrentCol();

    // Check if Snuggladon is visible from this position
    bool snuggladonVisible = false;
    for (int r = playerRow - 1; r <= playerRow + 1; r++) {
        for (int c = playerCol - 1; c <= playerCol + 1; c++) {
            if (r >= 0 && r < 12 && c >= 0 && c < 12) {
                if (r == snuggladon.getCurrentRow() && c == snuggladon.getCurrentCol()) {
                    // Snuggladon is visible, update last known position
                    player.setLastKnownSnuggladonPosition(r, c);
                    snuggladonVisible = true;
                }
            }
        }
    }

    if (snuggladonVisible) {
        cout << "You've spotted Snuggladon at position (" 
             << snuggladon.getCurrentRow() << ", " << snuggladon.getCurrentCol() << ")!" << endl;
    }

    // Print updated visible map
    player.printVisibleMap();

    // 3. Item phase
    cout << "\nItem Phase:" << endl;

    Item nextItem;
    if (Contestant::peekNextItem(nextItem)) {
        cout << "Next available item: " << nextItem.getName() << endl;
        cout << "Description: " << nextItem.getDescription() << endl;
        cout << "Effect: ";

        if (nextItem.getEffectType() == "Heal") {
            cout << "Restores " << nextItem.getEffectAmount() << " HP" << endl;
        } else if (nextItem.getEffectType() == "Boost") {
            cout << "Boosts attack by " << nextItem.getEffectAmount() << endl;
        } else if (nextItem.getEffectType() == "Shield") {
            cout << "Provides shield that absorbs " << nextItem.getEffectAmount() << " damage" << endl;
        }

        char itemChoice = getValidCharInput("YN", "Use this item? (Y/N): ");

        if (itemChoice == 'Y') {
            Contestant::useNextItem(player.getActiveCodemon());
        } else {
            cout << "Item not used." << endl;
        }
    } else {
        cout << "No items available." << endl;
    }

    // 4. Battle phase
    cout << "\nBattle Phase:" << endl;

    // Check if Snuggladon is adjacent
    bool snuggladonAdjacent = false;
    int playerR = player.getCurrentRow();
    int playerC = player.getCurrentCol();
    int snuggladonR = snuggladon.getCurrentRow();
    int snuggladonC = snuggladon.getCurrentCol();

    // Check all 8 surrounding tiles
    for (int r = playerR - 1; r <= playerR + 1; r++) {
        for (int c = playerC - 1; c <= playerC + 1; c++) {
            if (r >= 0 && r < 12 && c >= 0 && c < 12) {
                if (r == snuggladonR && c == snuggladonC) {
                    snuggladonAdjacent = true;
                    break;
                }
            }
        }
        if (snuggladonAdjacent) break;
    }

    if (snuggladonAdjacent) {
        // Display Codemon and Snuggladon status
        cout << "Your active Codemon:" << endl;
        Codemon& activeCodemon = player.getActiveCodemon();
        cout << activeCodemon.getName() << " (" << activeCodemon.getType() << ")" << endl;
        cout << "HP: " << activeCodemon.getCurrentHP() << "/" << activeCodemon.getMaxHP() << endl;

        if (activeCodemon.getBoostAmount() > 0) {
            cout << "Status: Attack Boosted (+" << activeCodemon.getBoostAmount() << ")" << endl;
        }

        if (activeCodemon.getShieldAmount() > 0) {
            cout << "Status: Shielded (" << activeCodemon.getShieldAmount() << " damage absorption)" << endl;
        }

        // List skills
        cout << "\nAvailable skills:" << endl;
        for (int i = 0; i < activeCodemon.getSkillCount(); i++) {
            const Skill& skill = activeCodemon.getSkill(i);
            cout << (i + 1) << ". " << skill.getName() << " (" << skill.getType() 
                 << ") - Damage: " << skill.getBaseDamage() << endl;
            cout << "   " << skill.getDescription() << endl;
        }

        // Display Snuggladon's status
        cout << "\nSnuggladon status:" << endl;
        cout << "Types: " << snuggladon.getTypesAsString() << endl;
        cout << "HP: " << snuggladon.getCurrentHP() << "/" << snuggladon.getMaxHP() << endl;
        cout << "Status: " << snuggladon.getStatusEffects() << endl;

        // Ask if player wants to battle
        char battleChoice = getValidCharInput("YN", "Do you want to battle Snuggladon? (Y/N): ");

        if (battleChoice == 'Y') {
            // Execute battle
            arena.executeBattle(player, snuggladon, contestants, contestantCount, terrainMap);

            // Check if Codemon fainted
            if (player.getActiveCodemon().isFainted()) {
                cout << player.getActiveCodemon().getName() << " has fainted!" << endl;

                // Try to switch to next available Codemon
                if (player.switchToNextCodemon()) {
                    cout << "Switched to " << player.getActiveCodemon().getName() << "!" << endl;
                } else {
                    // No more Codemons available
                    player.decrementRemainingCodemons();
                    cout << player.getName() << " has been eliminated from the battle!" << endl;
                }
            }
        } else {
            cout << "Decided not to battle this turn." << endl;
        }
    } else {
        cout << "Snuggladon is not adjacent. No battle possible." << endl;
    }

    cout << "\n" << player.getName() << "'s turn complete." << endl;
}

// Computer player's turn
void computerTurn(Arena& arena, Contestant& computer, Contestant** contestants, int contestantCount,
                 Snuggladon& snuggladon, Item* itemPool, int itemCount) {
    cout << "\n===== " << computer.getName() << "'s Turn =====" << endl;

    // 1. Movement phase - random direction
    int currentRow = computer.getCurrentRow();
    int currentCol = computer.getCurrentCol();

    // Try to move in a random direction
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // Row offsets
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // Column offsets

    // Create list of valid moves
    int validMoves[8]; // Store indices of valid moves
    int validCount = 0;

    for (int i = 0; i < 8; i++) {
        int newRow = currentRow + dx[i];
        int newCol = currentCol + dy[i];

        // Check boundaries
        if (newRow < 0 || newRow >= 12 || newCol < 0 || newCol >= 12) {
            continue;
        }

        // Check occupancy
        bool occupied = false;
        if (newRow == snuggladon.getCurrentRow() && newCol == snuggladon.getCurrentCol()) {
            occupied = true;
        }

        for (int j = 0; j < contestantCount; j++) {
            if (contestants[j] != &computer && 
                newRow == contestants[j]->getCurrentRow() && 
                newCol == contestants[j]->getCurrentCol()) {
                occupied = true;
                break;
            }
        }

        if (!occupied) {
            validMoves[validCount] = i;
            validCount++;
        }
    }

    // If there are valid moves, choose one randomly
    if (validCount > 0) {
        int moveIndex = validMoves[rand() % validCount];
        int newRow = currentRow + dx[moveIndex];
        int newCol = currentCol + dy[moveIndex];

        computer.setPosition(newRow, newCol);
        cout << computer.getName() << " moved to position (" << newRow << ", " << newCol << ")" << endl;

        // Check if there's an item on this tile
        if (itemMap[newRow][newCol] == 'I') {
            // Generate a random item to add to the inventory
            int randomItemIndex = rand() % itemCount;
            Contestant::addItem(itemPool[randomItemIndex]);

            // Remove item from the map
            itemMap[newRow][newCol] = ' ';
            cout << computer.getName() << " found an item!" << endl;
        }
    } else {
        cout << computer.getName() << " couldn't move this turn." << endl;
    }

    // 2. Scouting phase (automatically updates visibility)
    cout << computer.getName() << " is scouting..." << endl;

    // Update if Snuggladon is visible from this position
    int computerRow = computer.getCurrentRow();
    int computerCol = computer.getCurrentCol();

    // Check if Snuggladon is visible from this position
    bool snuggladonVisible = false;
    for (int r = computerRow - 1; r <= computerRow + 1; r++) {
        for (int c = computerCol - 1; c <= computerCol + 1; c++) {
            if (r >= 0 && r < 12 && c >= 0 && c < 12) {
                if (r == snuggladon.getCurrentRow() && c == snuggladon.getCurrentCol()) {
                    // Snuggladon is visible, update last known position
                    computer.setLastKnownSnuggladonPosition(r, c);
                    snuggladonVisible = true;
                }
            }
        }
    }

    if (snuggladonVisible) {
        cout << computer.getName() << " spotted Snuggladon!" << endl;
    }

    // 3. Item phase - AI decision
    cout << "\nItem Phase:" << endl;

    Item nextItem;
    if (Contestant::peekNextItem(nextItem)) {
        // AI logic for item usage
        bool useItem = false;

        if (nextItem.getEffectType() == "Heal") {
            // Use healing item if HP is below 70% of max
            int currentHP = computer.getActiveCodemon().getCurrentHP();
            int maxHP = computer.getActiveCodemon().getMaxHP();
            if (currentHP < (maxHP * 0.7)) {
                useItem = true;
            }
        } else if (nextItem.getEffectType() == "Boost" || nextItem.getEffectType() == "Shield") {
            // Always use boost or shield items
            useItem = true;
        }

        if (useItem) {
            cout << computer.getName() << " used " << nextItem.getName() << "." << endl;
            Contestant::useNextItem(computer.getActiveCodemon());
        } else {
            cout << computer.getName() << " did not use any items." << endl;
        }
    } else {
        cout << "No items available." << endl;
    }

    // 4. Battle phase
    cout << "\nBattle Phase:" << endl;

    // Check if Snuggladon is adjacent
    bool snuggladonAdjacent = false;
    int computerR = computer.getCurrentRow();
    int computerC = computer.getCurrentCol();
    int snuggladonR = snuggladon.getCurrentRow();
    int snuggladonC = snuggladon.getCurrentCol();

    // Check all 8 surrounding tiles
    for (int r = computerR - 1; r <= computerR + 1; r++) {
        for (int c = computerC - 1; c <= computerC + 1; c++) {
            if (r >= 0 && r < 12 && c >= 0 && c < 12) {
                if (r == snuggladonR && c == snuggladonC) {
                    snuggladonAdjacent = true;
                    break;
                }
            }
        }
        if (snuggladonAdjacent) break;
    }

    if (snuggladonAdjacent) {
        // AI always initiates battle if Snuggladon is adjacent
        cout << computer.getName() << " is initiating battle with Snuggladon!" << endl;

        // Execute battle
        arena.executeBattle(computer, snuggladon, contestants, contestantCount, terrainMap);

        // Check if Codemon fainted
        if (computer.getActiveCodemon().isFainted()) {
            cout << computer.getActiveCodemon().getName() << " has fainted!" << endl;

            // Try to switch to next available Codemon
            if (computer.switchToNextCodemon()) {
                cout << computer.getName() << " switched to " << computer.getActiveCodemon().getName() << "!" << endl;
            } else {
                // No more Codemons available
                computer.decrementRemainingCodemons();
                cout << computer.getName() << " has been eliminated from the battle!" << endl;
            }
        }
    } else {
        cout << "Snuggladon is not adjacent to " << computer.getName() << ". No battle possible." << endl;
    }

    cout << "\n" << computer.getName() << "'s turn complete." << endl;
}

// Snuggladon's turn
void snuggladonTurn(Arena& arena, Snuggladon& snuggladon, Contestant** contestants, int contestantCount) {
    cout << "\n===== Snuggladon's Turn =====" << endl;

    // 1. Movement phase - target nearest Codemon
    int snuggladonRow = snuggladon.getCurrentRow();
    int snuggladonCol = snuggladon.getCurrentCol();

    // Find nearest contestant
    double minDistance = 999.0;
    int targetRow = -1;
    int targetCol = -1;
    Contestant* targetContestant = nullptr;

    for (int i = 0; i < contestantCount; i++) {
        if (!contestants[i]->isDefeated()) {
            int contestantRow = contestants[i]->getCurrentRow();
            int contestantCol = contestants[i]->getCurrentCol();

            double distance = sqrt(pow(contestantRow - snuggladonRow, 2) + 
                                 pow(contestantCol - snuggladonCol, 2));

            if (distance < minDistance) {
                minDistance = distance;
                targetRow = contestantRow;
                targetCol = contestantCol;
                targetContestant = contestants[i];
            }
        }
    }

    // If no targets found, skip turn
    if (targetContestant == nullptr) {
        cout << "Snuggladon found no targets..." << endl;
        return;
    }

    cout << "Snuggladon is targeting " << targetContestant->getName() << "!" << endl;

    // Determine best direction to move
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // Row offsets
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // Column offsets

    double bestDistance = minDistance;
    int bestDirection = -1;

    for (int i = 0; i < 8; i++) {
        int newRow = snuggladonRow + dx[i];
        int newCol = snuggladonCol + dy[i];

        // Check boundaries
        if (newRow < 0 || newRow >= 12 || newCol < 0 || newCol >= 12) {
            continue;
        }

        // Check occupancy
        bool occupied = false;
        for (int j = 0; j < contestantCount; j++) {
            if (newRow == contestants[j]->getCurrentRow() && 
                newCol == contestants[j]->getCurrentCol()) {
                occupied = true;
                break;
            }
        }

        if (!occupied) {
            double newDistance = sqrt(pow(targetRow - newRow, 2) + pow(targetCol - newCol, 2));
            if (newDistance < bestDistance) {
                bestDistance = newDistance;
                bestDirection = i;
            }
        }
    }

    // Move in best direction if found
    if (bestDirection != -1) {
        int newRow = snuggladonRow + dx[bestDirection];
        int newCol = snuggladonCol + dy[bestDirection];

        snuggladon.setPosition(newRow, newCol);
        cout << "Snuggladon moved to position (" << newRow << ", " << newCol << ")" << endl;
    } else {
        cout << "Snuggladon couldn't find a good move and stays in place." << endl;
    }

    // 2. Battle phase - check for adjacent contestants
    int adjacentContestants = 0;
    Contestant* adjacentTargets[8]; // Max 8 possible adjacent contestants

    for (int i = 0; i < contestantCount; i++) {
        if (!contestants[i]->isDefeated()) {
            int contestantRow = contestants[i]->getCurrentRow();
            int contestantCol = contestants[i]->getCurrentCol();

            // Check if adjacent
            if (abs(contestantRow - snuggladon.getCurrentRow()) <= 1 && 
                abs(contestantCol - snuggladon.getCurrentCol()) <= 1) {
                adjacentTargets[adjacentContestants] = contestants[i];
                adjacentContestants++;
            }
        }
    }

    if (adjacentContestants > 0) {
        cout << "\nSnuggladon found " << adjacentContestants << " adjacent targets!" << endl;

        // Choose skill based on priority:
        int skillChoice;

        // Priority 1: Survival - use Ancient Renewal if HP is low
        if (snuggladon.getCurrentHP() <= snuggladon.getMaxHP() * 0.35) {
            skillChoice = Snuggladon::ANCIENT_RENEWAL;
        }
        // Priority 2: Area Threat - use Cataclysm Strike if 2+ enemies and available
        else if (adjacentContestants >= 2 && snuggladon.canUseCataclysm()) {
            skillChoice = Snuggladon::CATACLYSM_STRIKE;
        }
        // Priority 3: Buff Up - use Primal Fury
        else if (!snuggladon.isEnraged()) {
            skillChoice = Snuggladon::PRIMAL_FURY;
        }
        // Priority 4: Defense - use Stonehide Armor if no shield and not many enemies
        else if (snuggladon.getShieldAmount() == 0 && adjacentContestants < 2) {
            skillChoice = Snuggladon::STONEHIDE_ARMOR;
        }
        // Priority 5: Standard Attack - use Savage Bite
        else {
            skillChoice = Snuggladon::SAVAGE_BITE;
        }

        // Check if same skill as last turn
        if (skillChoice == snuggladon.getLastUsedSkill()) {
            // Can't use same skill twice in a row, pick a different one
            for (int i = 0; i < 5; i++) {
                if (i != skillChoice && i != snuggladon.getLastUsedSkill()) {
                    // Check if Cataclysm Strike is available
                    if (i == Snuggladon::CATACLYSM_STRIKE && !snuggladon.canUseCataclysm()) {
                        continue;
                    }
                    skillChoice = i;
                    break;
                }
            }
        }

        // Use the selected skill
        cout << snuggladon.useSkill(skillChoice, adjacentContestants > 1) << endl;

        // Apply effects to targets
        if (skillChoice == Snuggladon::CATACLYSM_STRIKE) {
            // Area attack on all adjacent targets
            for (int i = 0; i < adjacentContestants; i++) {
                Codemon& targetCodemon = adjacentTargets[i]->getActiveCodemon();

                int damage = arena.calculateDamage(snuggladon, targetCodemon, snuggladon.isEnraged());
                targetCodemon.takeDamage(damage);

                cout << "Snuggladon dealt " << damage << " damage to " 
                     << targetCodemon.getName() << "!" << endl;

                // Check if target fainted
                if (targetCodemon.isFainted()) {
                    cout << targetCodemon.getName() << " has fainted!" << endl;

                    // Try to switch to next Codemon
                    if (adjacentTargets[i]->switchToNextCodemon()) {
                        cout << adjacentTargets[i]->getName() << " switched to " 
                             << adjacentTargets[i]->getActiveCodemon().getName() << "!" << endl;
                    } else {
                        // No more Codemons
                        adjacentTargets[i]->decrementRemainingCodemons();
                        cout << adjacentTargets[i]->getName() << " has been eliminated!" << endl;
                    }
                }
            }
        } else if (skillChoice == Snuggladon::SAVAGE_BITE) {
            // Single target attack on nearest opponent
            Contestant* target = adjacentTargets[0]; // Choose first adjacent target
            Codemon& targetCodemon = target->getActiveCodemon();

            int damage = arena.calculateDamage(snuggladon, targetCodemon, snuggladon.isEnraged());
            targetCodemon.takeDamage(damage);

            cout << "Snuggladon dealt " << damage << " damage to " 
                 << targetCodemon.getName() << "!" << endl;

            // Check if target fainted
            if (targetCodemon.isFainted()) {
                cout << targetCodemon.getName() << " has fainted!" << endl;

                // Try to switch to next Codemon
                if (target->switchToNextCodemon()) {
                    cout << target->getName() << " switched to " 
                         << target->getActiveCodemon().getName() << "!" << endl;
                } else {
                    // No more Codemons
                    target->decrementRemainingCodemons();
                    cout << target->getName() << " has been eliminated!" << endl;
                }
            }
        }
    } else {
        cout << "No contestants are adjacent to Snuggladon. No battle occurs." << endl;
    }

    cout << "\nSnuggladon's turn complete." << endl;
}

// Redistribute items on the battlefield
void redistributeItems(Arena& arena, Item* itemPool, int itemCount) {
    cout << "\n===== Redistributing Uncollected Items =====" << endl;

    // Count uncollected items
    int uncollectedCount = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (itemMap[i][j] == 'I') {
                uncollectedCount++;
            }
        }
    }

    // Redistribute if there are any items left
    if (uncollectedCount > 0) {
        arena.distributeItems(itemMap, itemPool, itemCount, uncollectedCount);
        cout << uncollectedCount << " items have been redistributed on the battlefield." << endl;
    } else {
        cout << "No items to redistribute." << endl;
    }
}

// Check if game is over
bool isGameOver(Contestant** contestants, int contestantCount, Snuggladon& snuggladon) {
    // Game is over if Snuggladon is defeated
    if (snuggladon.isDefeated()) {
        return true;
    }

    // Game is over if all contestants are defeated
    bool allDefeated = true;
    for (int i = 0; i < contestantCount; i++) {
        if (!contestants[i]->isDefeated()) {
            allDefeated = false;
            break;
        }
    }

    return allDefeated;
}