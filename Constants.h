#pragma once

#include <array>
#include <tuple>

namespace Consts
{
	// Default resolution 1920x1080. 
	// Means game mainly for 16:9 aspect ratio, otherwize (16:10, 21:9) will be kind of creepy after rescale.
	// So TODO: make work for different aspect ratios 
	inline constexpr int ScrX{ 1920 };
	inline constexpr int ScrY{ 1080 };	

	// Tunnels
	inline const char* TunnelImageFileName{ "Underground_tunnel3.png" };

	inline constexpr int TunnelImgSizeX{ 500 };
	inline constexpr int TunnelImgSizeY{ 500 };

	inline constexpr int Tunnel1ImgPosX{ 105 };
	inline constexpr int Tunnel1ImgPosY{ 30 };

	inline constexpr int Tunnel2ImgPosX{ 710 };
	inline constexpr int Tunnel2ImgPosY{ 30 };

	inline constexpr int Tunnel3ImgPosX{ 1315 };
	inline constexpr int Tunnel3ImgPosY{ 30 };

	// Map
	inline const char* MapImageFileName{ "map2.png" };

	inline constexpr int MapImgSizeX{ 550 };
	inline constexpr int MapImgSizeY{ 550 };

	inline constexpr int MapImgPosX{ 685 };
	inline constexpr int MapImgPosY{ 530 };

	//		Cave Widget
	inline constexpr int CaveWidSizeX{ 40 };
	inline constexpr int CaveWidSizeY{ 40 };
	
	//		Caves on Map
	inline constexpr int CaveDrawYOffset{ 0 };
	inline constexpr std::array<std::tuple<const char*, int, int>, 21> CaveWidgetPoss{{
	{"0",0,0},
	{"1",253,78}, {"2",431,210}, {"3",364,432}, {"4",146,431}, {"5",78,212},
	{"6",137,232}, {"7",183,168}, {"8",253,146}, {"9",327,166}, {"10",372,232},
	{"11",374,313}, {"12",328,378}, {"13",253,402}, {"14",180,379}, {"15",137,313},
	{"16",196,292}, {"17",219,219}, {"18",292,218}, {"19",313,293}, {"20",253,337},
} };

}
