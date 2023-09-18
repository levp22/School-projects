#include "chessboard.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "king.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include <stdexcept>

ChessBoard::ChessBoard() : curPlayer{'w'}, setupMode{true} {
    gameboard[0][0].reset(new Rook{0,0,'w'});
    gameboard[0][1].reset(new Knight{0,1,'w'});
    gameboard[0][2].reset(new Bishop{0,2,'w'});
    gameboard[0][3].reset(new Queen{0,3,'w'});
    gameboard[0][4].reset(new King{0,4,'w'});
    gameboard[0][5].reset(new Bishop{0,5,'w'});
    gameboard[0][6].reset(new Knight{0,6,'w'});
    gameboard[0][7].reset(new Rook{0,7,'w'});

    for (int j = 0; j < 8; j++) {
        gameboard[1][j].reset(new Pawn{1,j,'w'});
        gameboard[6][j].reset(new Pawn{6,j,'b'});
    }

    gameboard[7][0].reset(new Rook{7,0,'b'});
    gameboard[7][1].reset(new Knight{7,1,'b'});
    gameboard[7][2].reset(new Bishop{7,2,'b'});
    gameboard[7][4].reset(new King{7,4,'b'});
    gameboard[7][3].reset(new Queen{7,3,'b'});
    gameboard[7][5].reset(new Bishop{7,5,'b'});
    gameboard[7][6].reset(new Knight{7,6,'b'});
    gameboard[7][7].reset(new Rook{7,7,'b'});
}

void ChessBoard::reset(){
    setupMode= true;
    curPlayer='w';
    gameboard[0][0].reset(new Rook{0,0,'w'});
    gameboard[0][1].reset(new Knight{0,1,'w'});
    gameboard[0][2].reset(new Bishop{0,2,'w'});
    gameboard[0][3].reset(new Queen{0,3,'w'});
    gameboard[0][4].reset(new King{0,4,'w'});
    gameboard[0][5].reset(new Bishop{0,5,'w'});
    gameboard[0][6].reset(new Knight{0,6,'w'});
    gameboard[0][7].reset(new Rook{0,7,'w'});

    for (int j = 0; j < 8; j++) {
        gameboard[1][j].reset(new Pawn{1,j,'w'});
        gameboard[6][j].reset(new Pawn{6,j,'b'});
    }
    for (int i = 2; i<6; i++){
        for (int j = 0; j<8; j++){
        gameboard[i][j]=nullptr;
    }
    }

    gameboard[7][0].reset(new Rook{7,0,'b'});
    gameboard[7][1].reset(new Knight{7,1,'b'});
    gameboard[7][2].reset(new Bishop{7,2,'b'});
    gameboard[7][4].reset(new King{7,4,'b'});
    gameboard[7][3].reset(new Queen{7,3,'b'});
    gameboard[7][5].reset(new Bishop{7,5,'b'});
    gameboard[7][6].reset(new Knight{7,6,'b'});
    gameboard[7][7].reset(new Rook{7,7,'b'});
}

void ChessBoard::swap(ChessBoard &other) {
    std::swap(curPlayer, other.curPlayer);
    std::swap(moveHistory, other.moveHistory);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::swap(gameboard[i][j], other.gameboard[i][j]);
        }
    }
}

ChessBoard::ChessBoard(const ChessBoard &other) : curPlayer{other.curPlayer}, moveHistory{other.moveHistory} {
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if (other.gameboard[i][j] == nullptr) continue;
            gameboard[i][j].reset(other.gameboard[i][j]->clone());
        }
    }
}

ChessBoard& ChessBoard::operator=(const ChessBoard &other) {
    ChessBoard tmp{other};
    swap(tmp);
    return *this;
}

ChessBoard::ChessBoard(ChessBoard &&other) : curPlayer{other.curPlayer} {
    moveHistory = std::move(other.moveHistory);
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            gameboard[i][j] = std::move(other.gameboard[i][j]);
        }
    }
}

ChessBoard& ChessBoard::operator=(ChessBoard &&other) {
    swap(other);
    return *this;
}

