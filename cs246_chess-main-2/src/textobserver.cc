#include "textobserver.h"
#include "chessboard.h"

TextObserver::TextObserver(ChessBoard *chessboard) : subject{chessboard} { subject->attach(this); }

void TextObserver::notify() {
    for (int i = 7; i >= 0; i--) {
        out << i + 1 << " ";
        for (int j = 0; j < 8; j++) {
            out << subject->pieceAt(i, j);
        }
        out << std::endl;
    }
    out << "  abcdefgh" << std::endl;
}

TextObserver::~TextObserver() { subject->detach(this); }
