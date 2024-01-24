#define _USE_MATH_DEFINES
#include <math.h>
#include <tuple>

#include "CaveWidget.h"
#include "Line.h"

Line CalcSegmentOnLine(const Line TargetLine, int Offset)
{
	double LineX = TargetLine.End.X - TargetLine.Start.X;
	double LineY = TargetLine.End.Y - TargetLine.Start.Y;
	double LineLen = sqrt(pow(LineX, 2) + pow(LineY, 2));

	double AngleRad = acos(LineX / LineLen);
	double AngleRad2 = asin(LineY / LineLen);

	double SegP1Len = Offset;
	int P1X = TargetLine.Start.X + SegP1Len * cos(AngleRad);
	int P1Y = TargetLine.Start.Y + SegP1Len * sin(AngleRad2);

	double SegP2Len = LineLen - Offset;
	int P2X = TargetLine.Start.X + SegP2Len * cos(AngleRad);
	int P2Y = TargetLine.Start.Y + SegP2Len * sin(AngleRad2);

	return Line{Point{ P1X, P1Y }, Point{ P2X,P2Y }};
}

CaveWidget::CaveWidget(int X, int Y, const char* Label, 
	Point AdjCave1, Point AdjCave2, Point AdjCave3,
	int W, int H
): Fl_Box(FL_NO_BOX, X, Y, W, H, Label)
{
	color(FL_BLACK);
	labelcolor(FL_DARK_BLUE);
	labeltype(_FL_EMBOSSED_LABEL);
	labelsize(h() * 2 / 3);
	labelfont(FL_TIMES_BOLD_ITALIC);

	int Offset = w() / 2;
	Point WidgetCenter{ x() + w() / 2, y() + h() / 2 };
	
	Line1 = CalcSegmentOnLine
	(
		Line {WidgetCenter, Point { AdjCave1.X + w() / 2, AdjCave1.Y + h() / 2 }}, 
		Offset
	);
	
	Line2 = CalcSegmentOnLine
	(
		Line { WidgetCenter, Point { AdjCave2.X + w() / 2, AdjCave2.Y + h() / 2 } },
		Offset
	);
	
	Line3 = CalcSegmentOnLine(
		Line{ WidgetCenter, Point { AdjCave3.X + w() / 2, AdjCave3.Y + h() / 2 } },
		Offset
	);
}

void CaveWidget::draw()
{
	Fl_Box::draw();
	if (VisibleTunnels)
	{
		fl_line(Line1.Start.X, Line1.Start.Y, Line1.End.X, Line1.End.Y);
		fl_line(Line2.Start.X, Line2.Start.Y, Line2.End.X, Line2.End.Y);
		fl_line(Line3.Start.X, Line3.Start.Y, Line3.End.X, Line3.End.Y);
	}

}
