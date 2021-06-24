#pragma once
#include <string>

// ===============
//      Linux 
// ===============
#define WOLF_SYMBOL "\U0001F43A"
#define SHEEP_SYMBOL "\U0001F411"
#define FOX_SYMBOL "\U0001F98A"
#define TURTLE_SYMBOL "\U0001F422"
#define ANTELOPE_SYMBOL "\U0001F40E"
#define HUMAN_SYMBOL "\U0001F9CD"
#define GRASS_SYMBOL "\U0001F331"
#define SONCHUS_SYMBOL "\U0001F33F"
#define GUARANA_SYMBOL "\U0001F348"
#define BERRIES_SYMBOL "\U0001F347"
#define SOSNOWSKI_BARSCH_SYMBOL "\U0001F33E"
#define DIVIDER_BLOCK "\U0001F7E9"

// =================
//      Windows 
// =================
// #define WOLF_SYMBOL "WW"
// #define SHEEP_SYMBOL "SS"
// #define FOX_SYMBOL "FF"
// #define TURTLE_SYMBOL "TT"
// #define ANTELOPE_SYMBOL "AA"
// #define HUMAN_SYMBOL "@@"
// #define GRASS_SYMBOL "II"
// #define SONCHUS_SYMBOL "++"
// #define GUARANA_SYMBOL "GG"
// #define BERRIES_SYMBOL "BB"
// #define SOSNOWSKI_BARSCH_SYMBOL "XX"
// #define DIVIDER_BLOCK "##"

#define NO_PROPER_KEY -1
#define KEY_QUIT 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_SUPER_POWER 5

#define HOW_MANY_PERCENTAGE_OF_ORGANISMS_ARE_ANIMALS 70
#define MIN_ANIMAL_AGE_TO_MULTIPLY 5
#define MIN_PLANT_AGE_TO_MULTIPLY 5
#define PERCENTAGE_CHANCE_PLANT_WILL_SPREAD 5
#define FIELDS_AROUND_ORGANISM 8

struct position {
    int x;
    int y;
    position(int x = 0, int y = 0) : x(x), y(y) { }
    bool operator==(const position& anotherPosition) const { 
        return x == anotherPosition.x && y == anotherPosition.y;
    }
};
