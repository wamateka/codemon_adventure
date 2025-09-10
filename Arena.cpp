// Programmers: Sesi, Barry, Ethan
// Section: all 101
// Usernames: swo6k7, eagnnc, bbndpx
// Date: 5/11
// File: Arena.cpp
// Assignment: Final Project
// Purpose: Battle arena class implementation with expanded features (Part 1)

#include "Arena.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

// Constructor
Arena::Arena() {
    initializeTypeChart();
}

// Type chart initialization
void Arena::initializeTypeChart() {
    // The expanded 11x11 type chart

    // Fire row
    typeChart[FIRE][FIRE] = 1.0;
    typeChart[FIRE][WATER] = 0.5;
    typeChart[FIRE][GRASS] = 2.0;
    typeChart[FIRE][ELECTRIC] = 1.0;
    typeChart[FIRE][ICE] = 2.0;
    typeChart[FIRE][ROCK] = 0.5;
    typeChart[FIRE][NORMAL] = 1.0;
    typeChart[FIRE][PSYCHIC] = 1.0;
    typeChart[FIRE][DARK] = 1.0;
    typeChart[FIRE][STEEL] = 2.0;
    typeChart[FIRE][FAIRY] = 1.0;

    // Water row
    typeChart[WATER][FIRE] = 2.0;
    typeChart[WATER][WATER] = 1.0;
    typeChart[WATER][GRASS] = 0.5;
    typeChart[WATER][ELECTRIC] = 1.0;
    typeChart[WATER][ICE] = 1.0;
    typeChart[WATER][ROCK] = 2.0;
    typeChart[WATER][NORMAL] = 1.0;
    typeChart[WATER][PSYCHIC] = 1.0;
    typeChart[WATER][DARK] = 1.0;
    typeChart[WATER][STEEL] = 1.0;
    typeChart[WATER][FAIRY] = 1.0;

    // Grass row
    typeChart[GRASS][FIRE] = 0.5;
    typeChart[GRASS][WATER] = 2.0;
    typeChart[GRASS][GRASS] = 1.0;
    typeChart[GRASS][ELECTRIC] = 1.0;
    typeChart[GRASS][ICE] = 1.0;
    typeChart[GRASS][ROCK] = 2.0;
    typeChart[GRASS][NORMAL] = 1.0;
    typeChart[GRASS][PSYCHIC] = 1.0;
    typeChart[GRASS][DARK] = 1.0;
    typeChart[GRASS][STEEL] = 0.5;
    typeChart[GRASS][FAIRY] = 1.0;

    // Electric row
    typeChart[ELECTRIC][FIRE] = 1.0;
    typeChart[ELECTRIC][WATER] = 2.0;
    typeChart[ELECTRIC][GRASS] = 0.5;
    typeChart[ELECTRIC][ELECTRIC] = 1.0;
    typeChart[ELECTRIC][ICE] = 1.0;
    typeChart[ELECTRIC][ROCK] = 1.0;
    typeChart[ELECTRIC][NORMAL] = 1.0;
    typeChart[ELECTRIC][PSYCHIC] = 1.0;
    typeChart[ELECTRIC][DARK] = 1.0;
    typeChart[ELECTRIC][STEEL] = 1.0;
    typeChart[ELECTRIC][FAIRY] = 1.0;

    // Ice row
    typeChart[ICE][FIRE] = 0.5;
    typeChart[ICE][WATER] = 0.5;
    typeChart[ICE][GRASS] = 2.0;
    typeChart[ICE][ELECTRIC] = 1.0;
    typeChart[ICE][ICE] = 0.5;
    typeChart[ICE][ROCK] = 1.0;
    typeChart[ICE][NORMAL] = 1.0;
    typeChart[ICE][PSYCHIC] = 1.0;
    typeChart[ICE][DARK] = 1.0;
    typeChart[ICE][STEEL] = 0.5;
    typeChart[ICE][FAIRY] = 1.0;

    // Rock row
    typeChart[ROCK][FIRE] = 2.0;
    typeChart[ROCK][WATER] = 1.0;
    typeChart[ROCK][GRASS] = 1.0;
    typeChart[ROCK][ELECTRIC] = 1.0;
    typeChart[ROCK][ICE] = 2.0;
    typeChart[ROCK][ROCK] = 1.0;
    typeChart[ROCK][NORMAL] = 1.0;
    typeChart[ROCK][PSYCHIC] = 1.0;
    typeChart[ROCK][DARK] = 0.5;
    typeChart[ROCK][STEEL] = 0.5;
    typeChart[ROCK][FAIRY] = 1.0;

    // Normal row
    typeChart[NORMAL][FIRE] = 1.0;
    typeChart[NORMAL][WATER] = 1.0;
    typeChart[NORMAL][GRASS] = 1.0;
    typeChart[NORMAL][ELECTRIC] = 1.0;
    typeChart[NORMAL][ICE] = 1.0;
    typeChart[NORMAL][ROCK] = 0.5;
    typeChart[NORMAL][NORMAL] = 1.0;
    typeChart[NORMAL][PSYCHIC] = 1.0;
    typeChart[NORMAL][DARK] = 0.5;
    typeChart[NORMAL][STEEL] = 0.5;
    typeChart[NORMAL][FAIRY] = 1.0;

    // Psychic row
    typeChart[PSYCHIC][FIRE] = 1.0;
    typeChart[PSYCHIC][WATER] = 1.0;
    typeChart[PSYCHIC][GRASS] = 1.0;
    typeChart[PSYCHIC][ELECTRIC] = 1.0;
    typeChart[PSYCHIC][ICE] = 1.0;
    typeChart[PSYCHIC][ROCK] = 1.0;
    typeChart[PSYCHIC][NORMAL] = 1.0;
    typeChart[PSYCHIC][PSYCHIC] = 0.5;
    typeChart[PSYCHIC][DARK] = 2.0;
    typeChart[PSYCHIC][STEEL] = 0.5;
    typeChart[PSYCHIC][FAIRY] = 1.0;

    // Dark row
    typeChart[DARK][FIRE] = 1.0;
    typeChart[DARK][WATER] = 1.0;
    typeChart[DARK][GRASS] = 1.0;
    typeChart[DARK][ELECTRIC] = 1.0;
    typeChart[DARK][ICE] = 1.0;
    typeChart[DARK][ROCK] = 1.0;
    typeChart[DARK][NORMAL] = 1.0;
    typeChart[DARK][PSYCHIC] = 2.0;
    typeChart[DARK][DARK] = 0.5;
    typeChart[DARK][STEEL] = 1.0;
    typeChart[DARK][FAIRY] = 2.0;

    // Steel row
    typeChart[STEEL][FIRE] = 0.5;
    typeChart[STEEL][WATER] = 0.5;
    typeChart[STEEL][GRASS] = 1.0;
    typeChart[STEEL][ELECTRIC] = 0.5;
    typeChart[STEEL][ICE] = 2.0;
    typeChart[STEEL][ROCK] = 2.0;
    typeChart[STEEL][NORMAL] = 1.0;
    typeChart[STEEL][PSYCHIC] = 1.0;
    typeChart[STEEL][DARK] = 1.0;
    typeChart[STEEL][STEEL] = 0.5;
    typeChart[STEEL][FAIRY] = 2.0;

    // Fairy row
    typeChart[FAIRY][FIRE] = 0.5;
    typeChart[FAIRY][WATER] = 1.0;
    typeChart[FAIRY][GRASS] = 1.0;
    typeChart[FAIRY][ELECTRIC] = 1.0;
    typeChart[FAIRY][ICE] = 1.0;
    typeChart[FAIRY][ROCK] = 1.0;
    typeChart[FAIRY][NORMAL] = 1.0;
    typeChart[FAIRY][PSYCHIC] = 1.0;
    typeChart[FAIRY][DARK] = 2.0;
    typeChart[FAIRY][STEEL] = 0.5;
    typeChart[FAIRY][FAIRY] = 1.0;
}

