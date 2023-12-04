#include <string>
#include "graphicsdisplay.h"
#include "piece.h"

GraphicsDisplay::GraphicsDisplay(int gridSize, Xwindow &xw): gridSize{gridSize}, xw{xw} {
  xw.fillRectangle(0, 0, windowSize, windowSize, xw.Gray);
	rectSize = windowSize / gridSize;
	for (int i = 0; i < 8; ++i) {
		char yAxisChar = '8' - i;
		char xAxisChar = 'a' + i;
		std::string yAxisStr(1, yAxisChar);
		std::string xAxisStr(1, xAxisChar);
		xw.drawString((rectSize / 2), (i + 0.5) * rectSize, yAxisStr);
		xw.drawString((i + 1.5) * rectSize, windowSize - (rectSize / 2), xAxisStr);
	}
}

void GraphicsDisplay::notify(const Piece &p, int oldX, int oldY) {
  int oldBackgroundColour = ((oldX + oldY) % 2 == 0) ? xw.White : xw.Black;
  xw.fillRectangle((oldY + 1) * rectSize, oldX * rectSize, rectSize, rectSize, oldBackgroundColour);
	Type type = p.getType();
	Colour pieceColour = p.getColour();
	int x = p.getX();
	int y = p.getY();

  int backgroundColour = ((x + y) % 2 == 0) ? xw.White : xw.Black;
	xw.fillRectangle((y + 1) * rectSize, x * rectSize, rectSize, rectSize, backgroundColour);
	if (type != Type::Nullpiece) {
		char c;
		switch(type) {
			case Type::Pawn:
				c = 'P';
				break;
			case Type::Queen:
				c = 'Q';
				break;
			case Type::King:
				c = 'K';
				break;
			case Type::Bishop:
				c = 'B';
				break;
			case Type::Knight:
				c = 'N';
				break;
			case Type::Rook:
				c = 'R';
				break;
			default: 
				break;
		}
		if (pieceColour == Colour::Black) {
			c += 'a' - 'A'; // convert to lower case character.
		}
		std::string s(1, c);
		xw.fillRectangle((y + 1.25) * rectSize, (x + 0.25) * rectSize, rectSize * 0.5, rectSize * 0.5, xw.Gray);
		xw.drawString((y + 1.5) * rectSize, (x + 0.5) * rectSize, s);
	}
}

GraphicsDisplay::~GraphicsDisplay() {}
