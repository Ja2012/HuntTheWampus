#include "ShootDialog.h"

void CallbackClickCancel(Fl_Widget* Widget)
{
	Widget->parent()->hide();
}


ShootDialog::ShootDialog(int Width, int Height) : Fl_Group(Props::SDPosX, Props::SDPosY, Width, Height)
{
	PathOut = new Fl_Text_Display{ Props::SDPathOutputPosX, Props::SDPathOutputPosY,
		Props::SDPathOutputSizeX, Props::SDPathOutputSizeY, };
	PathOut->box(FL_NO_BOX);
	PathOut->color(FL_BLACK);
	PathOut->textsize(int(Props::SDPathOutputSizeY) / 2);
	PathOut->textcolor(FL_WHITE);
	PathOut->textfont(FL_TIMES_BOLD_ITALIC);
	PathOut->hide_cursor();
	PathOut->wrap_mode(0, 0);
	PathOut->scrollbar_width(0);
	PathOut->buffer(PathOutBuffer);
	PathOutBuffer->text("20 - 19 - 18 - 17 - 16");
	PathOut->clear_visible_focus();
	PathOut->selection_color(FL_BLACK);
	PathOut->cursor_color(FL_BLACK);

	EraseBtn = new Fl_Button(Props::SDEraselBtnPosX, Props::SDEraselBtnPosY,
		Props::SDEraseBtnSizeX, Props::SDEraselBtnSizeY, "@+5undo");
	EraseBtn->labelcolor(FL_WHITE);
	EraseBtn->box(FL_NO_BOX);
	end();
}
