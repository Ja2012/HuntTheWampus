#pragma once
#include "FLTK.h"

class CaveNumberWidget : public Fl_Button
{
public:
	CaveNumberWidget(int Number, int X, int Y, int W, int H);
	int Number;
};