// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: GameFunctions.h
// Assignment: Final Project
// Purpose: Declaration of game functions for Codémons Rebellion

#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "Arena.h"
#include "Codemon.h"
#include "Contestant.h"
#include "Item.h"
#include "Snuggladon.h"
#include <string>

using namespace std;

// Function declarations
void loadCodemonsFromFile(Codemon* codemonPool, int& codemonCount, const string& filename);
void loadSkillsFromFile(Skill* skillPool, int& skillCount, const string& filename);
void loadItemsFromFile(Item* itemPool, int& itemCount, const string& filename);
void setupSnuggladon(Snuggladon& snuggladon, int totalContestants);
int getValidIntInput(int min, int max, const string& prompt);
char getValidCharInput(const string& validChars, const string& prompt);
int min(int a, int b);
void selectActiveCodemon(Contestant& contestant);
void setupContestant(Contestant& contestant, Codemon* codemonPool, int codemonCount, 
                    Skill* skillPool, int skillCount, bool isHuman);
void initializeGame(Arena& arena, Contestant** contestants, int contestantCount, 
                   Snuggladon& snuggladon, Codemon* codemonPool, int codemonCount, 
                   Skill* skillPool, int skillCount, Item* itemPool, int itemCount);
void playerTurn(Arena& arena, Contestant& player, Contestant** contestants, int contestantCount,
               Snuggladon& snuggladon, Item* itemPool, int itemCount, int turnCount);
void computerTurn(Arena& arena, Contestant& computer, Contestant** contestants, int contestantCount,
                 Snuggladon& snuggladon, Item* itemPool, int itemCount);
void snuggladonTurn(Arena& arena, Snuggladon& snuggladon, Contestant** contestants, int contestantCount);
void redistributeItems(Arena& arena, Item* itemPool, int itemCount);
bool isGameOver(Contestant** contestants, int contestantCount, Snuggladon& snuggladon);

#endif // GAME_FUNCTIONS_H