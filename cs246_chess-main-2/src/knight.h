#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight: public Piece {
    public:
        Knight(int r, int c, char colo);
        char getChar() override;
        int getValue() override;
        Piece* clone() override;
        std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) override;
};
#endif
