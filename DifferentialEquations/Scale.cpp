#include "Scale.h"



Scale::Scale()
{
}


void Scale::setScale(double xA, double xB, double yA, double yB,  RECT wndRect)
{

	//rect of the grid window
	this->xA = xA;
	this->xB = xB;
	this->yA = yA;
	this->yB = yB;

	//rect of the main window
	this->wndRect = wndRect;


	//grid coeffitient
	this->DgridX = (wndRect.right  -marginRight - margin) / 15;
	this->DgridY = (wndRect.bottom - 2 * margin) / 10;

	//grid coeffitient
	this->gX = (xB - xA) / ((wndRect.right  -marginRight - margin) / DgridX);
	this->gY = (yB - yA) / ((wndRect.bottom - 2 * margin) / DgridY);

	//function coeffitient
	this->fX = (wndRect.right - marginRight - margin) / (xB - xA);
	this->fY = (wndRect.bottom - 2 * margin) / (yB - yA);
}

void Scale::setScale(double xStart, double xEnd, double yStart, TCHAR * func)
{
	//interval to solve differential equation
	this->xStart = xStart;
	this->xEnd = xEnd;
	this->yStart = yStart;


	//function of differential equation
	_tcscpy_s(this->func, func);
}


Scale::~Scale()
{
}
