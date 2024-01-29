#pragma once

#include <iostream>

#include "FLTK.h"
#include "Properties.h"
#include "MapWidget.h"
#include "TunnelWidget.h"
#include "ArrowWidget.h"

class GameWindow : public Fl_Double_Window
{
public:	
	GameWindow(int Width = 300, int Height = 300, const char* Label = "Охота на Вампуса");
	Fl_Shared_Image* TunnelImg = static_cast<Fl_Shared_Image*>(Fl_Shared_Image::get(Consts::TunnelImageFileName)->copy(Props::TunnelImgSize.X, Props::TunnelImgSize.Y));
	TunnelWidget* Tunnel1 = new TunnelWidget{ TunnelImg, Props::Tunnel1ImgPos.X, Props::Tunnel1ImgPos.Y };
	TunnelWidget* Tunnel2 = new TunnelWidget{ TunnelImg, Props::Tunnel2ImgPos.X, Props::Tunnel2ImgPos.Y };
	TunnelWidget* Tunnel3 = new TunnelWidget{ TunnelImg, Props::Tunnel3ImgPos.X, Props::Tunnel3ImgPos.Y };

	Fl_Shared_Image* ArrowImg = static_cast<Fl_Shared_Image*>(Fl_Shared_Image::get(Consts::ArrowImgFileName)->copy(Props::ArrowImgSizeX, Props::ArrowImgSizeY));
	ArrowWidget* Arrow1 = new ArrowWidget{ ArrowImg, Props::ArrowImgPosX, Props::ArrowImgPosY + 0 * Props::ArrowsYDistance};
	ArrowWidget* Arrow2 = new ArrowWidget{ ArrowImg, Props::ArrowImgPosX, Props::ArrowImgPosY + 1 * Props::ArrowsYDistance};
	ArrowWidget* Arrow3 = new ArrowWidget{ ArrowImg, Props::ArrowImgPosX, Props::ArrowImgPosY + 2 * Props::ArrowsYDistance};
	ArrowWidget* Arrow4 = new ArrowWidget{ ArrowImg, Props::ArrowImgPosX, Props::ArrowImgPosY + 3 * Props::ArrowsYDistance};
	ArrowWidget* Arrow5 = new ArrowWidget{ ArrowImg, Props::ArrowImgPosX, Props::ArrowImgPosY + 4 * Props::ArrowsYDistance};

	Fl_PNG_Image* MapImg = static_cast<Fl_PNG_Image*>(Fl_PNG_Image(Consts::MapImageFileName).copy(Props::MapImgSize.X, Props::MapImgSize.Y));
	MapWidget* Map = new MapWidget(MapImg);

	Fl_Button* QuitBtn;
};