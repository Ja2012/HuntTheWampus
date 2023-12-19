#include <string>

#include "OutputField.h"


OutputField::OutputField(int X, int Y, int W, int H): Fl_Text_Display(X, Y, W, H)
{
	box(FL_NO_BOX);
	color(FL_BLACK);
	textsize(h() / 2);
	textcolor(FL_WHITE);
	textfont(FL_TIMES_BOLD_ITALIC);
	hide_cursor();
	wrap_mode(0, 0);
	scrollbar_width(0);
	buffer(Buffer);
	//Buffer->text("20 - 19 - 18 - 17 - 16");
	clear_visible_focus();
	selection_color(FL_BLACK);
	cursor_color(FL_BLACK);

}

void OutputField::Add(int CaveNum)
{
	std::string Str{ Buffer->text() };
	if (!Str.empty())
	{
		Str.append(" - ");
	}
	Str.append(std::to_string(CaveNum));
	Buffer->text(Str.c_str());
	CaveNumbersInPath.push_back(CaveNum);
}

void OutputField::Clear()
{
	Buffer->text("");
	CaveNumbersInPath.clear();
}

void OutputField::EraseLast()
{
	std::string Str{ Buffer->text() };
	if (Str.empty()) return;
	int Found = Str.find_last_of('-');
	if (Found != Str.npos)
	{
		Buffer->text(Str.substr(0, Found - 1).c_str());
		CaveNumbersInPath.pop_back();
	}
	else
	{
		Clear();
	}
}

