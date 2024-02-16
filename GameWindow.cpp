#include "GameWindow.h"

GameWindow::GameWindow(int Width, int Height, const char* Label) : Fl_Double_Window(Width, Height, Label)
{
	color(FL_BLACK);
	size(Props::ScrRes.X, Props::ScrRes.Y);
	fullscreen();

	QuitBtn->labelcolor(FL_WHITE);
	QuitBtn->box(FL_NO_BOX);

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

