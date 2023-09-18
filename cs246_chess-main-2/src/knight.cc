#include "knight.h"
#include "chessboard.h"

Knight::Knight(int r, int c, char colo): Piece{r, c, colo} {}

char Knight::getChar(){
    if (getColour()=='w'){
        return 'N';
    } 
    else {
        return 'n';
    }
}

int Knight::getValue() {
    return 3;
}

Piece* Knight::clone() {
    return new Knight{getRow(), getCol(), getColour()};
}

std::vector<Coordinates> Knight::availableMoves(ChessBoard* const chessboard) {
    std::vector<Coordinates> moves;
    std::vector<Coordinates> potentialMoves {
        Coordinates{getRow()+1,getCol()-2}, Coordinates{getRow()+1,getCol()+2},
        Coordinates{getRow()+2,getCol()+1}, Coordinates{getRow()+2,getCol()-1},
        Coordinates{getRow()-1,getCol()-2}, Coordinates{getRow()-1,getCol()+2},
        Coordinates{getRow()-2,getCol()+1}, Coordinates{getRow()-2,getCol()-1}
    };

    for (auto pm: potentialMoves) {
        if (pm.row < 0 || pm.row >= 8 || pm.col < 0 || pm.col >= 8) continue;
        
        if (chessboard->getPiece(pm.row, pm.col) == nullptr) {
            moves.emplace_back(pm);
        } else if (chessboard->getPiece(pm.row, pm.col)->getColour() != getColour()) {
            pm.capture = true;
            moves.emplace_back(pm);
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
