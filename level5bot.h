#ifndef LEVEL5BOT_H
#define LEVEL5BOT_H
#include "player.h"

class Level5Bot: public Player {
    public:
        //create a level 4 bot for colour
        Level5Bot(Colour colour);
        //execute a move and return true if successful
        bool makeMove(Board &b) const override;
};

#endif
