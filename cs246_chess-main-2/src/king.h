#ifndef KING_H
#define KING_H
#include "piece.h"

class King: public Piece {
    bool hasMoved;
    public:
        King(int r, int c, char colo, bool hasMoved=false);
        char getChar() override;
        int getValue() override;
        void setCoords(Coordinates newCoords) override;
        Piece* clone() override;
        std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) override;
};
#endif
