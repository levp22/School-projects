#include "queen.h"
#include "chessboard.h"

Queen::Queen(int r, int c, char colo): Piece{r, c, colo} {}

char Queen::getChar(){
    if (getColour()=='w'){
        return 'Q';
    } 
    else {
        return 'q';
    }
}

int Queen::getValue() {
    return 9;
}

Piece* Queen::clone() {
    return new Queen{getRow(), getCol(), getColour()};
}

std::vector<Coordinates> Queen::availableMoves(ChessBoard* const chessboard) {
    std::vector<Coordinates> moves;
    //bishop moves 
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
    //rook moves
    for(int i = getRow()+1; i<8; i++){
        if (chessboard->getPiece(i, getCol())==nullptr){
            moves.emplace_back(Coordinates{i, getCol()});
        }
        else {
            if (chessboard->getPiece(i, getCol())->getColour() != getColour()){
                moves.emplace_back(Coordinates{i, getCol(), true});
            }
            break;
        }
    }
    for(int i = getCol()+1; i<8; i++){
        if (chessboard->getPiece(getRow(), i)==nullptr){
            moves.emplace_back(Coordinates{getRow(), i});
        }
        else {
            if (chessboard->getPiece(getRow(), i)->getColour() != getColour()){
                moves.emplace_back(Coordinates{getRow(), i, true});
            }
            break;
        }
    }
    for(int i = getRow()-1; i>=0; i--){
        if (chessboard->getPiece(i, getCol())==nullptr){
            moves.emplace_back(Coordinates{i, getCol()});
        }
        else {
            if (chessboard->getPiece(i, getCol())->getColour() != getColour()){
                moves.emplace_back(Coordinates{i, getCol(), true});
            }
            break;
        }
    }
    for(int i = getCol()-1; i>=0; i--){
        if (chessboard->getPiece(getRow(), i)==nullptr){
            moves.emplace_back(Coordinates{getRow(), i});
        }
        else {
            if (chessboard->getPiece(getRow(), i)->getColour() != getColour()){
                moves.emplace_back(Coordinates{getRow(), i, true});
            }
            break;
        }
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
