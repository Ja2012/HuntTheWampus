#include "CaveNumberWidget.h"

CaveNumberWidget::CaveNumberWidget(int Number, int X, int Y, int W, int H) :
	Number(Number), Fl_Button(X, Y, W, H)
{
	labelcolor(FL_WHITE);
	box(FL_NO_BOX);
	//box(FL_BORDER_FRAME);
	labelsize(h() / 1.5);
	labelfont(FL_TIMES_BOLD_ITALIC);
	hide();
}
