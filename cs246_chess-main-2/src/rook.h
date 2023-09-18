#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook: public Piece {
    bool hasMoved;
    public:
        Rook(int r, int c, char colo, bool hasMoved=false);
        char getChar() override;
        int getValue() override;
        void setCoords(Coordinates newCoords) override;
        Piece* clone() override;
        std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) override;
        bool getHasMoved() override;
};
#endif
