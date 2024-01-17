#pragma once

#include <vector>
#include <iostream>

#include "FLTK.h"
#include "Properties.h"
#include "CaveWidget.h"

class MapWidget : Fl_Box
{
public:
	std::vector<CaveWidget*> Caves;

	MapWidget(Fl_Image* Image, int X = Props::MapImgPos.X, int Y = Props::MapImgPos.Y, 
		int W = Props::MapImgSize.X, int H = Props::MapImgSize.Y) : Fl_Box(X, Y, W, H)
	{
		image(Image);

		Caves.push_back(nullptr);
		for (int i = 1; i < Consts::CaveWidgetPoss.size(); ++i)
		{

			Caves.push_back(new CaveWidget(x() + Resize(std::get<1>(Consts::CaveWidgetPoss[i])),
				y() + Props::CaveDrawYOffset + Resize(std::get<2>(Consts::CaveWidgetPoss[i]), false),
				std::get<0>(Consts::CaveWidgetPoss[i]))
			);
		}
	}
private:
};
