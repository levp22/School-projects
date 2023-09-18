#ifndef PIECE_H
#define PIECE_H
#include "coordinates.h"
#include <vector>

class ChessBoard;

class Piece {
    int row, col;
    char colour;
    protected:
        int getRow() const { return row; }
        int getCol() const { return col; }
        void setRow(int r) { row=r; }
        void setCol(int c) { col=c; }
        Piece(int row, int col, char colour) : row{row}, col{col}, colour{colour} {}
    public:
        char getColour() const { return colour; }
        Coordinates getCoords() { return Coordinates{row, col}; }
        virtual void setCoords(Coordinates newCoords) { row=newCoords.row, col=newCoords.col; }
        virtual char getChar() = 0;
        virtual int getValue() = 0;
        virtual std::vector<Coordinates> availableMoves(ChessBoard* const chessboard) = 0;
        virtual Piece* clone() = 0;
        virtual ~Piece() = default;
        virtual bool getHasMoved(){ return false; }
};

#endif
