#include <iostream>
#include <sstream>
#include <limits>
#include "level5bot.h"
#include "botutil.h"
#include <random>

using namespace std;

const int DEPTH = 5;

Level5Bot::Level5Bot(Colour colour): Player{colour} {}

bool Level5Bot::makeMove(Board &b) const {
    Move chosenMove = getBestMove(colour, b, DEPTH);
    
    if (!b.move(chosenMove.r, chosenMove.c, chosenMove.nr, chosenMove.nc, chosenMove.promotePiece)) {
        cout << "bot move was invalid...\n";
        return false;
    }
    return true; 
}