ChessBoard::~ChessBoard() { }

char ChessBoard::pieceAt(int row, int col) const { 
    if(row>=0 && col>=0 && row<8 && col<8){
    if (gameboard[row][col] == nullptr) {
        // this might want to be moved to each observer, return just ' '
        if (row % 2 == col % 2) return '_'; // if both are even, they both return 0mod2, if both are odd, they both return 1mod2, so just check if they're equal
        else return ' ';
    } else {
        return gameboard[row][col]->getChar(); 
    }
    } else {
        return ' ';
    }
}

Piece* ChessBoard::getPiece(int row, int col) {
    // this might want to be handled with an exception
    if (row >= 0 && row < 8 && col >= 0 && col<8) {
        return gameboard[row][col].get();
    } else {
        return nullptr;
    }
}

std::vector<Piece*> ChessBoard::getPieces(char colour) {
    std::vector<Piece*> pieces;
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            if (getPiece(i,j) != nullptr && colour == getPiece(i,j)->getColour()) {
                pieces.emplace_back(getPiece(i,j));
            }
        }
    }
    return pieces;
}

void ChessBoard::changeTurn() {
    if (curPlayer == 'w') { curPlayer = 'b'; }
    else { curPlayer = 'w'; }
}

void ChessBoard::setTurn(char colour) {
    curPlayer = colour;
}
char ChessBoard::getTurn(){
    return curPlayer;
}

void ChessBoard::advancePiece(int row, int col, Coordinates newCoords, char newPiece) {
    moveHistory.emplace_back(LastMove{Coordinates{row, col}, newCoords, pieceAt(newCoords.row, newCoords.col)});

    //removes old piece in spot(captures it)
    if (gameboard[newCoords.row][newCoords.col] != nullptr) gameboard[newCoords.row][newCoords.col] = nullptr;
    //moves piece to new spot
    gameboard[newCoords.row][newCoords.col] = std::move(gameboard[row][col]);

    char colour = gameboard[newCoords.row][newCoords.col]->getColour();
    if (newCoords.castle){
        //check if its a left or right castle and moves the rook (king is handled above)
        if(newCoords.col>col){
            gameboard[row][newCoords.col-1] = std::move(gameboard[row][7]);
            gameboard[row][newCoords.col-1]->setCoords(Coordinates{row, newCoords.col-1});
        }
        else if(newCoords.col<col){
            gameboard[row][newCoords.col+1] = std::move(gameboard[row][0]);
            gameboard[row][newCoords.col+1]->setCoords(Coordinates{row, newCoords.col+1});
        }
        
    }

    // en passant
    if (newCoords.enpassant) {
        if (colour == 'w') {
            gameboard[newCoords.row - 1][newCoords.col] = nullptr;
        } else {
            gameboard[newCoords.row + 1][newCoords.col] = nullptr;
        }
    }

    // pawn promotion
    if (newPiece == 'Q' || newPiece == 'q' || (newPiece == ' ' && newCoords.promotion)) { 
        gameboard[newCoords.row][newCoords.col].reset(new Queen{newCoords.row, newCoords.col, colour});
    } else if (newPiece == 'B' || newPiece == 'b') {
        gameboard[newCoords.row][newCoords.col].reset(new Bishop{newCoords.row, newCoords.col, colour});
    } else if (newPiece == 'R' || newPiece == 'r') {
        gameboard[newCoords.row][newCoords.col].reset(new Rook{newCoords.row, newCoords.col, colour});
    } else if (newPiece == 'N' || newPiece == 'n') {
        gameboard[newCoords.row][newCoords.col].reset(new Knight{newCoords.row, newCoords.col, colour});
    } else {
        gameboard[newCoords.row][newCoords.col]->setCoords(newCoords);
    }

    changeTurn();
}

bool ChessBoard::removePiece(int row, int col){
    if (row < 8 && col < 8 && row >= 0 && col >= 0){
    if (gameboard[row][col] != nullptr) {
        gameboard[row][col]=nullptr;
        return 1;
    } else {
        return 0;
    }
    }
    else {
        return 0;
    }
}

