#include "human.h"
#include "chessboard.h"
#include "controller.h"
#include "coordinates.h"
#include "piece.h"
#include <iostream>
#include <stdexcept>

int convRow(int row){
    if (row < 9 && row > 0){
        return row-1;
    }
    else {
        throw std::out_of_range{"Invalid move"};
    }
}
int convCol(char col){
    if (col>96 && col < 105){
        return col-97;
    }
    else {
        throw std::out_of_range{"Invalid move"};
    }
}

Human::Human(char colour, ChessBoard *chessboard) : Controller{colour, chessboard} {}
void Human::nextMove()
{
    int curRow, nextRow;
    char cCol, nCol;
    ChessBoard *board = getBoard();
    std::cin >> cCol >> curRow >> nCol >> nextRow;
    curRow = convRow(curRow);
    int curCol = convCol(cCol);
    nextRow = convRow(nextRow);
    int nextCol = convCol(nCol);

    if (board->getPiece(curRow, curCol)!=nullptr && board->getPiece(curRow, curCol)->getColour()==getColour()){
        for (auto m: board->getPiece(curRow, curCol)->availableMoves(board)) {
            if (m.row == nextRow && m.col == nextCol) {
                if (m.promotion){
                    char piece;
                    std::cin>>piece;
                    board->advancePiece(curRow, curCol, m, piece);
                } else {
                    board->advancePiece(curRow, curCol, m);
                }
                return;
            }
        }
    }
    throw std::out_of_range{"Invalid move"};
}
