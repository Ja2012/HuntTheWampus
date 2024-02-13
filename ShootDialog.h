#pragma once

#include <vector>

#include "FLTK.h"
#include "Properties.h"
#include "BowWidget.h"
#include "OutputField.h"
class ShootDialog : public Fl_Group
{
public:
	ShootDialog(int Width = Props::SDSizeX, int Height = Props::SDSizeY);

	OutputField* PathOut;

	Fl_Button* EraseBtn;
	Fl_Button* CaveBtn[20];

	Fl_PNG_Image* BowImg = static_cast<Fl_PNG_Image*>(Fl_PNG_Image(Consts::BowImgFileName).copy(Props::BowBtnSizeX, Props::BowBtnSizeY));
	BowWidget* BowBtn = new BowWidget(BowImg);

	std::vector<int> GetSelectedCaves();

};