#include "GameWindow.h"

GameWindow::GameWindow(int Width, int Height, const char* Label) : Fl_Double_Window(Width, Height, Label)
{
	color(FL_BLACK);
	size(Props::ScrRes.X, Props::ScrRes.Y);
	fullscreen();

	QuitBtn->color(FL_DARK_RED);
	QuitBtn->labelcolor(FL_WHITE);
	QuitBtn->box(FL_UP_BOX);

	HelpBtn->color(FL_DARK_GREEN);
	HelpBtn->box(FL_UP_BOX);
	HelpBtn->labelcolor(FL_WHITE);
	HelpBtn->labelsize(HelpBtn->h() * 0.9);

	ShootDiag = new ShootDialog{};

	end();
	show();
}
void GameWindow::HideOneArrow()
{
	for (ArrowWidget* Arrow : Arrows)
	{
		if (Arrow->visible())
		{
			Arrow->hide();
			return;
		}
	}
}

