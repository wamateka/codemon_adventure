// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Arena4.cpp
// Assignment: Final Project
// Purpose: Battle arena class implementation - Part 4 (Movement and Items)

#include "Arena.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

// Movement validation
bool Arena::isValidMove(int row, int col) {
    return (row >= 0 && row < 12 && col >= 0 && col < 12);
}

// Check if tile is occupied
bool Arena::isTileOccupied(int row, int col, Contestant** contestants, int contestantCount, const Snuggladon& snuggladon) {
    // Check if occupied by Snuggladon
    if (row == snuggladon.getCurrentRow() && col == snuggladon.getCurrentCol()) {
        return true;
    }

    // Check if occupied by any contestant
    for (int i = 0; i < contestantCount; i++) {
        if (row == contestants[i]->getCurrentRow() && col == contestants[i]->getCurrentCol()) {
            return true;
        }
    }

    return false;
}

// Collect item from the battlefield
void Arena::collectItem(Contestant& contestant, int row, int col, char itemMap[12][12], Item* itemPool, int itemPoolSize) {
    // Check if there's an item at this position
    if (itemMap[row][col] == 'I') {
        // Generate random item from pool
        int randomItemIndex = rand() % itemPoolSize;
        Contestant::addItem(itemPool[randomItemIndex]);

        // Remove item from the map
        itemMap[row][col] = ' ';

        cout << "Found a " << itemPool[randomItemIndex].getName() << "! Added to inventory." << endl;
    }
}

// Move contestant and handle item collection
void Arena::moveContestant(Contestant& contestant, int newRow, int newCol, char itemMap[12][12], Item* itemPool, int itemPoolSize) {
    // Update position
    contestant.setPosition(newRow, newCol);

    // Check if new position has an item
    collectItem(contestant, newRow, newCol, itemMap, itemPool, itemPoolSize);
}

// Computer-controlled contestant movement
void Arena::computerMove(Contestant& computer, char itemMap[12][12], Item* itemPool, int itemPoolSize, 
                       Contestant** contestants, int contestantCount, const Snuggladon& snuggladon) {
    // Current position
    int currentRow = computer.getCurrentRow();
    int currentCol = computer.getCurrentCol();

    // Possible moves (including diagonals)
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Collect valid moves
    int validMoves[8]; // Store indices of valid moves
    int validCount = 0;

    for (int i = 0; i < 8; i++) {
        int newRow = currentRow + dx[i];
        int newCol = currentCol + dy[i];

        // Check boundaries
        if (newRow < 0 || newRow >= 12 || newCol < 0 || newCol >= 12) {
            continue;
        }

        // Check if occupied by Snuggladon
        if (newRow == snuggladon.getCurrentRow() && newCol == snuggladon.getCurrentCol()) {
            continue;
        }

        // Check if occupied by another contestant
        bool occupied = false;
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

        // Move and check for items
        moveContestant(computer, newRow, newCol, itemMap, itemPool, itemPoolSize);

        cout << computer.getName() << " moved to position (" << newRow << ", " << newCol << ")" << endl;
    } else {
        cout << computer.getName() << " couldn't find a valid move and stays in place." << endl;
    }
}

// Snuggladon movement logic
void Arena::snuggladonMove(Snuggladon& snuggladon, Contestant** contestants, int contestantCount) {
    // Find nearest contestant
    int currentRow = snuggladon.getCurrentRow();
    int currentCol = snuggladon.getCurrentCol();

    // Find nearest active contestant
    double minDistance = 999.9;
    int targetRow = -1;
    int targetCol = -1;
    Contestant* targetContestant = nullptr;

    for (int i = 0; i < contestantCount; i++) {
        if (!contestants[i]->isDefeated()) {
            int contestantRow = contestants[i]->getCurrentRow();
            int contestantCol = contestants[i]->getCurrentCol();

            double distance = calculateDistance(currentRow, currentCol, contestantRow, contestantCol);

            if (distance < minDistance) {
                minDistance = distance;
                targetRow = contestantRow;
                targetCol = contestantCol;
                targetContestant = contestants[i];
            }
        }
    }

    // If no target found, don't move
    if (targetContestant == nullptr) {
        cout << "Snuggladon couldn't find any targets and remains stationary." << endl;
        return;
    }

    // Find best move toward target
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    double bestDistance = minDistance;
    int bestDirection = -1;

    for (int i = 0; i < 8; i++) {
        int newRow = currentRow + dx[i];
        int newCol = currentCol + dy[i];

        // Check boundaries
        if (newRow < 0 || newRow >= 12 || newCol < 0 || newCol >= 12) {
            continue;
        }

        // Check if occupied by a contestant
        bool occupied = false;
        for (int j = 0; j < contestantCount; j++) {
            if (newRow == contestants[j]->getCurrentRow() && 
                newCol == contestants[j]->getCurrentCol()) {
                occupied = true;
                break;
            }
        }

        if (!occupied) {
            double newDistance = calculateDistance(newRow, newCol, targetRow, targetCol);

            if (newDistance < bestDistance) {
                bestDistance = newDistance;
                bestDirection = i;
            }
        }
    }

    // Move in best direction if found
    if (bestDirection != -1) {
        int newRow = currentRow + dx[bestDirection];
        int newCol = currentCol + dy[bestDirection];

        snuggladon.setPosition(newRow, newCol);

        cout << "Snuggladon moved toward " << targetContestant->getName() 
             << " to position (" << newRow << ", " << newCol << ")" << endl;
    } else {
        cout << "Snuggladon couldn't find a good move and stays in place." << endl;
    }
}

// Use an item from inventory
void Arena::useItem(Contestant& contestant) {
    cout << "Item Phase:" << endl;

    // Check if there are any items available
    if (Contestant::getItemCount() == 0) {
        cout << "No items available in inventory." << endl;
        return;
    }

    // Peek at the next item
    Item nextItem;
    if (Contestant::peekNextItem(nextItem)) {
        cout << "Next available item: " << nextItem.getName() << endl;
        cout << "Description: " << nextItem.getDescription() << endl;

        // For AI players, use logic to decide if item should be used
        if (contestant.isComputerPlayer()) {
            bool useItem = false;

            if (nextItem.getEffectType() == "Heal") {
                // Use healing item if HP is below 70% of max
                int currentHP = contestant.getActiveCodemon().getCurrentHP();
                int maxHP = contestant.getActiveCodemon().getMaxHP();
                if (currentHP < (maxHP * 0.7)) {
                    useItem = true;
                }
            } else if (nextItem.getEffectType() == "Boost" || 
                      nextItem.getEffectType() == "Shield") {
                // Always use boost or shield items
                useItem = true;
            }

            if (useItem) {
                Contestant::useNextItem(contestant.getActiveCodemon());
                cout << contestant.getName() << " used " << nextItem.getName() << "." << endl;
            } else {
                cout << contestant.getName() << " decided not to use an item." << endl;
            }
        } else {
            // For human players, ask if they want to use the item
            cout << "Do you want to use this item? (Y/N): ";
            char choice;
            cin >> choice;

            if (toupper(choice) == 'Y') {
                Contestant::useNextItem(contestant.getActiveCodemon());
                cout << "Item used successfully!" << endl;
            } else {
                cout << "Item not used." << endl;
            }
        }
    }
}