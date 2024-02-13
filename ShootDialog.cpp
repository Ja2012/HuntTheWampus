#include "ShootDialog.h"

void CallbackClickCancel(Fl_Widget* Widget)
{
	Widget->parent()->hide();
}


ShootDialog::ShootDialog(int Width, int Height) : Fl_Group(Props::SDPosX, Props::SDPosY, Width, Height)
{
	PathOut = new OutputField{ Props::SDPathOutputPosX, Props::SDPathOutputPosY,
		Props::SDPathOutputSizeX, Props::SDPathOutputSizeY, };

	EraseBtn = new Fl_Button(Props::SDEraselBtnPosX, Props::SDEraselBtnPosY,
		Props::SDEraseBtnSizeX, Props::SDEraselBtnSizeY, "@+5undo");
	EraseBtn->labelcolor(FL_WHITE);
	EraseBtn->box(FL_NO_BOX);
	end();
}
