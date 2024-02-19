#pragma once
#include "FLTK.h"
#include "Properties.h"
class InfoDialog : public Fl_Double_Window
{
public:
	InfoDialog(
		int X = Props::CenterW - Props::ScrX * 0.35,
		int Y = Props::CenterH - Props::ScrY * 0.35,
		int W = Props::ScrX * 0.7, 
		int H = Props::ScrY * 0.7);
		Fl_Button* OkBtn;
	
		Fl_PNG_Image* MapImg = static_cast<Fl_PNG_Image*>(Fl_PNG_Image(Consts::MapImageFileName).copy(Props::MapImgSize.X, Props::MapImgSize.Y));
		MapWidget* Map = new MapWidget(MapImg);

};