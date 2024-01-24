#pragma once

#include <vector>
#include <iostream>

#include "FLTK.h"
#include "Properties.h"
#include "CaveWidget.h"

class MapWidget : Fl_Box
{
public:
	MapWidget(Fl_Image* Image, int X = Props::MapImgPos.X, int Y = Props::MapImgPos.Y,
		int W = Props::MapImgSize.X, int H = Props::MapImgSize.Y);
	std::vector<CaveWidget*> CaveWidgets;
private:
};
