//Consider Ethans Submission Ignore this Submission
//It is the same thing but Ehtan's is our official final submission Email: eagnnc@mast.edu
// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: main.cpp
// Assignment: Final Project - Codémons Rebellion
// Purpose: Main game loop and initialization

#include "Arena.h"
#include "Codemon.h"
#include "Contestant.h"
#include "Item.h"
#include "Snuggladon.h"
#include "GameFunctions.h"  // Include the new header
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Global arrays
char terrainMap[12][12];
char visibleMap[12][12];
char itemMap[12][12];

// Maximum pool sizes
const int MAX_CODEMONS = 100;
const int MAX_SKILLS = 200;
const int MAX_ITEMS = 50;
const int MAX_CONTESTANTS = 8;

int main() {
    // Set random seed
    srand(950);

    cout << "Welcome to Codémons Rebellion — United We Stand!" << endl;
    cout << "================================================" << endl << endl;

    // Load data from files
    Codemon* codemonPool = new Codemon[MAX_CODEMONS];
    Skill* skillPool = new Skill[MAX_SKILLS];
    Item* itemPool = new Item[MAX_ITEMS];

    int codemonCount = 0;
    int skillCount = 0;
    int itemCount = 0;

    loadCodemonsFromFile(codemonPool, codemonCount, "codemons.txt");
    loadSkillsFromFile(skillPool, skillCount, "skills.txt");
    loadItemsFromFile(itemPool, itemCount, "items.txt");

    // Create game objects
    Arena arena;
    Contestant* contestants[MAX_CONTESTANTS];

    // Game initialization
    // Get user input for game setup
    cout << "\nGame Setup" << endl;
    cout << "==========" << endl;

    int humanCount = getValidIntInput(1, 4, "Enter number of human players (1-4): ");
    int aiCount = getValidIntInput(1, 8 - humanCount, 
                                 "Enter number of computer-controlled contestants (1-" 
                                 + to_string(8 - humanCount) + "): ");

    int contestantCount = humanCount + aiCount;

    int codemonsPerTeam = getValidIntInput(1, 6, "Enter number of Codemons per team (1-6): ");

    // Create Snuggladon
    Snuggladon snuggladon(contestantCount);

    // Setup Snuggladon's types (1-5 random types)
    setupSnuggladon(snuggladon, contestantCount);

    // Create contestants
    for (int i = 0; i < humanCount; i++) {
        string name;
        cout << "Enter name for human player " << (i + 1) << ": ";
        cin >> name;

        contestants[i] = new Contestant(name, codemonsPerTeam, false);
        setupContestant(*contestants[i], codemonPool, codemonCount, skillPool, skillCount, true);
    }

    for (int i = 0; i < aiCount; i++) {
        string name = "AI-" + to_string(i + 1);
        contestants[humanCount + i] = new Contestant(name, codemonsPerTeam, true);
        setupContestant(*contestants[humanCount + i], codemonPool, codemonCount, skillPool, skillCount, false);
    }

    // Initialize shared item queue
    Contestant::initializeItemQueue(contestantCount);

    // Initialize game
    initializeGame(arena, contestants, contestantCount, snuggladon, 
                  codemonPool, codemonCount, skillPool, skillCount, itemPool, itemCount);

    // Main game loop
    int turnCount = 0;

    while (!isGameOver(contestants, contestantCount, snuggladon)) {
        turnCount++;
        cout << "\n\n======== TURN " << turnCount << " ========" << endl;

        // Each contestant takes their turn
        for (int i = 0; i < contestantCount; i++) {
            if (!contestants[i]->isDefeated()) {
                if (contestants[i]->isComputerPlayer()) {
                    computerTurn(arena, *contestants[i], contestants, contestantCount, snuggladon, itemPool, itemCount);
                } else {
                    playerTurn(arena, *contestants[i], contestants, contestantCount, snuggladon, itemPool, itemCount, turnCount);
                }

                // Check if game is over after this contestant's turn
                if (isGameOver(contestants, contestantCount, snuggladon)) {
                    break;
                }
            }
        }

        // Snuggladon's turn
        if (!snuggladon.isDefeated()) {
            snuggladonTurn(arena, snuggladon, contestants, contestantCount);
        }

        // Redistribute items every 5 turns
        if (turnCount % 5 == 0) {
            redistributeItems(arena, itemPool, itemCount);
        }
    }

    // Game over
    cout << "\n\n======== GAME OVER ========" << endl;

    if (snuggladon.isDefeated()) {
        cout << "Congratulations! The Academy Contestants have defeated Snuggladon!" << endl;
        cout << "Codémonia has been liberated!" << endl;
    } else {
        cout << "All contestants have been defeated!" << endl;
        cout << "Snuggladon remains in control of Codémonia..." << endl;
    }

    // Clean up
    for (int i = 0; i < contestantCount; i++) {
        delete contestants[i];
    }

    Contestant::cleanupItemQueue();
    delete[] codemonPool;
    delete[] skillPool;
    delete[] itemPool;

    return 0;
}
// Add these implementations to your main.cpp file after the main() function

void loadCodemonsFromFile(Codemon* codemonPool, int& codemonCount, const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    codemonCount = 0;

    while (getline(file, line) && codemonCount < MAX_CODEMONS) {
        if (line == "(end of codemons.txt)") {
            break;
        }

        // Parse line: name,type,description
        stringstream ss(line);
        string name, type, description;

        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, description);

        // Generate random HP between 200-500
        int maxHP = 200 + rand() % 301;

        // Generate random level between 1-20
        int level = 1 + rand() % 20;

        codemonPool[codemonCount] = Codemon(name, type, description, level, maxHP);
        codemonCount++;
    }

    file.close();
}

void loadSkillsFromFile(Skill* skillPool, int& skillCount, const string& filename) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    skillCount = 0;

    while (getline(file, line) && skillCount < MAX_SKILLS) {
        if (line == "(End of skills.txt)") {
            break;
        }

        // Parse line: name,type,damage,description
        stringstream ss(line);
        string name, type, damageStr, description;

        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, damageStr, ',');
        getline(ss, description);

        // Convert damageStr to integer
        int damage = stoi(damageStr);

        // Create and add skill to pool
        skillPool[skillCount] = Skill(name, type, damage, description);
        skillCount++;
    }

    file.close();
}