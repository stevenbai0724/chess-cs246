#include "board.h"
#include <vector>

//algorithm to generate search tree for moves
int minimax(const int DEPTH, Board &b, int depth, Colour turn, int alpha, int beta, Move &chosenMove);

//wrapper function to get the best move using the value of minimax
Move getBestMove(Colour colour, Board &b, const int searchDepth);
