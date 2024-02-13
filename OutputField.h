#pragma once
#include "FLTK.h"

class OutputField : public Fl_Text_Display
{
public:
	OutputField(int X, int Y, int W, int H);
	Fl_Text_Buffer* Buffer = new Fl_Text_Buffer();

};

