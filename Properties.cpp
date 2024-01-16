#include "Properties.h"
#include "FLTK.h"

Point GetScreenResolution()
{
	int X, Y, W, H;
	Fl::screen_xywh(X, Y, W, H);
	return Point{ W, H };
	//RECT desktop;
	//const HWND hDesktop = GetDesktopWindow();
	//GetWindowRect(hDesktop, &desktop);
	//return ScreenResolution{ desktop.bottom, desktop.right };
}

int Resize(int Value, bool horizontal)
{
	return horizontal ? Value * Props::ResizeWRatio : Value * Props::ResizeHRatio;
}

Point& Resize(Point&& Pnt)
{
	Pnt.X *= Props::ResizeWRatio;
	Pnt.Y *= Props::ResizeHRatio;
	return Pnt;
}