void ChessBoard::placePiece(int row, int col, char type){
    if (row < 8 && col < 8 && row >= 0 && col >= 0){
    if (type=='P'){
        gameboard[row][col].reset(new Pawn{row, col, 'w'});
    }
    else if (type=='N'){
        gameboard[row][col].reset(new Knight{row, col, 'w'});
    }
    else if (type=='Q'){
        gameboard[row][col].reset(new Queen{row, col, 'w'});
    }
    else if (type=='K'){
        gameboard[row][col].reset(new King{row, col, 'w'});
    }
    else if (type=='B'){
        gameboard[row][col].reset(new Bishop{row, col, 'w'});
    }
    else if (type=='R'){
        gameboard[row][col].reset(new Rook{row, col, 'w'});
    }
    else if (type=='p'){
        gameboard[row][col].reset(new Pawn{row, col, 'b'});
    }
    else if (type=='n'){
        gameboard[row][col].reset(new Knight{row, col, 'b'});
    }
    else if (type=='q'){
        gameboard[row][col].reset(new Queen{row, col, 'b'});
    }
    else if (type=='k'){
        gameboard[row][col].reset(new King{row, col, 'b'});
    }
    else if (type=='b'){
        gameboard[row][col].reset(new Bishop{row, col, 'b'});
    }
    else if (type=='r'){
        gameboard[row][col].reset(new Rook{row, col, 'b'});
    }
    }
}

