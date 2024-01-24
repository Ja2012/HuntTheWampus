#include "MapWidget.h"
#include "Cave.h"

MapWidget::MapWidget(Fl_Image* Image, int X, int Y, int W, int H) : Fl_Box(X, Y, W, H)
{
	image(Image);

	CaveWidgets.push_back(nullptr);
	for (int i = 1; i < Props::CavesList.size(); ++i)
	//for (int i = 1; i < 6; ++i)
	{
		Cave Cave = Props::CavesList[i];
		CaveWidgets.push_back(new CaveWidget(
			Cave.Pos.X,
			Cave.Pos.Y,
			Cave.Label,
			Props::CavesList[Cave.AdjCaveNumbers[0]].Pos,
			Props::CavesList[Cave.AdjCaveNumbers[1]].Pos,
			Props::CavesList[Cave.AdjCaveNumbers[2]].Pos
			)
		);
	}
}
