#include "botutil.h"

using namespace std;

const vector<vector<int>> LAYERS = {{3,4}, {2,5}, {1,6}, {0,7}};   

vector<Move> getAllChildren(Board &b, Colour turn) {
    vector<Move> promotions;
    vector<Move> checks;
    vector<Move> captures;
    vector<Move> castles;
    vector<Move> normalMoves;
    
    for (auto layer : LAYERS) { // loop from center out
        int layerCount = 0;
        for (int j = layer[0]; j <= layer[1]; j++) {
            for (int i : layer) {
                if (b.pieceAt(i, j) && b.pieceColourAt(i, j) == turn ) { //can only move same piece
                    vector<Move> temp = b.pieceAt(i, j)->getValidMoves(b);
                    for(auto m: temp) {
                        if (m.moveType == MoveType::PROMOTE) {
                            promotions.emplace_back(m);
                        }
                        else if (m.isCheck) {
                            checks.emplace_back(m);
                        }
                        else if (m.moveType == MoveType::CAPTURE || m.moveType == MoveType::ENPASSANT) {
                            captures.emplace_back(m);
                        }
                        else if (m.moveType == MoveType::CASTLE) {
                            castles.emplace_back(m);
                        }
                        else {
                            normalMoves.emplace_back(m);
                        }
                    }
                }

                if ((i == layer[0] && j == layer[1]) || (j == layer[0] && i == layer[1])) {
                    continue;
                }
                if (i == j) {
                    continue;
                }

                if (b.pieceColourAt(j, i) == turn) { //can only move same piece
                    vector<Move> temp = b.pieceAt(j, i)->getValidMoves(b);
                    for(auto m: temp) {
                        if (m.moveType == MoveType::PROMOTE) {
                            promotions.emplace_back(m);
                        }
                        else if (m.isCheck) {
                            checks.emplace_back(m);
                        }
                        else if (m.moveType == MoveType::CAPTURE || m.moveType == MoveType::ENPASSANT) {
                            captures.emplace_back(m);
                        }
                        else if (m.moveType == MoveType::CASTLE) {
                            castles.emplace_back(m);
                        }
                        else {
                            normalMoves.emplace_back(m);
                        }
                    }
                }
            }
        }
    }

    vector<Move> orderedMoves; 
    for (auto m : promotions) {
        orderedMoves.emplace_back(m);
    }
    for (auto m : checks) {
        orderedMoves.emplace_back(m);
    }
    for (auto m : captures) {
        orderedMoves.emplace_back(m);
    }
    for (auto m : castles) {
        orderedMoves.emplace_back(m);
    }
    for (auto m : normalMoves) {
        orderedMoves.emplace_back(m);
    }

    
    return orderedMoves;
}

int minimax(const int DEPTH, Board &b, int depth, Colour turn, int alpha, int beta, Move &chosenMove) {

    if (depth == 0 || b.gameOver()) {
        return b.eval();
    }

    Move bestMove;

    if (turn == Colour::WHITE) {
        int bestEval = -99999999;

        for(auto m: getAllChildren(b, turn)) {
            Board copyBoard = Board{b};
            copyBoard.move(m.r, m.c, m.nr, m.nc, m.promotePiece);
            int eval = minimax(DEPTH, copyBoard, depth-1, Colour::BLACK, alpha, beta, chosenMove);
            alpha = max(alpha, eval);
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = m;
            }
            if (beta <= alpha) {
                break;
            }
        }

        if (depth == DEPTH) {
            chosenMove = bestMove;
        }
        return bestEval;
    }

    else {
        int bestEval = 99999999;
        for(auto m: getAllChildren(b, turn)) {
            Board copyBoard = Board{b};
            copyBoard.move(m.r, m.c, m.nr, m.nc, m.promotePiece);
            int eval = minimax(DEPTH, copyBoard, depth-1, Colour::WHITE, alpha, beta, chosenMove);

            beta = min(beta, eval);
            if (eval < bestEval) {
                bestEval = eval;
                bestMove = m;
            }
            if (beta <= alpha) {
                break;
            }
        }
        if (depth == DEPTH) {
            chosenMove = bestMove;
        }
        return bestEval;
    }
}

Move getBestMove(Colour colour, Board &b, const int searchDepth) {
    Move bestMove; 
    Board copyBoard = Board{b};
    int eval = minimax(searchDepth, copyBoard, searchDepth, colour, -99999999, 99999999, bestMove);
    return bestMove;
}
