// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Item.cpp
// Assignment: Final Project
// Purpose: Item class implementation

#include "Item.h"
#include <iostream>

Item::Item() {
    name = "";
    description = "";
    effectType = "";
    effectAmount = 0;
}

Item::Item(const string& n, const string& type, int amount, const string& desc) {
    name = n;
    effectType = type;
    effectAmount = amount;
    description = desc;
}

ostream& operator<<(ostream& os, const Item& item) {
    os << "Name: " << item.name << endl;
    os << "Description: " << item.description << endl;
    os << "Effect Type: " << item.effectType << endl;
    os << "Effect Amount: ";

    if (item.effectType == "Heal") {
        os << item.effectAmount << " HP";
    } else if (item.effectType == "Boost") {
        os << "+" << item.effectAmount << " Attack";
    } else if (item.effectType == "Shield") {
        os << "Absorbs " << item.effectAmount << " damage";
    } else {
        os << item.effectAmount;
    }

    return os;
}