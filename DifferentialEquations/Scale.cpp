#include "Scale.h"




Scale::Scale(double xStart, double yStart, double xA, double xB, double yA, double yB, RECT wndRect, TCHAR* func)
{
	this->xA = xA;
	this->xB = xB;
	this->yA = yA;
	this->yB = yB;

	this->xStart = xStart;
	this->yStart = yStart;

	_tcscpy_s(this->func, func);
	this->wndRect = wndRect;
	this->DgridX = (wndRect.right  -marginRight - margin) / 15;
	this->DgridY = (wndRect.bottom - 2 * margin) / 10;
	this->gX = (xB - xA) / ((wndRect.right  -marginRight - margin) / DgridX);
	this->gY = (yB - yA) / ((wndRect.bottom - 2 * margin) / DgridY);

	this->fX = (wndRect.right - marginRight - margin) / (xB - xA);
	this->fY = (wndRect.bottom - 2 * margin) / (yB - yA);

}


Scale::~Scale()
{
}
