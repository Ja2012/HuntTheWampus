/*
* Copyright © 2024 Eugene Grigoryev <diego1812@gmail.com>
* This work is free.You can redistribute it and /or modify it under the
* terms of the Do What The Fuck You Want To Public License, Version 2,
* as published by Sam Hocevar. See the COPYING file for more details.
*/

// FLTK manual https://www.fltk.org/doc-1.3/basics.html

#include <iostream>

#include "FLTK.h"

#include "GameWindow.h"
#include "Game.h"

int main() 
{
	fl_register_images();

	Game GameObj{};

	GameObj.PrapareGame();
	return Fl::run();
}