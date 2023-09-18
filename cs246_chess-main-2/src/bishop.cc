#include "bishop.h"
#include "chessboard.h"

Bishop::Bishop(int r, int c, char colo) : Piece{r, c, colo} {}

char Bishop::getChar(){
    if (getColour()=='w'){
        return 'B';
    } 
    else {
        return 'b';
    }
}

int Bishop::getValue() {
    return 3;
}

Piece* Bishop::clone() {
    return new Bishop{getRow(), getCol(), getColour()};
}

std::vector<Coordinates> Bishop::availableMoves(ChessBoard* const chessboard) {
    std::vector<Coordinates> moves;

    // checking all diagonals
    int i = getRow() + 1;
    int j = getCol() + 1;
    while (i<8&&j<8){
        if (chessboard->getPiece(i, j)==nullptr){
            moves.emplace_back(Coordinates{i, j});
        }
        else {
            if (chessboard->getPiece(i, j)->getColour() != getColour()){
                moves.emplace_back(Coordinates{i, j, true});
            }
            break;
        }
        i++;
        j++;
    }
    i = getRow()-1;
    j = getCol()-1;
    while (i>=0&&j>=0){
        if (chessboard->getPiece(i, j)==nullptr){
            moves.emplace_back(Coordinates{i, j});
        }
        else {
            if (chessboard->getPiece(i, j)->getColour() != getColour()){
                moves.emplace_back(Coordinates{i, j, true});
            }
            break;
        }
        i--;
        j--;
    }
    i = getRow()+1;
    j = getCol()-1;
    while (i<8&&j>=0){
        if (chessboard->getPiece(i, j)==nullptr){
            moves.emplace_back(Coordinates{i, j});
        }
        else {
            if (chessboard->getPiece(i, j)->getColour() != getColour()){
                moves.emplace_back(Coordinates{i, j, true});
            }
            break;
        }
        i++;
        j--;
    }
    i = getRow()-1;
    j = getCol()+1;
    while (i>=0&&j<8){
        if (chessboard->getPiece(i, j)==nullptr){
            moves.emplace_back(Coordinates{i, j});
        }
        else {
            if (chessboard->getPiece(i, j)->getColour() != getColour()){
                moves.emplace_back(Coordinates{i, j, true});
            }
            break;
        }
        i--;
        j++;
    }

    // simulates moves to see if it will put self/opponent in check
    for (auto it = moves.begin(); it != moves.end();) {
        ChessBoard tmp = *chessboard;
        char opposingColour;
        if (getColour() == 'w') opposingColour = 'b';
        else opposingColour = 'w';

        tmp.advancePiece(getRow(), getCol(), *it);

        // if move puts opposing player in check, add flag
        if (tmp.inCheck(opposingColour)) (*it).check = true;

        // if the move puts yourself in check, get rid of it
        if (tmp.inCheck(getColour())) {
            moves.erase(it);
        } else {
            ++it;
        }
    }

    return moves;
}
