#include "graphicObserver.h"
#include "chessboard.h"
#include "window.h"

GraphicObserver::GraphicObserver(ChessBoard *board) : subject{board}
{
    subject->attach(this);
    int x = 0;
    int y = 0;
    const int width = 50;
    const int length = 50;
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j < 8; ++j)
        {

            if (i % 2 == j % 2)
            {
                display.fillRectangle(x, y, width, length, Xwindow::White);
            }
            else
            {
                display.fillRectangle(x, y, width, length, Xwindow::Green);
            }
            if (!(subject->pieceAt(i, j) == '_' || subject->pieceAt(i, j) == ' '))
            {
            std::string piece(1, subject->pieceAt(i, j));
            display.drawString(x + 25, y + 25, piece);
            }
            x = x + 50;
        }
        x = 0;
        y = y + 50;
     }
}

void GraphicObserver::notify()
{
    int x = 0;
    int y = 0;
    const int width = 50;
    const int length = 50;
    ChessBoard tmp = *subject;
    //if not in setup mode can use undo function to determine the boards changes
    if (subject->getSetupMode()){
         for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (i % 2 == j % 2)
            {
                display.fillRectangle(x, y, width, length, Xwindow::White);
            }
            else
            {
                display.fillRectangle(x, y, width, length, Xwindow::Green);
            }
            if (!(subject->pieceAt(i, j) == '_' || subject->pieceAt(i, j) == ' '))
            {
            std::string piece(1, subject->pieceAt(i, j));
            display.drawString(x + 25, y + 25, piece);
            }
            x = x + 50;
        }
        x = 0;
        y = y + 50;
    }
    } else{
        tmp.undoMove();
        for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if(tmp.pieceAt(i, j)!=subject->pieceAt(i,j)){ //only displays if there is a differen e
            if (i % 2 == j % 2)
            {
                display.fillRectangle(x, y, width, length, Xwindow::White);
            }
            else
            {
                display.fillRectangle(x, y, width, length, Xwindow::Green);
            }
            if (!(subject->pieceAt(i, j) == '_' || subject->pieceAt(i, j) == ' '))
            {
            std::string piece(1, subject->pieceAt(i, j));
            display.drawString(x + 25, y + 25, piece);
            }
            }
            x = x + 50;
        }
        x = 0;
        y = y + 50;
    }
    }
}

GraphicObserver::~GraphicObserver() { subject->detach(this); }
