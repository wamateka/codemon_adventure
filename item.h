// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Item.h
// Assignment: Final Project
// Purpose: Item class definition

#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item {
private:
    string name;
    string description;
    string effectType; // "Heal", "Boost", or "Shield"
    int effectAmount;

public:
    // Constructors
    Item();
    Item(const string& n, const string& type, int amount, const string& desc);

    // Getters
    string getName() const { return name; }
    string getDescription() const { return description; }
    string getEffectType() const { return effectType; }
    int getEffectAmount() const { return effectAmount; }

    // Setters
    void setName(const string& n) { name = n; }
    void setDescription(const string& desc) { description = desc; }
    void setEffectType(const string& type) { effectType = type; }
    void setEffectAmount(int amount) { effectAmount = amount; }

    // Output operator
    friend ostream& operator<<(ostream& os, const Item& item);
};

#endif // ITEM_H