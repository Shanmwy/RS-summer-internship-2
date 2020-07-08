#pragma once
#include <vector>

//陈奕卓6.30：点类
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

class MyValueColorMap
{
public:
	MyValueColorMap(){}
	MyValueColorMap(double minValue, RGBQUAD color):minValue(minValue),color(color){}
	//minValue指示这一个灰度级的最小值，最大值存在下一个ValueColorMap里
	double minValue;
	RGBQUAD color;
};

class MyColorStyle
{
public:
	MyColorStyle(CString name):name(name){}
	CString name;
	//默认最小值是0，最大值是256
	std::vector<MyValueColorMap> valueColorMaps;
	RGBQUAD GetColor(double value, double minValue, double maxValue)
	{
		int size = valueColorMaps.size();
		value = valueColorMaps[0].minValue + (valueColorMaps[size-1].minValue - valueColorMaps[0].minValue) * (value - minValue) / (maxValue - minValue);
		
		for (int i = 1; i < size; i++)
		{
			if (value <= valueColorMaps[i].minValue)
			{
				//线性插值出颜色
				RGBQUAD lower = valueColorMaps[i - 1].color;
				RGBQUAD upper = valueColorMaps[i].color;
				double factor = (value - valueColorMaps[i - 1].minValue) / (valueColorMaps[i].minValue - valueColorMaps[i - 1].minValue);
				RGBQUAD res;
				res.rgbBlue = (byte)((double)lower.rgbBlue + factor * ((double)upper.rgbBlue - (double)lower.rgbBlue));
				res.rgbGreen = (byte)((double)lower.rgbGreen + factor * ((double)upper.rgbGreen - (double)lower.rgbGreen));
				res.rgbRed = (byte)((double)lower.rgbRed + factor * ((double)upper.rgbRed - (double)lower.rgbRed));
				return res;
			}
		}
	}
};