#pragma once

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
	
	//		Caves on Map. Check Properties for positions
	inline constexpr int CaveDrawYOffset{ 0 };

	// Arrows
	inline const char* ArrowImgFileName{ "arrow.png" };

	inline constexpr int ArrowImgSizeX{ 320 };
	inline constexpr int ArrowImgSizeY{ 98 };

	inline constexpr int ArrowImgPosX{ 350 };
	inline constexpr int ArrowImgPosY{ 530 };

	inline constexpr int ArrowsYDistance{ 108 };

	// Exit button
	inline constexpr int ExitBtnSizeX{ 50 };
	inline constexpr int ExitBtnSizeY{ 50 };
	inline constexpr int ExitBtnPosX{ 1860 };
	inline constexpr int ExitBtnPosY{ 10 };


}
