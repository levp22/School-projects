#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen: public Piece {
    public:
        Queen(int r, int c, char colo);
        char getChar() override;
        int getValue() override;
        Piece* clone() override;
        std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) override;
};
#endif
