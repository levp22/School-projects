#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "subject.h"
#include "coordinates.h"
#include "lastMove.h"
#include <memory>
#include <vector>

class Piece;

class ChessBoard: public Subject {
    char curPlayer;
    std::unique_ptr<Piece> gameboard[8][8];
    std::vector<LastMove> moveHistory;
    bool setupMode;
    public:
        ChessBoard();

        void swap(ChessBoard &other);
        ChessBoard(const ChessBoard &other);
        ChessBoard& operator=(const ChessBoard &other);
        ChessBoard(ChessBoard &&other);
        ChessBoard& operator=(ChessBoard &&other);
        ~ChessBoard();
        
        char pieceAt(int row, int col) const override;
        Piece* getPiece(int row, int col); // for now
        std::vector<Piece*> getPieces(char colour);
        void changeTurn();
        void setTurn(char colour);
        void advancePiece(int row, int col, Coordinates newCoords, char newPiece = ' ');
        void placePiece(int row, int col, char piece);
        bool removePiece(int row, int col);
        bool validBoard();
        bool inCheck(char colour);
        bool hasAvailableMove(char colour);
        bool notOnlyKing();
        int evaluate(char curPlayer);
        char getTurn();
        void undoMove();
        LastMove getLastMove();
        bool getSetupMode();
        void setSetupMode(bool set);
        void reset();
};

#endif
