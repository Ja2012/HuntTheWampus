#pragma once

#include <vector>

#include "FLTK.h"
#include "Properties.h"
class ShootDialog : public Fl_Group
{
public:
	ShootDialog(int Width = Props::SDSizeX, int Height = Props::SDSizeY);
	//virtual void draw_overlay();

	Fl_Text_Buffer* PathOutBuffer = new Fl_Text_Buffer();
	Fl_Text_Display* PathOut;

	Fl_Button* EraseBtn;
	Fl_Button* CancelBtn;
	Fl_Button* CaveBtn[20];
	Fl_Button* FireBtn;

	std::vector<int> GetSelectedCaves();

};