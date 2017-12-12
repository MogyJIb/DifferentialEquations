#pragma once

#include <Windows.h>
#include <tchar.h>

class Scale
{

public:
	Scale(double xStart, double yStart,double xA, double xB, double yA, double yB, RECT wndRect, TCHAR* func);

	RECT wndRect;
	TCHAR func[100];

	double xA;
	double xB;
	double yA;
	double yB;

	double gX;
	double gY;

	double fX;
	double fY;

	double xStart;
	double yStart;

	double DgridX;
	double DgridY;
	const double margin = 60;
	const double marginRight = 300;

	~Scale();
};
