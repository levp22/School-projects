#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn: public Piece {
    bool hasMoved;
    public:
        Pawn(int r, int c, char colo, bool hasMoved=false);
        char getChar() override;
        int getValue() override;
        void setCoords(Coordinates newCoords) override;
        Piece* clone() override;
        std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) override;
};
#endif
