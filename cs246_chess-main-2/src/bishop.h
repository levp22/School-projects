#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop: public Piece {
    public:
        Bishop(int r, int c, char colo);
        char getChar() override;
        int getValue() override;
        Piece* clone() override;
        std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) override;
};
#endif
