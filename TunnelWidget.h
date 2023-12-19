#pragma once

#include "FLTK.h"
#include "Properties.h"

class TunnelWidget : public Fl_Button
{
public:
	TunnelWidget(Fl_Image* Image, int X, int Y, int W = Props::TunnelImgSize.X, int H = Props::TunnelImgSize.Y);
	void SetLabel(int TunnelNumber);
	int* TunnelNum = new int(0);
private:
};
