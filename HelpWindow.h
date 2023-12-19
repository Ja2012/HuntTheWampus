#pragma once

#include "FLTK.h"
#include "Properties.h"
#include "OutputField.h"

class HelpWindow : public Fl_Double_Window
{
public:
	HelpWindow(
		int X = Props::CenterW - Props::ScrX * 0.45,
		int Y = Props::CenterH - Props::ScrY * 0.45,
		int W = Props::ScrX * 0.9,
		int H = Props::ScrY * 0.9
	);

	OutputField* MessageField;
	Fl_Button* OkBtn;

};