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
    std::unique_ptr<TextDisplay> td;            // Text display for the chessboard
    std::unique_ptr<GraphicsDisplay> gd;        // Graphics display for the chessboard
    std::unique_ptr<Board> chessboard;             // The chessboard
    std::vector<std::unique_ptr<Player>> players;   // List of players.
    Colour turn;                                // Current player's turn.
    bool gameActive;                            // Game's current state
    bool setupUsed;                             // Determines to use a default board or setup board
    Xwindow &xw;                                // Xwindow for graphical display.
    float &whiteScore;                          // White player's score
    float &blackScore;                          // Black player's score

    std::vector<int> convertCoords(std::string coords) const;
    public:
        Game(Xwindow &xw, float &whiteScore, float &blackScore);

        // Initialize the game with players
        void init(std::string p1, std::string p2);

        // Add a player to the game.
        void addPlayer(std::string player, Colour colour);

        // Add a piece to the chessboard.
        void addPiece(char piece, std::string coords);

        // Remove a piece from the chessboard.
        void removePiece(std::string coords);

        // Perform a player's move.
        void move(Colour curTurn);

        // Resign the game on behalf of a player.
        void resign(Colour curTurn);

        // Verify if the initial setup is valid.
        bool verifySetup() const;

        // // Get the current player's turn.
        Colour getTurn() const;

        // Set the current player's turn based on a string.
        void setTurn(std::string colour);

        // Check if the game is active.
        bool isGameActive() const;

        friend std::ostream &operator<<(std::ostream &out, const Game &g);

        // Undo the last move.
        void undo();

        // Set up the initial chessboard position.
        void setUp();
};

#endif
