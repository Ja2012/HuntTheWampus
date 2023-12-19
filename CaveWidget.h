#pragma once

#include "FLTK.h"
#include "Properties.h"

class CaveWidget : Fl_Box
{
public:
	CaveWidget(int X, int Y,
		const char* Label,
		int W = Props::CaveWidSize.X, int H = Props::CaveWidSize.Y
	) : Fl_Box(FL_NO_BOX, X, Y, W, H, Label)
	{
		color(FL_BLACK);
		labeltype(_FL_EMBOSSED_LABEL);
		labelsize(h() * 2 / 3);
		labelfont(FL_TIMES_BOLD_ITALIC);	
		//InsideBox = new Fl_Box(FL_OVAL_FRAME, x() + (w () / 20), y() + (h() / 20), w() - (w() / 10), h() - (h() / 10), Label);
		//InsideBox->color(FL_WHITE);

	}
	Fl_Box* InsideBox;

};