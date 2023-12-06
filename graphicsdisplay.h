#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "window.h"
#include "observer.h"
#include "piece.h"

// Black cell - light off, white cell - light on
class GraphicsDisplay: public Observer {
  int gridSize; // number of rows and columns we have
  int rectSize; // size of each rect based on gridSize
  Xwindow &xw; // reference to Xwindow so we can update it
  const int windowSize = 1080; // windows will be 1080 x 1080
 public:
  GraphicsDisplay(int gridSize, Xwindow &xw);  // Display starts all black (all lights off)
  void notify(const Piece &p, int oldX, int oldY) override; // when cell notifies, we will switch the colour of the rect
  ~GraphicsDisplay();
};

#endif
