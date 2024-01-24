#pragma once

#include "FLTK.h"
#include "Properties.h"
#include "Point.h"
#include "Line.h"

class CaveWidget : public Fl_Box
{
public:
	CaveWidget(int X, int Y,
		const char* Label,
		Point AdjCave1, Point AdjCave2, Point AdjCave3,
		int W = Props::CaveWidSize.X, int H = Props::CaveWidSize.Y
	);
	void draw();
private:
	Line Line1;
	Line Line2;
	Line Line3;
	bool VisibleTunnels{ false };
};