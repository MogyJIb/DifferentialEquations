#pragma once

#include <Windows.h>
#include <tchar.h>

class Scale
{

public:
	Scale();

	void setScale(double xA, double xB, double yA, double yB, RECT wndRect);
	void setScale(double xStart,double xEnd,double yStart, TCHAR* func);

	RECT wndRect;
	TCHAR func[100];


	const int count = 500;
	double res[1000];

	double xA;
	double xB;
	double yA;
	double yB;

	double gX;
	double gY;

	double fX;
	double fY;

	double xStart;
	double xEnd;
	double yStart;
	double yEnd;

	double DgridX;
	double DgridY;
	const double margin = 60;
	const double marginRight = 300;

	~Scale();
};
