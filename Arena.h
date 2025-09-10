// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Arena.h
// Assignment: Final Project
// Purpose: Battle arena class with expanded features

#ifndef ARENA_H
#define ARENA_H

#include "Codemon.h"
#include "Contestant.h"
#include "Snuggladon.h"
#include <string>

using namespace std;

class Arena {
private:
    // Type advantage chart - expanded to 11x11
    float typeChart[11][11];

    // Type indices
    enum TypeIndex {
        FIRE = 0,
        WATER = 1,
        GRASS = 2,
        ELECTRIC = 3,
        ICE = 4,
        ROCK = 5,
        NORMAL = 6,
        PSYCHIC = 7,
        DARK = 8,
        STEEL = 9,
        FAIRY = 10
    };

    // Helper functions
    int getTypeIndex(const string& type) const;
    bool isValidTerrain(char terrainMap[12][12], int row, int col, char terrain);
    double calculateDistance(int row1, int col1, int row2, int col2) const;

public:
    // Constructor
    Arena();

    // Game initialization
    void initializeTypeChart();
    void initializeTerrainMap(char terrainMap[12][12]);
    void initializeVisibleMap(char visibleMap[12][12]);
    void initializeItemMap(char itemMap[12][12]);
    void randomlyPlaceContestant(Contestant& contestant, char terrainMap[12][12]);
    void distributeItems(char itemMap[12][12], Item* itemPool, int itemPoolSize, int itemCount);

    // Battle mechanics
    float getTypeMultiplier(const string& attackerType, const string& defenderType);
    float getTypeMultiplier(const string& attackerType, const Snuggladon& defender);
    float getTypeMultiplier(const Snuggladon& attacker, const string& defenderType);
    int calculateDamage(const Codemon& attacker, const Codemon& defender);
    int calculateDamage(const Codemon& attacker, const Codemon& defender, int skillIndex); // New function for specific skill
    int calculateDamage(const Codemon& attacker, const Snuggladon& defender);
    int calculateDamage(const Codemon& attacker, const Snuggladon& defender, int skillIndex); // New function for specific skill
    int calculateDamage(const Snuggladon& attacker, const Codemon& defender, bool enraged);

// executeBattle function
void executeBattle(Contestant& contestant, Snuggladon& snuggladon, Contestant** contestants, int contestantCount, char terrainMap[12][12]);
    bool isEnemyInRange(const Contestant& contestant, const Snuggladon& snuggladon);
    int countAdjacentEnemies(const Snuggladon& snuggladon, Contestant** contestants, int contestantCount);

    // Movement mechanics
    bool isValidMove(int row, int col);
    bool isTileOccupied(int row, int col, Contestant** contestants, int contestantCount, const Snuggladon& snuggladon);
    void collectItem(Contestant& contestant, int row, int col, char itemMap[12][12], Item* itemPool, int itemPoolSize);
    void moveContestant(Contestant& contestant, int newRow, int newCol, char itemMap[12][12], Item* itemPool, int itemPoolSize);
    void computerMove(Contestant& computer, char itemMap[12][12], Item* itemPool, int itemPoolSize, 
                     Contestant** contestants, int contestantCount, const Snuggladon& snuggladon);
    void snuggladonMove(Snuggladon& snuggladon, Contestant** contestants, int contestantCount);

    // Item mechanics
    void useItem(Contestant& contestant);

    // Debug functions
    void printTerrainMap(char terrainMap[12][12]);
    void printFullMap(char terrainMap[12][12], Contestant** contestants, int contestantCount, const Snuggladon& snuggladon);
};

#endif // ARENA_H