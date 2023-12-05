#include "game.h"
#include "window.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{   
    Xwindow xw{};
    string cmd;

    bool undoEnabled = false;
    string flag = argc > 1 ? argv[argc - 1] : "";
    // enabling enhancements
    if (flag == "-enablebonus") {
        undoEnabled = true;
    }

    float player1 = 0;
    float player2 = 0;
    Game game{xw, player1, player2};

    while (true) {
        cin >> cmd;
        if (cin.eof()) break;

        if (cmd == "game" && !game.isGameActive()) {
            string p1, p2;
            cin >> p1 >> p2;
            if ((p1 == "human" || p1 == "computer[1]" || p1 == "computer[2]" || p1 == "computer[3]" || p1 == "computer[4]") &&
                (p2 == "human" || p2 == "computer[1]" || p2 == "computer[2]" || p2 == "computer[3]" || p2 == "computer[4]")) {
                game.init(p1, p2);
                std::cout << game;
            }
        } else if (cmd == "resign" && game.isGameActive()) {
            game.resign(game.getTurn());
        } else if (cmd == "move" && game.isGameActive()) {
            game.move(game.getTurn());
            std::cout << game;
        } else if (cmd == "setup" && !game.isGameActive()) {
            game.setUp();
            std::cout << game;
            while (true) {
                cin >> cmd;
                if (cmd == "+") {
                    char piece;
                    string coords;
                    cin >> piece >> coords;
                    game.addPiece(piece, coords);
                    std::cout << game;
                } else if (cmd == "-") {
                    string coords;
                    cin >> coords;
                    game.removePiece(coords);
                    std::cout << game;
                } else if (cmd == "=") {
                    string colour;
                    cin >> colour;
                    game.setTurn(colour);
                } else if (cmd == "done") {
                    if (game.verifySetup()) {
                        break;
                    }
                }
            }
        } else if (cmd == "undo" && game.isGameActive() && undoEnabled) {
            game.undo();
            std::cout << game;
        } else {
            std::cerr << "Invalid command" << endl; 
        }
    }

    std::cout << "Final Score:" << endl;
    std::cout << "White: " << player1 << endl;
    std::cout << "Black: " << player2 << endl;
}
