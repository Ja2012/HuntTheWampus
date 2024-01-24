#pragma once

#include <array>
#include <vector>

#include "Point.h"
#include "Unit.h"


struct Cave
{
	Cave() {};
	Cave(int Number, const char* Label, Point ScreenPosition, std::array<int, 3> AdjancentCaves) : 
		Num(Number), Label(Label), Pos(ScreenPosition), AdjCaveNumbers(AdjancentCaves) {}

	int Num;
	const char* Label;
	Point Pos;
	std::array<int, 3> AdjCaveNumbers;
	std::vector<Unit> Units;
};