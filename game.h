#ifndef GAME_H
#define GAME_H
#include <memory>
#include <iostream>
#include "textdisplay.h"
#include "board.h"

class Game {
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<Board> chessboard;
    public:
        void init();
};

#endif
