#pragma once

#include "FLTK.h"
#include "Properties.h"

class ArrowWidget : public Fl_Box
{
public:
	ArrowWidget(Fl_Image* Image, int X, int Y, int W = Props::ArrowImgSizeX, int H = Props::ArrowImgSizeY) : Fl_Box(X, Y, W, H)
	{
		image(Image);
	}

};
