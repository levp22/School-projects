#ifndef HUMAN_H
#define HUMAN_H
#include "controller.h"

class ChessBoard;

class Human : public Controller
{
public:
    Human(char colour, ChessBoard *chessboard);
    void nextMove() override;
};

#endif
