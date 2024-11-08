#pragma once

#include <vector>
#include <iostream>

#include "FLTK.h"
#include "Properties.h"
#include "CaveWidget.h"

class MapWidget : public Fl_Box
{
public:
	MapWidget(Fl_Image* Image, int X = Props::MapImgPos.X, int Y = Props::MapImgPos.Y,
		int W = Props::MapImgSize.X, int H = Props::MapImgSize.Y);
	std::vector<CaveWidget*> CaveWidgets;

	void ShowCave(int CaveNumber);
	void SetPlayerCaveMark(int CaveNumber);
	void UnsetPlayerCaveMark(int CaveNumber);
};
