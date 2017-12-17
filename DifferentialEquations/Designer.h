#pragma once




#include <tchar.h>
#include <stdio.h>
#include "Scale.h"
#include <cmath>

class Designer
{
private:
	double getXcoord(double xVal, Scale scale);
	double getYcoord(double yVal, Scale scale);
	HPEN hpen = (HPEN)GetStockObject(BLACK_PEN);
public:
	Designer();

	void drawCoordinateAxes(HDC hdc, Scale scale);
	void drawFunction(HDC hdc, Scale scale);

	~Designer();
};

