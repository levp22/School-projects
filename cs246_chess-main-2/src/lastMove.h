#ifndef LASTMOVE_H
#define LASTMOVE_H
#include "coordinates.h"

struct LastMove {
    Coordinates prevCoords;
    Coordinates newCoords;
    char capturedPiece;
    LastMove(Coordinates prevCoords, Coordinates newCoords, char capturedPiece) : prevCoords{prevCoords}, newCoords{newCoords}, capturedPiece{capturedPiece} {}
};

#endif
