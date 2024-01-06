#ifndef LEVEL4BOT_H
#define LEVEL4BOT_H
#include "player.h"

class Level4Bot: public Player {
    public:
        //create a level 4 bot for colour
        Level4Bot(Colour colour);
        //execute a move and return true if successful
        bool makeMove(Board &b) const override;
};

#endif
