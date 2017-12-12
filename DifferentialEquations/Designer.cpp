

#include "Designer.h"

using namespace std;

Designer::Designer()
{

}

void Designer::drawCoordinateAxes(HDC hdc, Scale scale)
{
	RECT wndRect = scale.wndRect;
	double kX = scale.DgridX, kY = scale.DgridY;
	double dX = scale.gX;
	double dY = scale.gY;
	double margin = scale.margin;

	double c = 5;


	MoveToEx(hdc, margin, margin, NULL);
	LineTo(hdc, margin, wndRect.bottom - margin);

	MoveToEx(hdc, margin, wndRect.bottom - margin, NULL);
	LineTo(hdc, wndRect.right - scale.marginRight, wndRect.bottom - margin);

	MoveToEx(hdc, margin, margin, NULL);
	LineTo(hdc, wndRect.right - scale.marginRight, margin);

	MoveToEx(hdc, wndRect.right - scale.marginRight,  margin, NULL);
	LineTo(hdc, wndRect.right - scale.marginRight, wndRect.bottom - margin);

	static RECT rt = RECT();
	static TCHAR index[100];

	double i = wndRect.bottom - margin-kY;
	double j = scale.yA+dY;
	for (; i > margin+kY/2; i -= kY, j += dY) {
		MoveToEx(hdc, margin, i, NULL);
		LineTo(hdc, wndRect.right - scale.marginRight, i);

		SetRect(&rt, margin - 45, i - 7, margin - 5, i + 7);
		_tcscpy_s(index, _T("00000000000"));
		_stprintf_s(index, _T("%.1f"), j);
		DrawText(hdc, index, _tcsclen(index), &rt, DT_RIGHT);
		
	}

	i = margin + kX;
	j = scale.xA+dX;
	for (; i < wndRect.right - scale.marginRight-kX/2; i += kX, j += dX) {
		MoveToEx(hdc, i, wndRect.bottom - margin, NULL);
		LineTo(hdc, i, margin);

		SetRect(&rt, i - 20, wndRect.bottom - margin + 5, i + 20, wndRect.bottom - margin + 25);
		_tcscpy_s(index, _T("00000000000"));
		_stprintf_s(index, _T("%.1f"), j);
		DrawText(hdc, index, _tcsclen(index), &rt, DT_RIGHT);
	}
	

}

void Designer::drawFunctionE(HDC hdc, Scale scale) {

	ProcessorRpn processorRpn = ProcessorRpn(scale.func);

	double xA = scale.xStart, xB = scale.xB,
		yA = scale.yStart, 
		h = (xB - xA) /500;

	double yk1 = yA, yk = yA+ h*processorRpn.function(xA, yA),  xk = xA+h,xk1= xk;


	for (; xk < xB;) {
				
		yk1 = yk+ h*processorRpn.function( xk, yk);
		xk1 += h;

		MoveToEx(hdc, getXcoord(xk, scale), getYcoord(yk, scale), NULL);
		LineTo(hdc, getXcoord(xk1, scale), getYcoord(yk1, scale));

		yk = yk1;
		xk = xk1;
		
	}

}

void Designer::drawFunctionRK(HDC hdc, Scale scale) {

	ProcessorRpn processorRpn = ProcessorRpn(scale.func);

	double xA = scale.xStart, xB = scale.xB,yA = scale.yStart,
		h = (xB - xA) / 1000;

	double k1 = h*processorRpn.function(xA, yA),
		k2 = h*processorRpn.function(xA+h/2, yA+k1/2),
		k3 = h*processorRpn.function(xA + h , yA + 2*k2-k1);
	double yk1 = yA, yk = yA, xk = xA, xk1 = xk;
	
	
	for (; xk < xB;) {

		yk1 = yk + (k1 + 4 * k2 + k3) / 6;
		k1 = h*processorRpn.function(xk, yk);
		k2 = h*processorRpn.function(xk + h / 2, xk + k1 / 2);
		k3 = h*processorRpn.function(xk + h, xk + 2 * k2 - k1);
		xk1 += h;

		MoveToEx(hdc, getXcoord(xk, scale), getYcoord(yk, scale), NULL);
		LineTo(hdc, getXcoord(xk1, scale), getYcoord(yk1, scale));

		yk = yk1;
		xk = xk1;

	}

}





int Designer::getXcoord(double xVal, Scale scale) {
	return (xVal - scale.xA)*scale.fX + scale.margin;
}
int Designer::getYcoord(double yVal, Scale scale) {
	double res = scale.wndRect.bottom - ((yVal - scale.yA)*scale.fY + scale.margin);
	res = res < scale.margin ? scale.margin : res;
	res = res > scale.wndRect.bottom - scale.margin ? scale.wndRect.bottom - scale.margin : res;
	return res;
}

Designer::~Designer()
{
}
