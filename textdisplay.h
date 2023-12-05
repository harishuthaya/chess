#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "piece.h"
class Piece;

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay; // 2D vector representing the display grid.
  const int gridSize; // size of the grid
 public:
  TextDisplay(int n); 

  // Notifies the display about a change in a piece's state or position.
  void notify(const Piece &p, int oldX, int oldY) override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
