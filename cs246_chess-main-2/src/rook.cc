#include "rook.h"
#include "chessboard.h"

Rook::Rook(int r, int c, char colo, bool hasMoved): Piece{r, c, colo}, hasMoved{hasMoved} {}

bool Rook::getHasMoved(){
    return hasMoved;
}
char Rook::getChar(){
    if (getColour()=='w'){
        return 'R';
    } 
    else {
        return 'r';
    }
}

int Rook::getValue() {
    return 5;
}

void Rook::setCoords(Coordinates newCoords) {
    setRow(newCoords.row);
    setCol(newCoords.col);
    if (!hasMoved) hasMoved = true;
}

Piece* Rook::clone() {
    return new Rook{getRow(), getCol(), getColour(), hasMoved};
}

std::vector<Coordinates> Rook::availableMoves(ChessBoard* const chessboard) {
    std::vector<Coordinates> moves;

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

        // if first move, add flag
        if (!hasMoved) (*it).firstMove = true;

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
