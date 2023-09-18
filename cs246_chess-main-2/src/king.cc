#include "king.h"
#include "chessboard.h"

King::King(int r, int c, char colo, bool hasMoved): Piece{r, c, colo}, hasMoved{hasMoved} {}

char King::getChar(){
    if (getColour()=='w'){
        return 'K';
    } 
    else {
        return 'k';
    }
}

// King doesn't have a value - will never get to this point
int King::getValue() {
    return 0;
}

void King::setCoords(Coordinates newCoords) {
    setRow(newCoords.row);
    setCol(newCoords.col);
    if (!hasMoved) hasMoved = true;
}

Piece* King::clone() {
    return new King{getRow(), getCol(), getColour(), hasMoved};
}

std::vector<Coordinates> King::availableMoves(ChessBoard* const chessboard) {
    std::vector<Coordinates> moves;
    std::vector<Coordinates> potentialMoves {
        Coordinates{getRow()+1,getCol()+1}, Coordinates{getRow()+1,getCol()},
        Coordinates{getRow(),getCol()+1}, Coordinates{getRow()+1,getCol()-1},
        Coordinates{getRow()-1,getCol()}, Coordinates{getRow()-1,getCol()-1},
        Coordinates{getRow()-1,getCol()+1}, Coordinates{getRow(),getCol()-1}
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
    //dealing with castling
    if (!hasMoved){
        //check both sides for cleared spots
        bool leftClear = true;
        for (int i = getCol()+1; i < 7; i++){
             if (chessboard->getPiece(getRow(), i)!=nullptr){
                leftClear=false;
            }
        }
        bool rightClear = true;
        for (int i = getCol()-1; i > 0; i--){
            if (chessboard->getPiece(getRow(), i)!=nullptr){
                rightClear=false;
            }
        }
        if(leftClear){
            Piece *leftRook = chessboard->getPiece(getRow(), 7);
            if(leftRook!=nullptr && leftRook->getColour()==getColour() && !leftRook->getHasMoved()){//castling issue with rook checking if it has moved
              //must make sure king is not in check at middle point  
                ChessBoard temp = *chessboard;
                temp.advancePiece(getRow(), getCol(), Coordinates{getRow(), getCol()+1});
                if (!temp.inCheck(getColour())) {
                    moves.emplace_back(Coordinates{getRow(), getCol()+2,false, false, false, false, true});
                    }
                }
        }
        if(rightClear){
            Piece *rightRook = chessboard->getPiece(getRow(), 0);
            if(rightRook!=nullptr && rightRook->getColour()==getColour() && !rightRook->getHasMoved()){
              //must make sure king is not in check at middle point  
                ChessBoard temp = *chessboard;
                temp.advancePiece(getRow(), getCol(), Coordinates{getRow(), getCol()+1});
                if (!temp.inCheck(getColour())) {
                    moves.emplace_back(Coordinates{getRow(), getCol()-2,false, false, false, false, true});
                    }
                }
        }
        

    }

    // simulates moves to see if it will put self/opponent in check
    for (auto it = moves.begin(); it != moves.end();) {
        ChessBoard tmp = *chessboard;
        char opposingColour;
        if (getColour() == 'w') opposingColour = 'b';
        else opposingColour = 'w';

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
