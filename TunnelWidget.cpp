#include "TunnelWidget.h"
#include <iostream>

void ClickCallback(Fl_Widget* Widget, long TunnelNumber)
{
	std::cout << "debug: " << TunnelNumber << "\n";
}

TunnelWidget::TunnelWidget(Fl_Image* Image, int X, int Y, int W, int H) : Fl_Button(X, Y, W, H)
{
	box(FL_NO_BOX);
	image(Image);

	align(
		FL_ALIGN_BOTTOM |
		FL_ALIGN_TEXT_OVER_IMAGE |
		FL_ALIGN_INSIDE |
		FL_ALIGN_IMAGE_BACKDROP
	);
	labelsize(h() / 6);
	labelcolor(FL_WHITE);
	labeltype(FL_SHADOW_LABEL);
	labelfont(FL_TIMES_BOLD_ITALIC);
	SetLabel(42);

	callback(ClickCallback, TunnelNum);
}

void TunnelWidget::SetLabel(int TunnelNumber)
{
	char buff[3];
	TunnelNum = TunnelNumber;
	_itoa_s(TunnelNumber, buff, 10);
	copy_label(buff);
}
