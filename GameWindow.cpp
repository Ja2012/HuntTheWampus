#include "GameWindow.h"

void ExitCallback(Fl_Widget *Widget) 
{ 
	if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape)
		return; // ignore Escape
	exit(0); 
}

GameWindow::GameWindow(int Width, int Height, const char* Label) : Fl_Double_Window(Width, Height, Label)
{
	color(FL_BLACK);
	size(Props::ScrRes.X, Props::ScrRes.Y);
	fullscreen();

	callback(ExitCallback);

	ExitBtn = new Fl_Button(Props::ExitBtnPosX, Props::ExitBtnPosY, Props::ExitBtnSizeX, Props::ExitBtnSizeY, "@+51+");
	ExitBtn->callback(ExitCallback);

	end();
	show();
};
