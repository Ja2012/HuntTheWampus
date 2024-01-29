#include "GameWindow.h"

GameWindow::GameWindow(int Width, int Height, const char* Label) : Fl_Double_Window(Width, Height, Label)
{
	color(FL_BLACK);
	size(Props::ScrRes.X, Props::ScrRes.Y);
	fullscreen();

	QuitBtn = new Fl_Button(Props::ExitBtnPosX, Props::ExitBtnPosY, Props::ExitBtnSizeX, Props::ExitBtnSizeY, "@+51+");

	end();
	show();
};
