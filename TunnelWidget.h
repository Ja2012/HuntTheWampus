#pragma once

#include "FLTK.h"
#include "Properties.h"

class TunnelWidget : public Fl_Box
{
public:
	TunnelWidget(Fl_Image* Image, int X, int Y, int W = Props::TunnelImgSize.X, int H = Props::TunnelImgSize.Y) : Fl_Box(X, Y, W, H)
	{
		image(Image);
	}

};
