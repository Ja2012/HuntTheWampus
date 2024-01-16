#pragma once
#include "Point.h"
#include "Utilities.h"
#include "Constants.h"

Point GetScreenResolution();
Point& Resize(Point&& Pnt);
int Resize(int Value, bool horizontal = true);

namespace Props
{
	// Screen
	const Point ScrRes = GetScreenResolution();

	inline const double ResizeWRatio = ScrRes.X / double(Consts::ScrX);
	inline const double ResizeHRatio = ScrRes.Y / double(Consts::ScrY);

	inline const int ScrX = Resize(Consts::ScrX);
	inline int ScrY = Resize(Consts::ScrY, false);

	inline const int CenterW = ScrX / 2;
	inline const int CenterH = ScrY / 2;
	const Point Center = Point{ CenterW, CenterH };

	// GameWindow
	const Point TunnelImgSize = Resize(Point{ Consts::TunnelImgSizeX, Consts::TunnelImgSizeY });
	const Point Tunnel1ImgPos = Resize(Point{ Consts::Tunnel1ImgPosX, Consts::Tunnel1ImgPosY });
	const Point Tunnel2ImgPos = Resize(Point{ Consts::Tunnel2ImgPosX, Consts::Tunnel2ImgPosY });
	const Point Tunnel3ImgPos = Resize(Point{ Consts::Tunnel3ImgPosX, Consts::Tunnel3ImgPosY });

	//		Map
	const Point MapImgSize = Resize(Point{ Consts::MapImgSizeX, Consts::MapImgSizeY });
	const Point MapImgPos = Resize(Point{ Consts::MapImgPosX, Consts::MapImgPosY});

	//		Cave on map
	const Point CaveWidSize = Resize(Point{ Consts::CaveWidSizeX, Consts::CaveWidSizeY});

};

