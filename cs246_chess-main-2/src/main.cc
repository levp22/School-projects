#include "chessboard.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "textobserver.h"
#include "graphicObserver.h"
#include "computer.h"
#include <vector>
#include <iostream>
#include "human.h"
#include "controller.h"
#include <memory>

int convertRow(int row)
{
    return row - 1;
}
int convertCol(char col)
{
    return col -97;
}

int main()
{
    // make a new chessboard
    ChessBoard chessboard;
    TextObserver textOb{&chessboard};
    GraphicObserver graphicOb{&chessboard};
    std::string command;
    int wScore = 0;
    int bScore = 0;
    Computer c{'w', &chessboard, 3};
    Computer d{'b', &chessboard, 2};
    while (std::cin >> command)
    {
        if (command == "game")
        {
            chessboard.setSetupMode(false);
            std::string whitePlayer;
            std::cin >> whitePlayer;
            std::vector<std::unique_ptr<Controller>> controllers;
            if (whitePlayer == "human")
            {
                controllers.emplace_back(new Human{'w', &chessboard});
            }
            else if (whitePlayer == "computer")
            {
                int level;
                std::cin >> level;
                controllers.emplace_back(new Computer{'w', &chessboard, level});
            }
            // should we throw an exception for else
            std::string blackPlayer;
            std::cin >> blackPlayer;
            if (blackPlayer == "human")
            {
                controllers.emplace_back(new Human{'b', &chessboard});
            }
            else if (blackPlayer == "computer")
            {
                int level;
                std::cin >> level;
                controllers.emplace_back(new Computer{'b', &chessboard, level});
            }
            // should we throw an exception for else
            // now start being able to make moves
            while (true)
            {
                std::cin >> command;
                char curTurn = chessboard.getTurn();
                if (command == "resign")
                {
                    if (curTurn == 'b')
                    {
                        std::cout << "White wins!" << std::endl;
                        wScore++;
                    }
                    else
                    {
                        std::cout << "Black wins!" << std::endl;
                        bScore++;
                    }
                    break;
                }
                else if (command == "move")
                {
                    try
                    {
                        if (curTurn == 'b')
                        {
                            controllers[1]->nextMove();
                            bool check = chessboard.inCheck('w');
                            bool hasMoves = chessboard.hasAvailableMove('w');
                            if (check && hasMoves)
                            {
                                std::cout << "White is in check." << std::endl;
                            }
                            else if (check && !hasMoves)
                            {
                                bScore++;
                                std::cout << "Checkmate! Black wins!" << std::endl;
                                break;
                            }
                            else if (!check && !hasMoves)
                            {
                                wScore = wScore + 0.5;
                                bScore = bScore + 0.5;
                                std::cout << "Stalemate!" << std::endl;
                                break;
                            }
                        }
                        else
                        {
                            controllers[0]->nextMove();
                            bool check = chessboard.inCheck('b');
                            bool hasMoves = chessboard.hasAvailableMove('b');
                            if (check && hasMoves)
                            {
                                std::cout << "Black is in check." << std::endl;
                            }
                            else if (check && !hasMoves)
                            {
                                wScore++;
                                std::cout << "Checkmate! White wins!" << std::endl;
                                break;
                            }
                            else if (!check && !hasMoves)
                            {
                                wScore = wScore + 0.5;
                                bScore = bScore + 0.5;
                                std::cout << "Stalemate!" << std::endl;
                                break;
                            }
                        }
                        if (!chessboard.notOnlyKing())
                        {
                            wScore = wScore + 0.5;
                            bScore = bScore + 0.5;
                            std::cout << "Stalemate!" << std::endl;
                            break;
                        }
                        chessboard.notifyObservers();
                        // chessboard.changeTurn();
                    } catch(std::out_of_range m) {
                        std::cout << m.what() << std::endl;
                    }
                }
                else if (command == "undo")
                {
                    try
                    {
                        chessboard.setSetupMode(true);
                        chessboard.undoMove();
                        chessboard.notifyObservers();
                        chessboard.setSetupMode(false);
                    }
                    catch (std::out_of_range m)
                    {
                        std::cout << m.what() << std::endl;
                    }
                }
               
            }
            // reset the board
            chessboard.reset();
            chessboard.notifyObservers();
        }
        else if (command == "setup")
        {
            std::cout<< "entering setup mode" << std::endl;
            while (true)
            {
                std::cin >> command;
                if (command == "+")
                {
                    int row;
                    char type, col;
                    std::cin >> type >> col >> row;
                    // convert row and col
                    row = convertRow(row);
                    int newCol = convertCol(col);
                    chessboard.placePiece(row, newCol, type); // throw exception in place Piece or just don't do anything
                    chessboard.notifyObservers();
                }
                else if (command == "done")
                {
                    if (chessboard.validBoard())
                    {
                        std::cout<< "setup mode left" << std::endl;
                        break;
                    }
                    else {
                        std::cout<< "invalid board" << std::endl;
                    }
                }
                else if (command == "-")
                {
                    int row;
                    char col;
                    std::cin >> col >> row;
                    row = convertRow(row);
                    int newCol = convertCol(col);
                    if (chessboard.removePiece(row, newCol))
                        chessboard.notifyObservers();
                }
                else if (command == "=")
                {
                    char colour;
                    std::cin >> colour;
                    chessboard.setTurn(colour);
                }
            }
        }
    }
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << wScore << std::endl;
    std::cout << "Black: " << bScore << std::endl;
}
