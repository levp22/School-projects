#include "pawn.h"
#include "chessboard.h"
#include "lastMove.h"

Pawn::Pawn(int r, int c, char colo, bool hasMoved): Piece{r, c, colo}, hasMoved{hasMoved} {}

char Pawn::getChar(){
    if (getColour()=='w'){
        return 'P';
    } 
    else {
        return 'p';
    }
}

int Pawn::getValue() {
    return 1;
}

void Pawn::setCoords(Coordinates newCoords) {
    if (!hasMoved) hasMoved = true; 
    setRow(newCoords.row);
    setCol(newCoords.col);
}

Piece* Pawn::clone() {
    return new Pawn{getRow(), getCol(), getColour(), hasMoved};
}

std::vector<Coordinates> Pawn::availableMoves(ChessBoard* const chessboard) {
    std::vector<Coordinates> moves;

    int dir = 1;

    // advances "forward" if white, "backwards" if black
    if (getColour() == 'b') {
        dir = -1;
    }

    if (getRow()+1*dir >= 0 && getRow()+1*dir < 8) {
        // checking going forward
        if (chessboard->getPiece(getRow()+1*dir,getCol()) == nullptr) {
            moves.emplace_back(Coordinates{getRow()+1*dir, getCol()});
            if (hasMoved == false && getRow()+2*dir >= 0 && getRow()+2*dir < 8 && chessboard->getPiece(getRow()+2*dir, getCol()) == nullptr) {
                moves.emplace_back(Coordinates{getRow()+2*dir, getCol()});
            }
        }

        // checking diagonals
        if (getCol()+1 >= 0 && getCol()+1 < 8 && chessboard->getPiece(getRow()+1*dir,getCol()+1) != nullptr && chessboard->getPiece(getRow()+1*dir,getCol()+1)->getColour() != getColour()) {
            moves.emplace_back(Coordinates{getRow()+1*dir, getCol()+1,true});
        }

        if (getCol()-1 >= 0 && getCol()-1 < 8 && chessboard->getPiece(getRow()+1*dir,getCol()-1) != nullptr && chessboard->getPiece(getRow()+1*dir,getCol()-1)->getColour() != getColour()) {
            moves.emplace_back(Coordinates{getRow()+1*dir, getCol()-1,true});
        }

        // en passant
        try {
            LastMove move = chessboard->getLastMove();
            if (chessboard->pieceAt(move.newCoords.row, move.newCoords.col) == 'P' || chessboard->pieceAt(move.newCoords.row, move.newCoords.col) == 'p') {
                if ((move.newCoords.row - move.prevCoords.row)*-1*dir == 2 && getRow() == move.newCoords.row && getCol() + 1 == move.newCoords.col) {
                    moves.emplace_back(Coordinates{getRow()+1*dir, getCol()+1, true, false, false, true});
                } else if ((move.newCoords.row - move.prevCoords.row)*-1*dir == 2 && getRow() == move.newCoords.row && getCol() - 1 == move.newCoords.col) {
                    moves.emplace_back(Coordinates{getRow()+1*dir, getCol()-1, true, false, false, true});
                } 
            }
        } catch(...) {
            // doesn't need to do anything, just won't work if size is 0
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

        // if move reaches end of board, add promotion flag
        if ((*it).row == 7 || (*it).row == 0) (*it).promotion = true;

        // if the move puts yourself in check, get rid of it
        if (tmp.inCheck(getColour())) {
            moves.erase(it);
        } else {
            ++it;
        }
    }

    return moves;
}
