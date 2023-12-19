#include "BowWidget.h"

BowWidget::BowWidget(Fl_Image* Image, int X, int Y, int W, int H): Fl_Button(X, Y, W, H)
{
	box(FL_NO_BOX);
	image(Image);
}
