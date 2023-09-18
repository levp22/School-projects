#include "controller.h"
#include "chessboard.h"
#include "piece.h"

char Controller::getColour() { return colour; }

ChessBoard* Controller::getBoard() { return chessboard; }

Controller::Controller(char colour, ChessBoard *chessboard) : colour{colour}, chessboard{chessboard} {}
