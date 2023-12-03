#ifndef GAME_H
#define GAME_H
#include <memory>
#include <iostream>
#include <vector>
#include <string>

#include "textdisplay.h"
#include "board.h"
#include "player.h"
#include "piece.h"

class Game {
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<Board> chessboard;
    std::vector<std::unique_ptr<Player>> players;
    Colour turn;

    std::vector<int> convertCoords(std::string coords) const;
    public:
        Game();
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
        friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
