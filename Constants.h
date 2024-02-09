#pragma once

// Default resolution 1920x1080. 
// Means game mainly for 16:9 aspect ratio, otherwize (16:10, 21:9) will be kind of creepy after rescale.
// So TODO: make work for different aspect ratios 

namespace Consts
{
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

	inline constexpr int ArrowImgSizeX{ 228 };
	inline constexpr int ArrowImgSizeY{ 69 };

	inline constexpr int ArrowImgPosX{ 26 };
	inline constexpr int ArrowImgPosY{ 593 };

	inline constexpr int ArrowsYDistance{ 99 };

	// Exit button
	inline constexpr int ExitBtnSizeX{ 50 };
	inline constexpr int ExitBtnSizeY{ 50 };
	inline constexpr int ExitBtnPosX{ 1860 };
	inline constexpr int ExitBtnPosY{ 10 };

	// Bow button
	inline const char* BowImgFileName{ "bow.png" };

	inline constexpr int BowBtnSizeX{ 101 };
	inline constexpr int BowBtnSizeY{ 450 };
	inline constexpr int BowBtnPosX{ 560 };
	inline constexpr int BowBtnPosY{ 590 };

	// Shoot Dialog -----------------------------------------------------------
	inline constexpr int SDSizeX{ 550 };
	inline constexpr int SDSizeY{ 600 };
	inline constexpr int SDPosX{ 1290 };
	inline constexpr int SDPosY{ 530 };

	inline constexpr int SDPathOutputSizeX{ 350 };
	inline constexpr int SDPathOutputSizeY{ 50 };
	inline constexpr int SDPathOutputPosX{ 1340 };
	inline constexpr int SDPathOutputPosY{ 570 };

	inline constexpr int SDEraseBtnSizeX{ 50 };
	inline constexpr int SDEraselBtnSizeY{ 50 };
	inline constexpr int SDEraselBtnPosX{ 1290 };
	inline constexpr int SDEraselBtnPosY{ 570 };

	inline constexpr int SDCancelBtnSizeX{ 50 };
	inline constexpr int SDCancelBtnSizeY{ 50 };
	inline constexpr int SDCancelBtnPosX{ 1780 };
	inline constexpr int SDCancelBtnPosY{ 540 };

	inline constexpr int SDCaveBtnSizeX{ 50 };
	inline constexpr int SDCaveBtnSizeY{ 50 };
	inline constexpr int SDCaveBtnPosX{ 1340 };
	inline constexpr int SDCaveBtnPosY{ 650 };

	inline constexpr int SDFireBtnSizeX{ 205 };
	inline constexpr int SDFireBtnSizeY{ 50 };
	inline constexpr int SDFireBtnPosX{ 1462 };
	inline constexpr int SDFireBtntPosY{ 1009};

	// END Shoot Dialog Constants ---------------------------------------------

}
