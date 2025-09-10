// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Contestant.cpp
// Assignment: Final Project
// Purpose: Contestant class implementation with expanded features

#include "Contestant.h"
#include <cmath>
#include <iostream>

using namespace std;

// Initialize static members
Item* Contestant::itemQueue = nullptr;
int Contestant::itemCount = 0;
int Contestant::itemCapacity = 0;

// External global variables (declared in main.cpp)
extern char terrainMap[12][12];
extern char visibleMap[12][12];
extern char itemMap[12][12];

Contestant::Contestant() {
    name = "";
    teamSize = 0;
    team = nullptr;
    activeCodemonIndex = 0;
    currentRow = 0;
    currentCol = 0;
    isComputer = false;
    remainingCodemons = 0;
    lastKnownSnuggladonRow = -1;
    lastKnownSnuggladonCol = -1;
}

Contestant::Contestant(const string& n, int size, bool computer) {
    name = n;
    teamSize = size;
    team = new Codemon[teamSize];
    activeCodemonIndex = 0;
    currentRow = 0;
    currentCol = 0;
    isComputer = computer;
    remainingCodemons = size;
    lastKnownSnuggladonRow = -1;
    lastKnownSnuggladonCol = -1;
}

// Copy constructor
Contestant::Contestant(const Contestant& other) {
    name = other.name;
    teamSize = other.teamSize;
    team = new Codemon[teamSize];
    activeCodemonIndex = other.activeCodemonIndex;
    currentRow = other.currentRow;
    currentCol = other.currentCol;
    isComputer = other.isComputer;
    remainingCodemons = other.remainingCodemons;
    lastKnownSnuggladonRow = other.lastKnownSnuggladonRow;
    lastKnownSnuggladonCol = other.lastKnownSnuggladonCol;

    // Deep copy of team
    for (int i = 0; i < teamSize; i++) {
        team[i] = other.team[i];
    }
}

// Assignment operator
Contestant& Contestant::operator=(const Contestant& other) {
    if (this != &other) {
        // Delete existing team
        delete[] team;

        // Copy data
        name = other.name;
        teamSize = other.teamSize;
        team = new Codemon[teamSize];
        activeCodemonIndex = other.activeCodemonIndex;
        currentRow = other.currentRow;
        currentCol = other.currentCol;
        isComputer = other.isComputer;
        remainingCodemons = other.remainingCodemons;
        lastKnownSnuggladonRow = other.lastKnownSnuggladonRow;
        lastKnownSnuggladonCol = other.lastKnownSnuggladonCol;

        // Deep copy of team
        for (int i = 0; i < teamSize; i++) {
            team[i] = other.team[i];
        }
    }
    return *this;
}

// Destructor
Contestant::~Contestant() {
    delete[] team;
}

void Contestant::addCodemon(int index, const Codemon& codemon) {
    if (index >= 0 && index < teamSize) {
        team[index] = codemon;
    }
}

bool Contestant::switchToNextCodemon() {
    for (int i = 0; i < teamSize; i++) {
        if (!team[i].isFainted()) {
            activeCodemonIndex = i;
            return true;
        }
    }
    return false;
}

void Contestant::setActiveCodemon(int index) {
    if (index >= 0 && index < teamSize && !team[index].isFainted()) {
        activeCodemonIndex = index;
    }
}

Codemon& Contestant::operator[](int index) {
    return team[index];
}

const Codemon& Contestant::operator[](int index) const {
    return team[index];
}

