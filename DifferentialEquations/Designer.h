#pragma once


#include "ProcessorRpn.h"

#include "Scale.h"
#include <cmath>

class Designer
{
private:
	int getXcoord(double xVal, Scale scale);
	int getYcoord(double yVal, Scale scale);
public:
	Designer();

	void drawCoordinateAxes(HDC hdc, Scale scale);
	void drawFunctionE(HDC hdc, Scale scale);
	void drawFunctionRK(HDC hdc, Scale scale);

	~Designer();
};

