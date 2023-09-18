#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <memory>
#include <vector>
#include "coordinates.h"

class Piece;
class ChessBoard;

class Controller {
    char colour;
    ChessBoard *chessboard;
    protected:
        Controller(char colour, ChessBoard *chessboard);
        char getColour();
        ChessBoard* getBoard();
    public:
        virtual void nextMove() = 0;
        virtual ~Controller() = default;
};

#endif
