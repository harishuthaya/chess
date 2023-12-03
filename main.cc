// #include "board.h"
// #include "queen.h"
#include "game.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string cmd;
    Game game;

    while (true) {
        cin >> cmd;
        if (cin.eof()) break;

        if (cmd == "game") {
            string p1, p2;
            cin >> p1 >> p2;
            game.init(p1, p2);
        } else if (cmd == "resign") {
            game.resign();
        } else if (cmd == "move") {
            game.move();
        } else if (cmd == "setup") {
            while (true) {
                cin >> cmd;
                if (cmd == "+") {
                    char piece;
                    string coords;
                    cin >> piece >> coords;
                    game.addPiece(piece, coords);
                    cout << game;
                } else if (cmd == "-") {
                    string coords;
                    cin >> coords;
                    game.removePiece(coords);
                    cout << game;
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
        }
    }
}


// // void printBoard(Board &chessBoard)
// // {
// //     for (int i = 0; i < chessBoard.getSize(); i++)
// //     {
// //         for (int j = 0; j < chessBoard.getSize(); j++)
// //         {
// //             Piece *piece = chessBoard.getPiece(i, j);
// //             if (piece->getType() == Type::Nullpiece)
// //             {
// //                 cout << '_';
// //             }
// //             else
// //             {
// //                 if (piece->getColour() == Colour::Black)
// //                 {
// //                     if (piece->getType() == Type::Queen) {
// //                         cout << 'q';
// //                     } else if (piece->getType() == Type::Bishop) {
// //                         cout << 'b';
// //                     }
// //                 }
// //                 else
// //                 {
// //                     if (piece->getType() == Type::Queen) {
// //                         cout << 'Q';
// //                     } else if (piece->getType() == Type::Bishop) {
// //                         cout << 'B';
// //                     }
// //                 }
// //             }
// //         }
// //         cout << endl;
// //     }
// // }

// int main()
// {
//     Board chessBoard;
//     char c;
//     while (cin >> c)
//     {
//         if (c == 'p')
//         {
//             printBoard(chessBoard);
//         }
//         else if (c == 'a')
//         {
//             char c;
//             cin >> c;
//             int a, b, d;
//             cin >> a >> b >> d;
//             chessBoard.addPiece(c, a, b, d);
//         }
//         else
//         {
//             int a, b, c, d;
//             cin >> a >> b >> c >> d;
//             bool y = chessBoard.moveSuccess(a, b, c, d);
//         }
//     }
// }