bool ChessBoard::inCheck(char colour){
    // finding position of king
    int row, col;
    bool found = false;
    for(int i=0; i < 8; i++){
        for(int j=0; j < 8; j++){
            if (pieceAt(i, j)=='k' && colour=='b') {
                found = true;
                row = i;
                col = j;
                break;
            }  
            else if (pieceAt(i, j)=='K' && colour=='w') {
                found = true;
                row = i;
                col = j;
                break;
            }
        } 
        if (found){
            break;
        }
    }
    if (!found) return true;
    if (colour=='w'){
        // checking diagonals
        int i = row+1;
        int j = col+1;
        while (i<8&&j<8){
            if (pieceAt(i, j)=='b' || pieceAt(i, j)=='q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i++;
            j++;
        }
        i = row-1;
        j = col-1;
        while (i>=0&&j>=0){
            if (pieceAt(i, j)=='b' || pieceAt(i, j)=='q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i--;
            j--;
        }
        i = row+1;
        j = col-1;
        while (i<8&&j>=0){
            if (pieceAt(i, j)=='b' || pieceAt(i, j)=='q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i++;
            j--;
        }
        i = row-1;
        j = col+1;
        while (i>=0&&j<8){
            if (pieceAt(i, j)=='b' || pieceAt(i, j)=='q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i--;
            j++;
        }

        // checking forward/sideways
        for(int i = row+1; i<8; i++){
            if (pieceAt(i, col)=='r' || pieceAt(i, col)=='q'){
                return true;
            }
            else if(gameboard[i][col]!=nullptr){
                break;
            }
        }
        for(int i = col+1; i<8; i++){
            if (pieceAt(row, i)=='r'|| pieceAt(row, i)=='q'){
                return true;
            }
            else if(gameboard[row][i]!=nullptr){
                break;
            }
        }
        for(int i = row-1; i>=0; i--){
            if (pieceAt(i, col)=='r'|| pieceAt(i, col)=='q'){
                return true;
            }
            else if(gameboard[i][col]!=nullptr){
                break;
            }
        }
        for(int i = col-1; i>=0; i--){
            if (pieceAt(row, i)=='r'|| pieceAt(row, i)=='q'){
                return true;
            }
            else if(gameboard[row][i]!=nullptr){
                break;
            }
        }
        if(pieceAt(row+1, col+1)=='p'||pieceAt(row+1, col-1)=='p'){
            return true;
        }
        if(pieceAt(row+2, col+1)=='n'||pieceAt(row+1, col+2)=='n'||pieceAt(row-2, col+1)=='n'||pieceAt(row-2, col-1)=='n'||pieceAt(row+2, col-1)=='n'||pieceAt(row-1, col+2)=='n'||pieceAt(row-1, col-2)=='n'||pieceAt(row+1, col-2)=='n'){
            return true;
        }

        // to ensure piece doesn't move itself into checkmate
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (pieceAt(row+i, col+j) == 'k') return true;
            }
        }
    }
    else {
        //same thing but for other colour
        int i = row+1;
        int j = col+1;
        while (i<8&&j<8){
            if (pieceAt(i, j)=='B' || pieceAt(i, j)=='Q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i++;
            j++;
        }
        i = row-1;
        j = col-1;
        while (i>=0&&j>=0){
            if (pieceAt(i, j)=='B' || pieceAt(i, j)=='Q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i--;
            j--;
        }
        i = row+1;
        j = col-1;
        while (i<8&&j>=0){
            if (pieceAt(i, j)=='B' || pieceAt(i, j)=='Q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i++;
            j--;
        }
        i = row-1;
        j = col+1;
        while (i>=0&&j<8){
            if (pieceAt(i, j)=='B' || pieceAt(i, j)=='Q'){
                return true;
            }
            else if(gameboard[i][j]!=nullptr){
                break;
            }
            i--;
            j++;
        }
        for(int i = row+1; i<8; i++){
            if (pieceAt(i, col)=='R' || pieceAt(i, col)=='Q'){
                return true;
            }
            else if(gameboard[i][col]!=nullptr){
                break;
            }
        }
        for(int i = col+1; i<8; i++){
            if (pieceAt(row, i)=='R'|| pieceAt(row, i)=='Q'){
                return true;
            }
            else if(gameboard[row][i]!=nullptr){
                break;
            }
        }
        for(int i = row-1; i>=0; i--){
            if (pieceAt(i, col)=='R'|| pieceAt(i, col)=='Q'){
                return true;
            }
            else if(gameboard[i][col]!=nullptr){
                break;
            }
        }
        for(int i = col-1; i>=0; i--){
            if (pieceAt(row, i)=='R'|| pieceAt(row, i)=='Q'){
                return true;
            }
            else if(gameboard[row][i]!=nullptr){
                break;
            }
        }
        if(pieceAt(row-1, col+1)=='P'||pieceAt(row-1, col-1)=='P'){
            return true;
        }
        if(pieceAt(row+2, col+1)=='N'||pieceAt(row+1, col+2)=='N'||pieceAt(row-2, col+1)=='N'||pieceAt(row-2, col-1)=='N'||pieceAt(row+2, col-1)=='N'||pieceAt(row-1, col+2)=='N'||pieceAt(row-1, col-2)=='N'||pieceAt(row+1, col-2)=='N'){
            return true;
        }
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (pieceAt(row+i, col+j) == 'K') return true;
            }
        }
    }
    return false;
}

bool ChessBoard::validBoard(){
    //checks pawns on every area
    for (int i = 0; i < 8; i++){
        if (pieceAt(0, i)=='p'){
            return false;
        }
        else if (pieceAt(0, i)=='P'){
            return false;
        }
        else if (pieceAt(7, i)=='p'){
            return false;
        }
        else if (pieceAt(7, i)=='P'){
            return false;
        }
    }
    //ensures there is only 1 of each king
    int whiteKing = 0;
    int blackKing = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (pieceAt(i, j)=='k'){
                blackKing++;
                if (inCheck('b')){
                    return false;
                    }
            }
            if (pieceAt(i, j)=='K'){
                whiteKing++;
                if (inCheck('w')){
                    return false;
                }
            }
        }
    }
    if (whiteKing==1 && blackKing ==1){
        return true;
    }
    return false;
}

bool ChessBoard::hasAvailableMove(char colour){
    for(int i=0; i < 8; i++){
        for(int j=0; j < 8; j++){
            if (getPiece(i, j)!=nullptr && getPiece(i,j)->getColour()==colour && getPiece(i,j)->availableMoves(this).size()!=0){
                return true;
            }
        }
    }
    return false;
}

bool ChessBoard::notOnlyKing(){
    for(int i=0; i < 8; i++){
        for(int j=0; j < 8; j++){
            if (getPiece(i, j)!=nullptr && !(getPiece(i,j)->getChar()=='k' || getPiece(i,j)->getChar()=='K')){
                return true;
            }
        }
    }
    return false;
}


int ChessBoard::evaluate(char curPlayer) {
    int whiteValue = 0;
    int blackValue = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece *piece = getPiece(i,j);
            if (piece != nullptr) {
                if (piece->getColour() == 'w') {
                    whiteValue += piece->getValue();
                } else if (piece->getColour() == 'b') {
                    blackValue += piece->getValue();
                }
            }
        }
    }

    if (curPlayer == 'w') {
        return whiteValue - blackValue;
    } else {
        return blackValue - whiteValue;
    }
}

