#include <string>

#include "ShootDialog.h"

void CallbackClickCancel(Fl_Widget* Widget)
{
	Widget->parent()->hide();
}


ShootDialog::ShootDialog(int Width, int Height) : Fl_Group(Props::SDPosX, Props::SDPosY, Width, Height)
{
	PathOut = new OutputField{ Props::SDPathOutputPosX, Props::SDPathOutputPosY,
		Props::SDPathOutputSizeX, Props::SDPathOutputSizeY, };

	EraseBtn = new Fl_Button(Props::SDEraselBtnPosX, Props::SDEraselBtnPosY,
		Props::SDEraseBtnSizeX, Props::SDEraselBtnSizeY, "@+5undo");
	EraseBtn->labelcolor(FL_WHITE);
	EraseBtn->box(FL_NO_BOX);

	// calculate cave number buttons for net 5 x 4 = 20 (left to right, up to down)
	int XDistanceBetweenCaveNumbers = (Props::SDCaveLastBtnPosX - Props::SDCaveBtnPosX)/4;
	int YDistanceBetweenCaveNumbers = (Props::SDCaveLastBtnPosY - Props::SDCaveBtnPosY)/3;

	int CaveNum{ 1 };
	for (int Row = 1; Row < 5; ++Row)
	{
		for (int Col = 1; Col < 6; ++Col)
		{
			CaveNumberButtons[CaveNum - 1] = new CaveNumberWidget
			{ 
				CaveNum,
				Props::SDCaveBtnPosX + (Col - 1) * XDistanceBetweenCaveNumbers,
				Props::SDCaveBtnPosY + (Row - 1) * YDistanceBetweenCaveNumbers,
				Props::SDCaveBtnSizeX,
				Props::SDCaveBtnSizeY,
			};
			CaveNumberButtons[CaveNum - 1]->copy_label(std::to_string(CaveNum).c_str());
			++CaveNum;
		}
	}
	end();
}

void ShootDialog::ShowCaveNumbers(std::vector<int> Numbers)
{
	for (CaveNumberWidget* Widget : CaveNumberButtons)
	{
		if (std::find(Numbers.begin(), Numbers.end(), Widget->Number) != Numbers.end())
		{
			Widget->show();
		}
		else
		{
			Widget->hide();
		}
	}
}
