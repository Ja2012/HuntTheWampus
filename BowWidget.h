#pragma once

#include "FLTK.h"
#include "Properties.h"

class BowWidget : public Fl_Button
{
public:
	BowWidget(Fl_Image* Image, int X = Props::BowBtnPosX, int Y = Props::BowBtnPosY, int W = Props::BowBtnSizeX, int H = Props::BowBtnSizeY);
private:
};