void ChessBoard::undoMove() {
    if (moveHistory.size() == 0) throw std::out_of_range{"No moves"}; // maybe throw exception

    changeTurn();
    LastMove move = moveHistory.back();
    moveHistory.pop_back();

    // moves piece back
    gameboard[move.prevCoords.row][move.prevCoords.col] = std::move(gameboard[move.newCoords.row][move.newCoords.col]);
    // if it was a first move, reset piece
    if (move.newCoords.firstMove) {
        char piece = pieceAt(move.prevCoords.row, move.prevCoords.col);
        if (piece == 'p' || piece == 'P') {
            gameboard[move.prevCoords.row][move.prevCoords.col].reset(new Pawn{move.prevCoords.row, move.prevCoords.col, curPlayer});
        } else if (piece == 'r' || piece == 'R') {
            gameboard[move.prevCoords.row][move.prevCoords.col].reset(new Rook{move.prevCoords.row, move.prevCoords.col, curPlayer});
        } else {
            gameboard[move.prevCoords.row][move.prevCoords.col].reset(new King{move.prevCoords.row, move.prevCoords.col, curPlayer});
        }
    } else {
        gameboard[move.prevCoords.row][move.prevCoords.col]->setCoords(move.prevCoords);
    }

    //en passant
    if (move.newCoords.enpassant) {
        int dir = 1;
        if (curPlayer == 'w') dir = -1;
        gameboard[move.newCoords.row + 1*dir][move.newCoords.col].reset(new Pawn{move.newCoords.row, move.newCoords.col, curPlayer, true});
    } else if (move.capturedPiece != ' ' && move.capturedPiece != '_') {
        placePiece(move.newCoords.row, move.newCoords.col, move.capturedPiece);
    }

    //promotion
    if (move.newCoords.promotion) {
        gameboard[move.prevCoords.row][move.prevCoords.col].reset(new Pawn{move.prevCoords.row, move.prevCoords.col, curPlayer, true});
    }

    //castle
    if (move.newCoords.castle) {
        int diff = move.newCoords.col - move.prevCoords.col;

        // moved left
        if (diff < 0) {
            gameboard[move.prevCoords.row][0] = std::move(gameboard[move.prevCoords.row][move.newCoords.col+1]);
            gameboard[move.prevCoords.row][0].reset(new Rook{move.prevCoords.row, 0, curPlayer});
        } 
        else {
            gameboard[move.prevCoords.row][7] = std::move(gameboard[move.prevCoords.row][move.newCoords.col-1]);
            gameboard[move.prevCoords.row][7].reset(new Rook{move.prevCoords.row, 7, curPlayer});
        }
    }
}

LastMove ChessBoard::getLastMove() {
    if (moveHistory.size() == 0) throw std::out_of_range{"No moves"};
    return moveHistory.back();
}

bool ChessBoard::getSetupMode(){
    return setupMode;
}

void ChessBoard::setSetupMode(bool set){
    setupMode=set;
}
