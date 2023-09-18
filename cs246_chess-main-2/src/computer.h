#ifndef COMPUTER_H
#define COMPUTER_H
#include "controller.h"
#include "chessboard.h"

class Piece;

class Computer: public Controller {
    int difficulty;
    private:
        void randomMove();
        bool checkCaptureMove();
        bool avoidCaptureMove();
        bool avoidCaptureMoveAndEnsureSafe();
        int negamax(int depth, ChessBoard chessboard, int alpha, int beta);
        void negamaxRoot(int depth);
        //int negamax(int depth, ChessBoard chessboard);
    public:
        Computer(char colour, ChessBoard* chessboard, int difficulty);
        void nextMove() override;
};

#endif