// Helper function to get type index
int Arena::getTypeIndex(const string& type) const {
    if (type == "Fire") return FIRE;
    if (type == "Water") return WATER;
    if (type == "Grass") return GRASS;
    if (type == "Electric") return ELECTRIC;
    if (type == "Ice") return ICE;
    if (type == "Rock") return ROCK;
    if (type == "Normal") return NORMAL;
    if (type == "Psychic") return PSYCHIC;
    if (type == "Dark") return DARK;
    if (type == "Steel") return STEEL;
    if (type == "Fairy") return FAIRY;

    // Default to normal if type not found
    return NORMAL;
}

// Type multiplier calculation
float Arena::getTypeMultiplier(const string& attackerType, const string& defenderType) {
    int attackerIndex = getTypeIndex(attackerType);
    int defenderIndex = getTypeIndex(defenderType);

    return typeChart[attackerIndex][defenderIndex];
}

// Type multiplier with multiple defender types (for Snuggladon)
float Arena::getTypeMultiplier(const string& attackerType, const Snuggladon& defender) {
    float multiplier = 1.0f;

    for (int i = 0; i < defender.getTypeCount(); i++) {
        multiplier *= getTypeMultiplier(attackerType, defender.getType(i));
    }

    return multiplier;
}

// Type multiplier with multiple attacker types (from Snuggladon)
float Arena::getTypeMultiplier(const Snuggladon& attacker, const string& defenderType) {
    float multiplier = 1.0f;

    for (int i = 0; i < attacker.getTypeCount(); i++) {
        multiplier *= getTypeMultiplier(attacker.getType(i), defenderType);
    }

    return multiplier;
}