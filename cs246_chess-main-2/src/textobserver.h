#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include <iostream>

class ChessBoard;

class TextObserver: public Observer {
    std::ostream &out = std::cout;

    ChessBoard *subject;
    public:
        TextObserver(ChessBoard* chessboard);
        void notify() override;
        ~TextObserver();
};

#endif
