#pragma once

//³ÂÞÈ×¿6.30£ºµãÀà
class MyPoint
{
public:
	MyPoint(){x = 0;y = 0;};
	MyPoint(float x, float y) :x(x), y(y) {}
	float x;
	float y;
};

class MyBoundingBox
{
public:
	MyBoundingBox(float xmin, float xmax, float ymin, float ymax) :xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}
	MyBoundingBox() {}
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	float Height()
	{
		return ymax - ymin;
	}
	float Width()
	{
		return xmax - xmin;
	}
};

class MyGCPPair
{
public:
	MyGCPPair(){}
	MyGCPPair(MyPoint basePt, MyPoint warpPt):basePt(basePt),warpPt(warpPt),predPt(warpPt){}
	MyPoint basePt;
	MyPoint warpPt;
	MyPoint predPt;
	float GetErrX()
	{
		return predPt.x - warpPt.x;
	}
	float GetErrY()
	{
		return predPt.y - warpPt.y;
	}
	float GetDist()
	{
		return sqrt((predPt.x - warpPt.x)*(predPt.x - warpPt.x) + (predPt.y - warpPt.y)*(predPt.y - warpPt.y));
	}
};