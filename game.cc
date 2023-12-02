#include <iostream>
#include "game.h"
using namespace std;

void Game::init() {
  td = make_unique<TextDisplay>(8);
  chessboard = make_unique<Board>(td.get());

  char c;
  while (cin >> c)
    {
        if (c == 'p')
        {
            cout << *chessboard;
        }
        else if (c == 'a')
        {
            char c;
            cin >> c;
            int a, b, d;
            cin >> a >> b >> d;
            chessboard->addPiece(c, a, b, d);
        }
        else if (c == 'r') {
            int x, y;
            cin >> x >> y;
            chessboard->removePiece(x, y);
        }
        else
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            bool y = chessboard->moveSuccess(a, b, c, d);
        }
    }
}