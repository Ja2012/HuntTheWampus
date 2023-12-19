// License file: COPYING.WTFPL. Author: diego1812@gmail.com
#include "InfoDialog.h"

InfoDialog::InfoDialog(int X, int Y, int W, int H ):
	Fl_Double_Window(X, Y, W, H)
{
	clear_border();
	box(FL_UP_BOX);
	color(FL_BLACK);

	int OkBtnSizeW = w() * 0.5;
	int OkBtnSizeH = h() * 0.06;
	OkBtn = new Fl_Button(w() / 2 - OkBtnSizeW / 2, h() - OkBtnSizeH - Offset, OkBtnSizeW, OkBtnSizeH);
	OkBtn->box(FL_UP_BOX);
	OkBtn->label("Ok");
	OkBtn->labelfont(FL_TIMES_ITALIC);
	OkBtn->labelsize(OkBtnSizeH / 1.5);

	int MessageFieldSizeW = w() * 0.8;
	int MessageFieldSizeH = h() * 0.3;
	int MessageTextSize = MessageFieldSizeH * 0.2;
	MessageField = new OutputField(
		w() / 2 - MessageFieldSizeW / 2, 
		h() / 2,
		MessageFieldSizeW, MessageFieldSizeH);
	MessageField->wrap_mode(OutputField::WRAP_AT_BOUNDS, 10);
	MessageField->textsize(MessageTextSize);
	MessageField->textfont(FL_TIMES_ITALIC);

	ImgHeight = MessageField->y() - Offset * 3;

	end();
	hide();
}

void InfoDialog::ShowInfo(Type Type)
{
	Fl_PNG_Image* TitleImg;
	const char* Message;


	switch (Type)
	{
	case GAMEOVER_WAMPUS:
		{
		TitleImg = GameOverImg;
		//Message = "You were eaten by a wandering Wampus.";
		Message = "Вы зашли в пещеру с Вампусом и он съел вас.";
		break;
	}
	case GAMEOVER_WAMPUS_WALK_IN_SAME_CAVE:
	{
		TitleImg = GameOverImg;
		//Message = "You were really unlucky because Wampus entered the same cave with you and ate you.";
		Message = "Вы встретили Вампуса и он съел вас.";
		break;
	}
	case GAMEOVER_WOKE_UP_WAMPUS:
	{
		TitleImg = GameOverImg;
		//Message = "Ugh, you've entered cave with Wampus, woke him up and he ate you.";
		Message = "Вы зашли в пещеру со спящим Вампусом. Он проснулся и съел вас.";
		break;
	}
	case GAMEOVER_PIT:
	{
		TitleImg = GameOverImg;
		//Message = "You fell into the abyss and died.";
		Message = "Вы упали в пропасть и разбились.";
		break;
	}
	case GAMEOVER_ARROW:
	{
		TitleImg = GameOverImg;
		//Message = "You killed yourself with your own arrow.";
		Message = "Вы убили себя собственной стрелой.";
		break;
	}
	case GAMEOVER_NO_ARROWS:
	{
		TitleImg = GameOverImg;
		//Message = "You wasted all your arrows and soon Wampus found and ate you.";
		Message = "Вы потратили все стрелы и вскоре Вампус вас нашёл.";
		break;
	}
	case BATS:
	{
		TitleImg = BatsImg;
		//Message = "They grab you and send to a random cave!";
		Message = "Летучие мыши схватили вас и перенесли в случайную пещеру!";
		break;
	}
	case YOUWIN:
	{
		TitleImg = YouWinImg;
		//Message = "You killed the Wampus! Congrats!";
		Message = "Вы попали в Вампуса и убили его. Вы победили!";
		break;
	}
	case WAMPUS_RUN:
	{
		TitleImg = WampusImg;
		//Message = "Ugh, you've entered cave with Wampus and woke up him, but he run away to neighboring cave.";
		Message = "Вы зашли в пещеру с Вампусом. Он проснулся и убежал в соседнюю пещеру.";
		break;
	}
	default: 
		return;
	}
	
	MessageField->Buffer->text(Message);

	double ImgAspectRation = double(TitleImg->w()) / TitleImg->h();
	int ImgWidth = ImgHeight * ImgAspectRation;
	ResultImgBox->size(ImgWidth, ImgHeight);
	ResultImgBox->position(w() / 2 - ImgWidth / 2, Offset);
	ResultImgBox->image(static_cast<Fl_PNG_Image*>(TitleImg->copy(ImgWidth, ImgHeight)));

	show();
	while (shown()) Fl::wait();
}
	