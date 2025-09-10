// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Arena2.cpp
// Assignment: Final Project
// Purpose: Battle arena class implementation - Part 2 (Map and Terrain)

#include "Arena.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

// Check terrain validity
bool Arena::isValidTerrain(char terrainMap[12][12], int row, int col, char terrain) {
    // Check adjacent cells for same terrain type
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];

        if (newRow >= 0 && newRow < 12 && newCol >= 0 && newCol < 12) {
            if (terrainMap[newRow][newCol] == terrain) {
                return false; // Same terrain found adjacent
            }
        }
    }
    return true;
}

// Euclidean distance calculation
double Arena::calculateDistance(int row1, int col1, int row2, int col2) const {
    return sqrt(pow(row1 - row2, 2) + pow(col1 - col2, 2));
}

// Initialize terrain map
void Arena::initializeTerrainMap(char terrainMap[12][12]) {
    char terrainTypes[] = {'F', 'M', 'P', 'W', 'S'};

    // Initialize with placeholder
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            terrainMap[i][j] = '?';
        }
    }

    // Fill with terrain types
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            bool placed = false;
            while (!placed) {
                char terrain = terrainTypes[rand() % 5];
                if (isValidTerrain(terrainMap, i, j, terrain)) {
                    terrainMap[i][j] = terrain;
                    placed = true;
                }
            }
        }
    }
}

// Initialize visible map
void Arena::initializeVisibleMap(char visibleMap[12][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            visibleMap[i][j] = '#';
        }
    }
}

// Initialize item map
void Arena::initializeItemMap(char itemMap[12][12]) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            itemMap[i][j] = ' '; // Empty space
        }
    }
}

// Distribute items on the battlefield
void Arena::distributeItems(char itemMap[12][12], Item* itemPool, int itemPoolSize, int itemCount) {
    // Clear existing items
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            itemMap[i][j] = ' ';
        }
    }

    // Place new items
    int placedItems = 0;
    while (placedItems < itemCount) {
        int row = rand() % 12;
        int col = rand() % 12;

        // Check if cell is empty
        if (itemMap[row][col] == ' ') {
            // Mark the cell
            itemMap[row][col] = 'I';
            placedItems++;
        }
    }
}

// Random contestant placement
void Arena::randomlyPlaceContestant(Contestant& contestant, char terrainMap[12][12]) {
    int row, col;
    bool placed = false;

    while (!placed) {
        row = rand() % 12;
        col = rand() % 12;

        // Make sure position is not already occupied
        placed = true;
        contestant.setPosition(row, col);
    }
}

// Print the terrain map (for debugging)
void Arena::printTerrainMap(char terrainMap[12][12]) {
    cout << "Terrain Map:" << endl;
    cout << "  ";
    for (int j = 0; j < 12; j++) {
        cout << j % 10 << " ";
    }
    cout << endl;

    for (int i = 0; i < 12; i++) {
        cout << i % 10 << " ";
        for (int j = 0; j < 12; j++) {
            cout << terrainMap[i][j] << " ";
        }
        cout << endl;
    }
}

// Print the full map with all entities (for debugging)
void Arena::printFullMap(char terrainMap[12][12], Contestant** contestants, int contestantCount, const Snuggladon& snuggladon) {
    // Create a display map
    char displayMap[12][12];

    // Copy terrain
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            displayMap[i][j] = terrainMap[i][j];
        }
    }

    // Add Snuggladon
    int snuggladonRow = snuggladon.getCurrentRow();
    int snuggladonCol = snuggladon.getCurrentCol();
    displayMap[snuggladonRow][snuggladonCol] = 'S';

    // Add contestants
    for (int i = 0; i < contestantCount; i++) {
        if (!contestants[i]->isDefeated()) {
            int row = contestants[i]->getCurrentRow();
            int col = contestants[i]->getCurrentCol();

            if (contestants[i]->isComputerPlayer()) {
                displayMap[row][col] = 'C'; // Computer-controlled
            } else {
                displayMap[row][col] = 'H'; // Human-controlled
            }
        }
    }

    // Print
    cout << "Full Map (S=Snuggladon, H=Human, C=Computer):" << endl;
    cout << "  ";
    for (int j = 0; j < 12; j++) {
        cout << j % 10 << " ";
    }
    cout << endl;

    for (int i = 0; i < 12; i++) {
        cout << i % 10 << " ";
        for (int j = 0; j < 12; j++) {
            cout << displayMap[i][j] << " ";
        }
        cout << endl;
    }

    // Print legend
    cout << "Terrain Legend: F=Forest, M=Mountain, P=Plains, W=Water, S=Swamp/Snuggladon" << endl;
}