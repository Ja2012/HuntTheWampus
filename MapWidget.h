#pragma once

#include "FLTK.h"
#include "Properties.h"
#include "CaveWidget.h"

class MapWidget : Fl_Box
{
public:
	MapWidget(Fl_Image* Image, int X = Props::MapImgPos.X, int Y = Props::MapImgPos.Y, 
		int W = Props::MapImgSize.X, int H = Props::MapImgSize.Y) : Fl_Box(X, Y, W, H)
	{
		//box(Fl_Boxtype::_FL_ROUND_DOWN_BOX);
		//color(FL_WHITE);
		image(Image);
		//box(FL_BORDER_BOX);

		//CaveWidget* CaveWid1 = new CaveWidget(0, 0);
		CaveWidget* CaveWid1 = new CaveWidget(x() + Resize(250), y() + Resize(70, false), "1");
	}
private:
};
