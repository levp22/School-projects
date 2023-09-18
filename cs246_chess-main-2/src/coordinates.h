#ifndef COORDINATES_H
#define COORDINATES_H

struct Coordinates {
    int row, col;
    bool capture, check, promotion, enpassant, castle, firstMove;
    Coordinates(int row, int col, bool capture=false, bool check=false, bool promotion=false, bool enpassant=false, bool castle=false, bool firstMove=false) : 
        row{row}, col{col}, capture{capture}, check{check}, promotion{promotion}, enpassant{enpassant}, castle{castle}, firstMove{firstMove} {}
};

#endif
