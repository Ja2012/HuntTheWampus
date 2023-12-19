#pragma once

struct Point
{
	int X{};
	int Y{};
	Point() {};
	Point(int X, int Y) : X(X), Y(Y) {};
	Point& operator+=(Point Point) { X += Point.Y; Y += Point.Y; return *this; }
	Point& operator-=(Point Point) { X -= Point.Y; Y -= Point.Y; return *this; }
};
inline bool operator==(Point A, Point B) { return A.X == B.X && A.Y == B.Y; }
inline bool operator!=(Point A, Point B) { return !(A == B); }

