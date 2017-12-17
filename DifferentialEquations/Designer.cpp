


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


	HPEN hpenDASH = CreatePen(PS_DASH, 0.1, RGB(0, 0, 0));
	SelectObject(hdc, hpenDASH);

	static RECT rt = RECT();
	static TCHAR index[100];

	double i = wndRect.bottom - margin - kY;
	double j = scale.yA + dY;
	for (; i > margin + kY / 2; i -= kY, j += dY) {
		MoveToEx(hdc, margin, i, NULL);
		LineTo(hdc, wndRect.right - scale.marginRight, i);

		SetRect(&rt, margin - 45, i - 7, margin - 5, i + 7);
		_tcscpy_s(index, _T("00000000000"));
		_stprintf_s(index, _T("%.1f"), j);
		DrawText(hdc, index, _tcsclen(index), &rt, DT_RIGHT);

	}

	i = margin + kX;
	j = scale.xA + dX;
	for (; i < wndRect.right - scale.marginRight - kX / 2; i += kX, j += dX) {
		MoveToEx(hdc, i, wndRect.bottom - margin, NULL);
		LineTo(hdc, i, margin);

		SetRect(&rt, i - 20, wndRect.bottom - margin + 5, i + 20, wndRect.bottom - margin + 25);
		_tcscpy_s(index, _T("00000000000"));
		_stprintf_s(index, _T("%.1f"), j);
		DrawText(hdc, index, _tcsclen(index), &rt, DT_RIGHT);
	}


	SelectObject(hdc, hpen);
	DeleteObject(hpenDASH);
	hpenDASH = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hpenDASH);

	MoveToEx(hdc, margin, margin, NULL);
	LineTo(hdc, margin, wndRect.bottom - margin);

	MoveToEx(hdc, margin, wndRect.bottom - margin, NULL);
	LineTo(hdc, wndRect.right - scale.marginRight, wndRect.bottom - margin);

	MoveToEx(hdc, margin, margin, NULL);
	LineTo(hdc, wndRect.right - scale.marginRight, margin);

	MoveToEx(hdc, wndRect.right - scale.marginRight, margin, NULL);
	LineTo(hdc, wndRect.right - scale.marginRight, wndRect.bottom - margin);



	i = wndRect.bottom - margin - kY;
	for (; i > margin + kY / 2; i -= kY) {
		MoveToEx(hdc, margin - 5, i, NULL);
		LineTo(hdc, margin + 5, i);
	}

	i = margin + kX;
	for (; i < wndRect.right - scale.marginRight - kX / 2; i += kX) {
		MoveToEx(hdc, i, wndRect.bottom - margin + 5, NULL);
		LineTo(hdc, i, wndRect.bottom - margin - 5);
	}

	SelectObject(hdc, hpen);
	DeleteObject(hpenDASH);
}



double Designer::getXcoord(double xVal, Scale scale) {
	return (xVal - scale.xA)*scale.fX + scale.margin;
}
double Designer::getYcoord(double yVal, Scale scale) {
	return  scale.wndRect.bottom - ((yVal - scale.yA)*scale.fY + scale.margin);
}



void Designer::drawFunction(HDC hdc, Scale scale)
{
	HPEN hpenSolid = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	SelectObject(hdc, hpenSolid);

	for (int i = 0; i < 2 * scale.count - 3; i += 2) {
		
		MoveToEx(hdc, getXcoord(scale.res[i], scale), getYcoord(scale.res[i + 1], scale), NULL);
		LineTo(hdc, getXcoord(scale.res[i + 2], scale), getYcoord(scale.res[i + 3], scale));
		
	}

	SelectObject(hdc, hpen);
	DeleteObject(hpenSolid);
}

Designer::~Designer()
{
}
