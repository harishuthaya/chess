#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include "piece.h"
#include "player.h"
#include "board.h"

class Computer: public Player {
    int level;
    Board *board;

    // Helper functions
    std::string convertCoords(int x, int y) const;
    std::vector<int> convert(const std::string& coords) const;
    
    // 4 levels of computer for generating moves
    std::vector<std::string> generateLevel1();
    std::vector<std::string> generateLevel2();
    std::vector<std::string> generateLevel3();
    std::vector<std::string> generateLevel4();
    
    // Returns a list of all moves
    std::vector<std::vector<std::string>> generateAllMoves();

    // Returns the score for a move calculated based on its effectiveness
    int scoreMove(int startX, int startY, int endX, int endY);

    // Returns the value of a piece based on its importance
    int getPieceValue(Type pieceType);



    public: 
        Computer(Colour colour, int level, Board *board);

        // Returns a computer generated move
        std::vector<std::string> getMove() override;

        // Gets the pawn promotion piece option
        char getPromotion() const override;
};

#endif
