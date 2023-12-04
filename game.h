#ifndef GAME_H
#define GAME_H
#include <memory>
#include <iostream>
#include <vector>
#include <string>

#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "board.h"
#include "player.h"
#include "piece.h"

enum class GameState { NoGame, GameRunning, Player1Win, Player2Win, Tie };

class Game {
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<GraphicsDisplay> gd;
    std::unique_ptr<Board> chessboard;
    std::vector<std::unique_ptr<Player>> players;
    Colour turn;
    bool gameActive;
    Xwindow &xw;

    std::vector<int> convertCoords(std::string coords) const;
    public:
        Game(Xwindow &xw);
        void init(std::string p1, std::string p2);
        void addPlayer(std::string player, Colour colour);
        void addPiece(char piece, std::string coords);
        void removePiece(std::string coords);
        void move(Colour curTurn);
        void resign(Colour curTurn);
        bool verifySetup() const;
        Colour getTurn() const;
        void setTurn(std::string colour);
        std::vector<int> getScores() const;
        bool isGameActive() const;
        friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
