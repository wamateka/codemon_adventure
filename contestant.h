// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Contestant.h
// Assignment: Final Project
// Purpose: Contestant class with expanded features

#ifndef CONTESTANT_H
#define CONTESTANT_H

#include "Codemon.h"
#include "Item.h"
#include <string>

using namespace std;

class Contestant {
private:
    string name;
    Codemon* team; // Dynamic array of Codemons
    int teamSize;
    int activeCodemonIndex;
    int currentRow;
    int currentCol;
    bool isComputer;
    int remainingCodemons;

    // Static data for all contestants
    static Item* itemQueue; // Shared item queue (dynamic array)
    static int itemCount;   // Current number of items in queue
    static int itemCapacity; // Current capacity of the queue

    int lastKnownSnuggladonRow; // Last known position of Snuggladon
    int lastKnownSnuggladonCol;

public:
    // Constructors
    Contestant();
    Contestant(const string& n, int teamSize, bool computer = false);

    // Big Four (for proper memory management)
    Contestant(const Contestant& other); // Copy constructor
    Contestant& operator=(const Contestant& other); // Assignment operator
    ~Contestant(); // Destructor

    // Getters
    string getName() const { return name; }
    Codemon& getActiveCodemon() { return team[activeCodemonIndex]; }
    const Codemon& getActiveCodemon() const { return team[activeCodemonIndex]; }
    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }
    bool isComputerPlayer() const { return isComputer; }
    int getRemainingCodemons() const { return remainingCodemons; }
    bool isDefeated() const { return remainingCodemons <= 0; }
    int getTeamSize() const { return teamSize; }
    int getLastKnownSnuggladonRow() const { return lastKnownSnuggladonRow; }
    int getLastKnownSnuggladonCol() const { return lastKnownSnuggladonCol; }

    // Setters
    void setPosition(int row, int col) {
        currentRow = row;
        currentCol = col;
    }
    void setName(const string& n) { name = n; }
    void setLastKnownSnuggladonPosition(int row, int col) {
        lastKnownSnuggladonRow = row;
        lastKnownSnuggladonCol = col;
    }

    // Manage team
    void addCodemon(int index, const Codemon& codemon);
    bool switchToNextCodemon();
    void setActiveCodemon(int index);

    // Overloaded operator
    Codemon& operator[](int index);
    const Codemon& operator[](int index) const;

    // Display map
    void printVisibleMap() const;

    // Battle functions
    void decrementRemainingCodemons() { remainingCodemons--; }

    // Item management
    static void initializeItemQueue(int totalContestants);
    static void addItem(const Item& item);
    static bool useNextItem(Codemon& codemon);
    static bool peekNextItem(Item& item);
    static int getItemCount() { return itemCount; }
    static void printItemInventory();
    static void resizeItemQueue(int newCapacity);

    // Memory management helper
    static void cleanupItemQueue();
};

#endif // CONTESTANT_H