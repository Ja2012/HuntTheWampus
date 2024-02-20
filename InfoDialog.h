#pragma once
#include "FLTK.h"
#include "Properties.h"
#include "OutputField.h"

//class InfoDialog : public Fl_Box
class InfoDialog : public Fl_Double_Window
{
public:
	enum Type {
		GAMEOVER_WAMPUS,
		GAMEOVER_WAMPUS_WALK_IN_SAME_CAVE,
		GAMEOVER_PIT,
		GAMEOVER_ARROW,
		GAMEOVER_NO_ARROWS,
		BATS, 
		YOUWIN};
	InfoDialog(
		int X = Props::CenterW - Props::ScrX * 0.45,
		int Y = Props::CenterH - Props::ScrY * 0.30,
		int W = Props::ScrX * 0.9, 
		int H = Props::ScrY * 0.6);

		int Offset = 60;		

		Fl_Box* ResultImgBox = new Fl_Box(0, 0, 0, 0);
		int ImgHeight;
		Fl_PNG_Image* GameOverImg = new Fl_PNG_Image{ Consts::GameOverImgFileName };
		Fl_PNG_Image* YouWinImg = new Fl_PNG_Image{ Consts::YouWinImgFileName };
		Fl_PNG_Image* BatsImg = new Fl_PNG_Image{ Consts::BatsImgFileName };

		OutputField* MessageField;

		Fl_Button* OkBtn;

		void ShowInfo(Type);

};