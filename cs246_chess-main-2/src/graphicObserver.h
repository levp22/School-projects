#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "observer.h"
#include "window.h"

class ChessBoard;

class GraphicObserver : public Observer
{
    ChessBoard *subject;
    Xwindow display;

public:
    GraphicObserver(ChessBoard *subject);
    void notify() override;
    ~GraphicObserver();
};

#endif
