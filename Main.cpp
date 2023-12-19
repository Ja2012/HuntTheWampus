// License file: COPYING.WTFPL. Author: diego1812@gmail.com
#include <iostream>

#include "FLTK.h"

#include "GameWindow.h"
#include "Game.h"

int run()
{
	fl_register_images();
	Fl::visual(FL_DOUBLE | FL_INDEX);

	Game GameObj{};

	GameObj.PrapareGame();
	return Fl::run();
}

int main() 
{
	return run();
}
