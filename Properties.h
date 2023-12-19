// License file: COPYING.WTFPL. Author: diego1812@gmail.com
#pragma once

#include <array>

#include "Point.h"
#include "Cave.h"
#include "Utilities.h"
#include "Constants.h"

Point GetScreenResolution();
Point& Resize(Point&& Pnt);
int Resize(int Value, bool horizontal = true);


namespace Props
{
	// Screen
	inline const Point ScrRes = GetScreenResolution();

	inline const double ResizeWRatio = ScrRes.X / double(Consts::ScrX);
	inline const double ResizeHRatio = ScrRes.Y / double(Consts::ScrY);

	inline const int ScrX = Resize(Consts::ScrX);
	inline const int ScrY = Resize(Consts::ScrY, false);

	inline const int CenterW = ScrX / 2;
	inline const int CenterH = ScrY / 2;
	inline const Point Center = Point{ CenterW, CenterH };

	// GameWindow
	inline const Point TunnelImgSize = Resize(Point{ Consts::TunnelImgSizeX, Consts::TunnelImgSizeY });
	inline const Point Tunnel1ImgPos = Resize(Point{ Consts::Tunnel1ImgPosX, Consts::Tunnel1ImgPosY });
	inline const Point Tunnel2ImgPos = Resize(Point{ Consts::Tunnel2ImgPosX, Consts::Tunnel2ImgPosY });
	inline const Point Tunnel3ImgPos = Resize(Point{ Consts::Tunnel3ImgPosX, Consts::Tunnel3ImgPosY });

	//		Map
	inline const Point MapImgSize = Resize(Point{ Consts::MapImgSizeX, Consts::MapImgSizeY });
	inline const Point MapImgPos = Resize(Point{ Consts::MapImgPosX, Consts::MapImgPosY});

	//		Caves on map
	inline const Point CaveWidSize = Resize(Point{ Consts::CaveWidSizeX, Consts::CaveWidSizeY});
	inline const int CaveDrawYOffset = Resize(Consts::CaveDrawYOffset, false);

	inline const std::array<Cave, 21> CavesList
	{
		Cave {0, "0", Point {0, 0}, {0,0,0}},

		Cave {1, "1", Resize(Point {939, 608}), {2,5,8}},
		Cave {2, "2", Resize(Point {1116 , 740 }), {1,3,10}},
		Cave {3, "3", Resize(Point {1049 ,962 }), {2, 4, 12}},
		Cave {4, "4", Resize(Point {831 ,961 }), {3, 5, 14}},
		Cave {5, "5", Resize(Point {763 ,742 }), {1, 4, 6}},

		Cave {6, "6", Resize(Point {822 ,762 }), {5, 7, 15}},
		Cave {7, "7", Resize(Point {868 ,698 }), {6, 8, 17}},
		Cave {8, "8", Resize(Point {939 ,676 }), {1, 7, 9}},
		Cave {9, "9", Resize(Point {1012 ,696 }), {8, 10, 18}},
		Cave {10, "10", Resize(Point {1057  ,762  }), {2, 9, 11}},

		Cave {11, "11", Resize(Point {1059   ,843   }), {10, 12, 19}},
		Cave {12, "12", Resize(Point {1013   ,908   }), {3, 11, 13}},
		Cave {13, "13", Resize(Point {939   ,931   }), {12, 14, 20}},
		Cave {14, "14", Resize(Point {865  ,909   }), {4, 13, 15}},
		Cave {15, "15", Resize(Point {822   ,843   }), {6, 14, 16}},

		Cave {16, "16", Resize(Point {881   ,822   }), {15, 17, 20}},
		Cave {17, "17", Resize(Point {904   ,749   }), {7, 16, 18}},
		Cave {18, "18", Resize(Point {977   ,748   }), {9, 17, 19}},
		Cave {19, "19", Resize(Point {998   ,823   }), {11, 18, 20}},
		Cave {20, "20", Resize(Point {938   ,867   }), {13, 16, 19}},
	};

	// Arrows
	inline const int ArrowImgSizeX = Resize(Consts::ArrowImgSizeX);
	inline const int ArrowImgSizeY = Resize(Consts::ArrowImgSizeY, false);
	inline const int ArrowImgPosX = Resize(Consts::ArrowImgPosX);
	inline const int ArrowImgPosY = Resize(Consts::ArrowImgPosY, false);

	inline const int ArrowsYDistance = Resize(Consts::ArrowsYDistance, false);

	// Exit button
	inline int ExitBtnSizeX = Resize(Consts::ExitBtnSizeX);
	inline int ExitBtnSizeY = Resize(Consts::ExitBtnSizeY, false);
	inline int ExitBtnPosX = Resize(Consts::ExitBtnPosX);
	inline int ExitBtnPosY = Resize(Consts::ExitBtnPosY, false);

	// Help button
	inline int HelpBtnSizeX = Resize(Consts::HelpBtnSizeX);
	inline int HelpBtnSizeY = Resize(Consts::HelpBtnSizeY, false);
	inline int HelpBtnPosX = Resize(Consts::HelpBtnPosX);
	inline int HelpBtnPosY = Resize(Consts::HelpBtnPosY, false);

	// Bow button
	inline int BowBtnSizeX = Resize(Consts::BowBtnSizeX);
	inline int BowBtnSizeY = Resize(Consts::BowBtnSizeY, false);
	inline int BowBtnPosX = Resize(Consts::BowBtnPosX);
	inline int BowBtnPosY = Resize(Consts::BowBtnPosY, false);

	// Shoot Dialog -----------------------------------------------------------
	inline int SDSizeX = Resize(Consts::SDSizeX);
	inline int SDSizeY = Resize(Consts::SDSizeY, false);
	inline int SDPosX = Resize(Consts::SDPosX);
	inline int SDPosY = Resize(Consts::SDPosY, false);

	//		output field
	inline  int SDPathOutputSizeX = Resize(Consts::SDPathOutputSizeX);
	inline  int SDPathOutputSizeY = Resize(Consts::SDPathOutputSizeY, false);
	inline  int SDPathOutputPosX = Resize(Consts::SDPathOutputPosX);
	inline  int SDPathOutputPosY = Resize(Consts::SDPathOutputPosY, false);

	//		erase button
	inline  int SDEraseBtnSizeX = Resize(Consts::SDEraseBtnSizeX);
	inline  int SDEraselBtnSizeY = Resize(Consts::SDEraselBtnSizeY, false);
	inline  int SDEraselBtnPosX = Resize(Consts::SDEraselBtnPosX);
	inline  int SDEraselBtnPosY = Resize(Consts::SDEraselBtnPosY, false);
	
	//		first cave button
	inline  int SDCaveBtnSizeX = Resize(Consts::SDCaveBtnSizeX);
	inline  int SDCaveBtnSizeY = Resize(Consts::SDCaveBtnSizeY, false);
	inline  int SDCaveBtnPosX = Resize(Consts::SDCaveBtnPosX);
	inline  int SDCaveBtnPosY = Resize(Consts::SDCaveBtnPosY, false);
	//		last cave button
	inline  int SDCaveLastBtnPosX = Resize(Consts::SDCaveLastBtnPosX);
	inline  int SDCaveLastBtnPosY = Resize(Consts::SDCaveLastBtnPosY, false);

	// END Shoot Dialog Properties ---------------------------------------------



};

