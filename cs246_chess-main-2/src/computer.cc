#include "computer.h"
#include "chessboard.h"
#include "piece.h"
#include <cstdlib>
#include <chrono>
#include <limits>
#include <algorithm>
#include "textobserver.h"

Computer::Computer(char colour, ChessBoard* chessboard, int difficulty) : Controller{colour, chessboard}, difficulty{difficulty} {}

// randomly chooses a piece, randomly chooses an available move from that piece
void Computer::randomMove() {
    std::vector<Piece*> pieces = getBoard()->getPieces(getColour());
    while (true) {
        unsigned int sysTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        std::srand(sysTime); // resets randomized seed

        int randPieceID = std::rand() % pieces.size();
        Piece* randPiece = pieces[randPieceID];

        if (randPiece != nullptr) {
            // check possible moves, if move is valid, move accordingly
            std::vector<Coordinates> moveCoords = randPiece->availableMoves(getBoard());
            if (moveCoords.size() == 0) continue;
            int randMoveID = std::rand() % moveCoords.size();
            Coordinates prevCoords = randPiece->getCoords();
            getBoard()->advancePiece(prevCoords.row, prevCoords.col, moveCoords[randMoveID]);
            return;
        }
    }
}

// looks for capturing moves + checks
bool Computer::checkCaptureMove() {
    std::vector<Piece*> pieces = getBoard()->getPieces(getColour());
    for (auto p: pieces) {
        Coordinates prevCoords = p->getCoords();
        for (auto m: p->availableMoves(getBoard())) {
            if (m.check || m.capture) {
                getBoard()->advancePiece(prevCoords.row, prevCoords.col, m);
                return true;
            }
        }
    }
    return false;
}

// Looks through opponents pieces, sees if they are attacking our piece, and advances it if so
bool Computer::avoidCaptureMove() {
    char opposingColour;
    if (getColour() == 'w') opposingColour = 'b';
    else opposingColour = 'w';
    std::vector<Piece*> pieces = getBoard()->getPieces(opposingColour);
    for (auto p: pieces) {
        for (auto m: p->availableMoves(getBoard())) {
            if (m.capture) {
                for (auto m2: getBoard()->getPiece(m.row, m.col)->availableMoves(getBoard())) {
                    getBoard()->advancePiece(m.row, m.col, m2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Computer::avoidCaptureMoveAndEnsureSafe() {
    char opposingColour;
    if (getColour() == 'w') opposingColour = 'b';
    else opposingColour = 'w';
    std::vector<Piece*> pieces = getBoard()->getPieces(opposingColour);
    for (auto p: pieces) {
        for (auto m: p->availableMoves(getBoard())) {
            if (m.capture) {
                //checks each possible move of attacked piece and finds one that is safe to move to
                for (auto m2: getBoard()->getPiece(m.row, m.col)->availableMoves(getBoard())) {
                    ChessBoard tmp = *getBoard();
                    tmp.advancePiece(m.row, m.col, m2);
                    pieces = tmp.getPieces(opposingColour);
                    bool safe = true;
                        for (auto p2: pieces){
                            for (auto m3: p2->availableMoves(&tmp)){
                                if(m3.capture){
                                    safe = false;
                                }
                            }
                        }
                    if (safe){
                        getBoard()->advancePiece(m.row, m.col, m2);
                        return true;
                    }
                }
                    return false;
            }
        }
    }
    return false;
}

int Computer::negamax(int depth, ChessBoard chessboard, int alpha, int beta) {
    if (depth == 0) {
        return chessboard.evaluate(chessboard.getTurn());
    }

    if (!chessboard.hasAvailableMove(chessboard.getTurn())) {
        if (chessboard.inCheck(chessboard.getTurn())) {
            return std::numeric_limits<int>::min();
        }
        return 0;
    }

    int value = std::numeric_limits<int>::min();
    
    for (auto p: chessboard.getPieces(chessboard.getTurn())) {
        bool running = true;
        Coordinates prevCoords = p->getCoords();
        for (auto m: p->availableMoves(&chessboard)) {
            chessboard.advancePiece(prevCoords.row, prevCoords.col, m);
            value = std::max(value, -negamax(depth - 1, chessboard, -beta, -alpha));
            chessboard.undoMove();
            alpha = std::max(alpha, value);
            if (alpha >= beta) {
                running = false;
                break;
            }
        }
        if (!running) break;
    }

    return value;
}

void Computer::negamaxRoot(int depth) {
    ChessBoard* chessboard = getBoard();

    int pieceID = 0;
    int moveID = 0;
    int max = std::numeric_limits<int>::min();

    int pieceCounter = 0;
    std::vector<Piece*> pieces = chessboard->getPieces(getColour());

    bool finished = false;
    
    for (auto p: pieces) {
        int moveCounter = 0;
        Coordinates prevCoords = p->getCoords();
        std::vector<Coordinates> moves = p->availableMoves(chessboard);
        for (auto m: moves) {
            chessboard->advancePiece(prevCoords.row, prevCoords.col, m);            
            //int moveValue = negamax(3, *chessboard);
            int moveValue = negamax(depth, *chessboard, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            if (moveValue > max) {
                max = moveValue;
                moveID = moveCounter;
                pieceID = pieceCounter;
            }
            chessboard->undoMove();
            moveCounter++;
        }
        pieceCounter++;
        if (pieceCounter == pieces.size()) finished = true;
    }

    if (finished) {

        Piece *piece = chessboard->getPieces(getColour())[pieceID];

        Coordinates prevCoords = piece->getCoords();
        Coordinates bestMove = piece->availableMoves(getBoard())[moveID];

        getBoard()->advancePiece(prevCoords.row, prevCoords.col, bestMove);
    }
}

void Computer::nextMove() {
    if (difficulty == 1) {
        randomMove();
    } else if (difficulty == 2) {
        if (!checkCaptureMove()) randomMove();
    } else if (difficulty == 3) {
        if (!avoidCaptureMove()) {
            if (!checkCaptureMove()) randomMove();
        }
    }
        else if (difficulty == 4) {
        if (!avoidCaptureMoveAndEnsureSafe()) {
            if (!checkCaptureMove()) randomMove();
        }
    } else {
        //depth is difficulty level - 2
        negamaxRoot(difficulty-2);
    }
}
