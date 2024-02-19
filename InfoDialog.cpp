#include "InfoDialog.h"

InfoDialog::InfoDialog(int X, int Y, int W, int H ):
	Fl_Double_Window(X, Y, W, H)
{
	clear_border();
	box(FL_UP_BOX);
	color(FL_BLACK);
	//color(0xb0841f00);

	int OkBtnSizeW = w() / 15;
	int OkBtnSizeH = h() / 15;
	OkBtn = new Fl_Button(w() / 2 - OkBtnSizeW / 2, h() - OkBtnSizeH - 10, OkBtnSizeW, OkBtnSizeH);
	OkBtn->box(FL_UP_BOX);
	OkBtn->label("Ok");
	//OkBtn->labelfont(FL_TIMES_BOLD_ITALIC);
	OkBtn->labelsize(OkBtnSizeH / 1.5);

	end();
	hide();
}