void Contestant::printVisibleMap() const {
    // Update visible map based on current position
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            visibleMap[i][j] = '#';
        }
    }

    // Reveal 3x3 area around current position
    for (int i = currentRow - 1; i <= currentRow + 1; i++) {
        for (int j = currentCol - 1; j <= currentCol + 1; j++) {
            if (i >= 0 && i < 12 && j >= 0 && j < 12) {
                visibleMap[i][j] = terrainMap[i][j];

                // If there's an item on this tile, mark it
                if (itemMap[i][j] != ' ') {
                    visibleMap[i][j] = 'I';
                }
            }
        }
    }

    // Mark player position
    visibleMap[currentRow][currentCol] = '@';

    // Print the visible map
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            cout << visibleMap[i][j] << " ";
        }
        cout << endl;
    }

    cout << "=========" << endl;

    // Print current Codemon info
    cout << "[@] Contestant " << name << "'s "
         << team[activeCodemonIndex].getName() << " is standing on ";

    switch (terrainMap[currentRow][currentCol]) {
    case 'F':
        cout << "Forest";
        break;
    case 'M':
        cout << "Mountain";
        break;
    case 'P':
        cout << "Plains";
        break;
    case 'W':
        cout << "Water";
        break;
    case 'S':
        cout << "Swamp";
        break;
    }
    cout << "." << endl;
    cout << team[activeCodemonIndex] << endl << endl;

    // Display last known position of Snuggladon if available
    if (lastKnownSnuggladonRow != -1 && lastKnownSnuggladonCol != -1) {
        cout << "Snuggladon's last known location remains at (" 
             << lastKnownSnuggladonRow << ", " << lastKnownSnuggladonCol << ")..." << endl;
    }
}

// Static item queue management
void Contestant::initializeItemQueue(int totalContestants) {
    itemCapacity = totalContestants * 2; // Initial capacity is twice the number of contestants
    itemQueue = new Item[itemCapacity];
    itemCount = 0;
}

void Contestant::addItem(const Item& item) {
    // Check if we need to resize
    if (itemCount >= itemCapacity) {
        // Increase capacity by 50%
        int newCapacity = itemCapacity + (itemCapacity / 2);
        resizeItemQueue(newCapacity);
    }

    // Add item to the end of the queue
    itemQueue[itemCount] = item;
    itemCount++;

    cout << "You found a " << item.getName() << "! Added to the inventory." << endl;
}

bool Contestant::useNextItem(Codemon& codemon) {
    if (itemCount == 0) {
        return false;
    }

    // Get the first item (FIFO)
    Item item = itemQueue[0];

    // Apply effect to Codemon
    if (item.getEffectType() == "Heal") {
        codemon.heal(item.getEffectAmount());
        cout << codemon.getName() << " restored " << item.getEffectAmount() << " HP!" << endl;
    } else if (item.getEffectType() == "Boost") {
        codemon.applyBoost(item.getEffectAmount());
        cout << codemon.getName() << " attack boosted by " << item.getEffectAmount() << "!" << endl;
    } else if (item.getEffectType() == "Shield") {
        codemon.applyShield(item.getEffectAmount());
        cout << codemon.getName() << " is shielded against " << item.getEffectAmount() << " damage!" << endl;
    }

    // Remove item from queue (shift everything left)
    for (int i = 0; i < itemCount - 1; i++) {
        itemQueue[i] = itemQueue[i + 1];
    }
    itemCount--;

    // Check if we should shrink the queue
    if (itemCount <= itemCapacity / 4 && itemCapacity > 8) {
        // Shrink by 50%
        int newCapacity = itemCapacity / 2;
        resizeItemQueue(newCapacity);
    }

    return true;
}

bool Contestant::peekNextItem(Item& item) {
    if (itemCount == 0) {
        return false;
    }

    item = itemQueue[0];
    return true;
}

void Contestant::printItemInventory() {
    cout << "Item Inventory:" << endl;

    if (itemCount == 0) {
        cout << "  No items available." << endl;
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        cout << (i + 1) << ". " << itemQueue[i] << endl << endl;
    }
}

void Contestant::resizeItemQueue(int newCapacity) {
    // Create new array
    Item* newQueue = new Item[newCapacity];

    // Copy items (limited by smaller of old count or new capacity)
    int itemsToCopy = (itemCount < newCapacity) ? itemCount : newCapacity;
    for (int i = 0; i < itemsToCopy; i++) {
        newQueue[i] = itemQueue[i];
    }

    // Update count if necessary (in case we had to truncate)
    if (itemCount > newCapacity) {
        itemCount = newCapacity;
    }

    // Delete old array
    delete[] itemQueue;

    // Update pointer and capacity
    itemQueue = newQueue;
    itemCapacity = newCapacity;

    if (newCapacity > itemCapacity) {
        cout << "Item inventory expanded to hold more items." << endl;
    } else {
        cout << "Item inventory reduced to free up memory." << endl;
    }
}

void Contestant::cleanupItemQueue() {
    if (itemQueue != nullptr) {
        delete[] itemQueue;
        itemQueue = nullptr;
        itemCount = 0;
        itemCapacity = 0;
    }
}