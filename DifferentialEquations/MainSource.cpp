// ����������� ���������� ��� ������ � windows
#include <Windows.h>
#include <Windowsx.h>
#include <stdlib.h>
// ���������� ��� ������ � ������� �����������
#include <tchar.h>

#include "ProcessorDE.h"
#include "Designer.h"
#include "Scale.h"
#include "ScilabScript.h"


#define INPUT_INFORM_TEXT _T("The format of inputed differential \n equation should be as y'=f(x,y).\n\n For example, if you have \n equation y'=y-x^2, you  should \n input 'y-x^2'.")
#define BUTTON_E_TITLE _T("Eyler")
#define BUTTON_RK_TITLE _T("Runge-Kutta")
#define BUTTON_SCILAB_TITLE _T("Scilab")
#define DIFFEQ_LABLE_TEXT _T("Enter differential equation here")
#define INITCOORD_LABLE_TEXT _T("Enter the initial coordinates")
#define STARTCOORDF_LABLE_TEXT _T("Y ( ")
#define ENDCOORD_LABLE_TEXT _T("Xn = ")
#define STARTCOORDS_LABLE_TEXT _T(" ) = ")

#define WUM_FIRSTAPPRBUTTONCLICK 0x0403
#define ID_EDITXA 100
#define ID_EDITXB 101
#define ID_EDITYA 102
#define ID_EDITYB 103
#define ID_EDITFUNC 104

#define ID_EDITYSTART 105
#define ID_EDITXSTART 106
#define ID_EDITXEND 106

#define ID_BUTTONE 107
#define ID_BUTTONRK 108
#define ID_BUTTONSCILAB 109

HWND hEditXa, hEditXb, hEditYa, hEditYb, hEditFunc, hEditXstart, hEditXend, hEditYstart;
HWND hButtonE, hButtonRK, hButtonScilab;

static double margin = 60, marginRight = 300;

void setStartScaleValues(Scale &scale);
void setScale(Scale &scale, RECT wndRect);
void createEdit(HWND hWndParent, HWND &hEdit, int id);

void createButton(HWND hWndParent, HWND &hButton, int id, TCHAR* title);

// �������� ������� �������
LRESULT CALLBACK WndProc(HWND,				// ���������� ���� 
	UINT,									// ����� ��������� 
	WPARAM,									// 32-��������� ����� �������� 
	LPARAM);								// �������������� ��������� ���������
											// ��� ������ ���� ����������
TCHAR WinName[] = _T("Graph");

// ������� �������
int APIENTRY _tWinMain(HINSTANCE This,		// ���������� �������� ����������
	HINSTANCE Prev,							// � ����������� �������� ������ 0
	LPTSTR cmd,								//  ��������� ������
	int mode) {								// ����� ����������� ����
											// ���������� �������� ���� ���������
	HWND hWnd;
	// ��������� ��� �������� ���������
	MSG msg;
	// ����� ����
	WNDCLASS wndcl;
	// ����������� ������ ����
	wndcl.hInstance = This;
	// ��� ������ ����
	wndcl.lpszClassName = WinName;
	// ������� ����
	wndcl.lpfnWndProc = WndProc;
	// ����� ����
	wndcl.style = CS_HREDRAW | CS_DBLCLKS ;
	// ����������� ������
	wndcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// ����������� ������
	wndcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	// ��� ����
	wndcl.lpszMenuName = NULL;
	// ��� �������������� ������ ������
	wndcl.cbClsExtra = 0;
	// ��� �������������� ������ ����
	wndcl.cbWndExtra = 0;
	// ���������� ���� ����� ������
	wndcl.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// ����������� ������ ����
	if (!RegisterClass(&wndcl))
		return 0;
	// �������� ����
	hWnd = CreateWindow(WinName,					// ��� ������ ����
		_T("Graph"),					// ��������� ���� 
		WS_OVERLAPPEDWINDOW,						// ����� ���� 
		CW_USEDEFAULT,								 // x 
		CW_USEDEFAULT,								 // y ������� ���� 
		CW_USEDEFAULT,								 // Width 
		CW_USEDEFAULT,								 // Height 
		HWND_DESKTOP,								// ���������� ������������� ���� 
		NULL,										// ��� ���� 
		This,										// ���������� ����������
		NULL);										// �������������� ���������� ��� 
													//�������� ���� 
	ShowWindow(hWnd, mode);
	// ���� ��������� ��������� 
	while (GetMessage(&msg,							// ��������� �� ���������, ��� �������� ���������
		NULL,										// ����, ��� �������� ������������� ���������
		0,											// �������� ���������� ��������� (���,���)
		0)) {
		// ������� ���������� ����� ������� ������� 
		TranslateMessage(&msg);
		// �������� ��������� ������� WndProc() 
		DispatchMessage(&msg);
	}
	return 0;
}

// ������� ������� ���������� ������������ �������� 
// � �������� ��������� �� ������� ��� ������� ���������� 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static Designer designer = Designer();
	static double xA = 0, xB = 0, yA = 0, yB = 0;
	static bool isClear=true;

	static RECT wndRect = RECT();
	static RECT rt = RECT();

	static Scale scale = Scale();
	static ProcessorDE procDE = ProcessorDE();

	// ���������� ��������� 
	switch (message) {
	

	case WM_CREATE: {
		createEdit(hWnd, hEditXa, ID_EDITXA);
		Edit_SetText(hEditXa, _T("0"));

		createEdit(hWnd, hEditXb, ID_EDITXB);
		Edit_SetText(hEditXb, _T("10"));

		createEdit(hWnd, hEditYa, ID_EDITYA);
		Edit_SetText(hEditYa, _T("0"));

		createEdit(hWnd, hEditYb, ID_EDITYB);
		Edit_SetText(hEditYb, _T("10"));

		createEdit(hWnd, hEditFunc, ID_EDITFUNC);
		Edit_SetText(hEditFunc, _T("1"));

		createEdit(hWnd, hEditXstart, ID_EDITXSTART);
		Edit_SetText(hEditXstart, _T("0"));

		createEdit(hWnd, hEditYstart, ID_EDITYSTART);
		Edit_SetText(hEditYstart, _T("0"));

		createEdit(hWnd, hEditXend, ID_EDITXEND);
		Edit_SetText(hEditXend, _T("10"));

		createButton(hWnd, hButtonE, ID_BUTTONE,BUTTON_E_TITLE);
		createButton(hWnd, hButtonRK, ID_BUTTONRK, BUTTON_RK_TITLE);
		createButton(hWnd, hButtonScilab, ID_BUTTONSCILAB, BUTTON_SCILAB_TITLE);

		break;
	}
	case WM_SIZE: {
		int xWndSize = LOWORD(lParam);
		int yWndSize = HIWORD(lParam);

		SetRect(&wndRect, 0, 0, xWndSize, yWndSize);

		static int width = 40, height = 20;

		MoveWindow(hEditXa,
			margin- height/2, yWndSize - margin+3,                  // starting x- and y-coordinates 
			width,        // width of client area 
			height,        // height of client area 
			TRUE);                 // repaint window 


		MoveWindow(hEditXb,
			xWndSize - marginRight- height / 2, yWndSize -margin + 3,                  // starting x- and y-coordinates 
			width,        // width of client area 
			height,        // height of client area 
			TRUE);                 // repaint window 

		MoveWindow(hEditYa,
			margin- width-3, yWndSize -margin- height/2,                  // starting x- and y-coordinates 
			width,        // width of client area 
			height,        // height of client area 
			TRUE);               // repaint window 

		MoveWindow(hEditYb,
			margin- width-3, margin -height/2,                  // starting x- and y-coordinates 
			width,        // width of client area 
			height,        // height of client area 
			TRUE);                  // repaint window 

		MoveWindow(hEditFunc,
			xWndSize  - 250,  120,                 // starting x- and y-coordinates 
			width+110,        // width of client area 
			height,        // height of client area 
			TRUE);                 // repaint window 

		MoveWindow(hEditXstart,
			xWndSize - 220, 170,                 // starting x- and y-coordinates 
			width-10,        // width of client area 
			height,        // height of client area 
			TRUE);

		MoveWindow(hEditYstart,
			xWndSize - 165, 170,                 // starting x- and y-coordinates 
			width-10,        // width of client area 
			height,        // height of client area 
			TRUE);

		MoveWindow(hButtonE,
			xWndSize - 270, 220,                 // starting x- and y-coordinates 
			width +70,        // width of client area 
			height+15,        // height of client area 
			TRUE);

		MoveWindow(hButtonRK,
			xWndSize - 150, 220,                 // starting x- and y-coordinates 
			width + 70,        // width of client area 
			height + 15,        // height of client area 
			TRUE);

		MoveWindow(hButtonScilab,
			xWndSize - 220, 410,                 // starting x- and y-coordinates 
			width + 90,        // width of client area 
			height + 15,        // height of client area 
			TRUE);

		MoveWindow(hEditXend,
			xWndSize - 70, 170,                 // starting x- and y-coordinates 
			width - 10,        // width of client area 
			height,        // height of client area 
			TRUE);

		break;
	}
	case WM_PAINT: {

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);


		SetRect(&rt, wndRect.right - 265, 100, wndRect.right - 10, 115);
		DrawText(hdc, DIFFEQ_LABLE_TEXT, _tcsclen(DIFFEQ_LABLE_TEXT), &rt, DT_LEFT);

		SetRect(&rt, wndRect.right - 265, 150, wndRect.right - 10, 165);
		DrawText(hdc, INITCOORD_LABLE_TEXT, _tcsclen(INITCOORD_LABLE_TEXT), &rt, DT_LEFT);

		SetRect(&rt, wndRect.right - 240, 170, wndRect.right - 220, 190);
		DrawText(hdc, STARTCOORDF_LABLE_TEXT, _tcsclen(STARTCOORDF_LABLE_TEXT), &rt, DT_LEFT);

		SetRect(&rt, wndRect.right - 190, 170, wndRect.right - 170, 190);
		DrawText(hdc, STARTCOORDS_LABLE_TEXT, _tcsclen(STARTCOORDF_LABLE_TEXT), &rt, DT_LEFT);

		SetRect(&rt, wndRect.right - 105, 170, wndRect.right - 10, 190);
		DrawText(hdc, ENDCOORD_LABLE_TEXT, _tcsclen(STARTCOORDF_LABLE_TEXT), &rt, DT_LEFT);

		SetRect(&rt, wndRect.right - 265, 280, wndRect.right - 10, 400);
		DrawText(hdc, INPUT_INFORM_TEXT, _tcsclen(INPUT_INFORM_TEXT), &rt, DT_LEFT| DT_EDITCONTROL);


		setScale(scale, wndRect);
		designer.drawCoordinateAxes(hdc, scale);
		
		try {
			designer.drawFunction(hdc, scale);
		}
		catch (int ex) {

		}


		EndPaint(hWnd, &ps);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_EDITXA:
		case ID_EDITXB:
		case ID_EDITYA:
		case ID_EDITYB:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE: {
				SetRect(&rt, margin, margin, wndRect.right - marginRight, wndRect.bottom - margin);
				InvalidateRect(hWnd, &rt, TRUE);

				SetRect(&rt, 0, margin+20, margin, wndRect.bottom - margin-20);
				InvalidateRect(hWnd, &rt, TRUE);

				SetRect(&rt, margin+30, wndRect.bottom, wndRect.right - marginRight-30, wndRect.bottom - margin);
				InvalidateRect(hWnd, &rt, TRUE);
				break;
			}
				
			}
		case ID_BUTTONE: {
			switch (HIWORD(wParam))
			{
			case BN_CLICKED: {
				SetRect(&rt, margin, margin, wndRect.right - marginRight, wndRect.bottom - margin);
				

				
				try {
					setStartScaleValues(scale);
					procDE.Eyler(scale);

					tstring yBstr = to_tstring(scale.yB);
					Edit_SetText(hEditYb, yBstr.data());
					yBstr = to_tstring(scale.yA);
					Edit_SetText(hEditYa, yBstr.data());
				}
				catch (int e) {

				}
				InvalidateRect(hWnd, &rt, TRUE);
				

				break;
			}
			}
			break;
		}
		case ID_BUTTONRK: {
			switch (HIWORD(wParam))
			{
			case BN_CLICKED: {
				SetRect(&rt, margin, margin, wndRect.right - marginRight, wndRect.bottom - margin);

				try {
					setStartScaleValues(scale);
					procDE.RungeKutta(scale);

					tstring yBstr = to_tstring(scale.yB);
					Edit_SetText(hEditYb, yBstr.data());
					yBstr = to_tstring(scale.yA);
					Edit_SetText(hEditYa, yBstr.data());
				}
				catch (int e) {

				}
				

				InvalidateRect(hWnd, &rt, TRUE);
				break;
			}
			}
			break;
		}
		case ID_BUTTONSCILAB: {
			switch (HIWORD(wParam))
			{
			case BN_CLICKED: {
				static ScilabScript scilabScript = ScilabScript();
				try{
					setStartScaleValues(scale);
				}
				catch (int e) {

				}
				tstring func = tstring(scale.func);
				tstring x0 = to_tstring(scale.xStart);
				tstring xN = to_tstring(scale.xEnd);
				tstring y0 = to_tstring(scale.yStart);

				tstring script = scilabScript.generate(func, x0, y0, xN);
				tstring dataCommand = tstring(_T("\"C:\\Program Files\\scilab-6.0.0\\bin\\WScilex.exe\" -e \""))
					.append(script.data())
					.append(_T(" \""));
				const TCHAR* ss = dataCommand.data();
				TCHAR szCmdLine[MAX_PATH];
				_tcscpy_s(szCmdLine, dataCommand.c_str());
				STARTUPINFO cif;
				ZeroMemory(&cif, sizeof(STARTUPINFO));
				PROCESS_INFORMATION pi;
				CreateProcess(NULL, szCmdLine,
					NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi);
				break;
			}

			}
			break;
		}
			
		default: return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

		// ���������� ��������� 
	case WM_DESTROY: PostQuitMessage(0);
		break;


		// ��������� ��������� �� ��������� 
	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void setStartScaleValues(Scale &scale) {
	static double xStart = 0, yStart = 0, xEnd = 0;

	TCHAR buff[100];
	Edit_GetText(hEditXstart, buff, 100);
	xStart = _ttof(buff);
	Edit_SetText(hEditXa, buff);
	buff[0] = _T('\0');

	Edit_GetText(hEditYstart, buff, 100);
	yStart = _ttof(buff);
	Edit_SetText(hEditYa, buff);
	buff[0] = _T('\0');


	Edit_GetText(hEditXend, buff, 100);
	xEnd = _ttof(buff);
	Edit_SetText(hEditXb, buff);
	buff[0] = _T('\0');


	Edit_GetText(hEditFunc, buff, 100);
	scale.setScale(xStart, xEnd, yStart, buff);

}

void setScale(Scale &scale, RECT wndRect){
	static double xA = 0, xB = 0, yA = 0, yB = 0;

	TCHAR buff[100];
	Edit_GetText(hEditXa, buff, 100);
	xA = _ttof(buff);
	buff[0] = _T('\0');

	Edit_GetText(hEditXb, buff, 100);
	xB = _ttof(buff);
	buff[0] = _T('\0');

	Edit_GetText(hEditYa, buff, 100);
	yA = _ttof(buff);
	buff[0] = _T('\0');

	Edit_GetText(hEditYb, buff, 100);
	yB = _ttof(buff);
	buff[0] = _T('\0');

	scale.setScale(xA, xB,  yA, yB, wndRect);
}

void createEdit(HWND hWndParent, HWND &hEdit, int id) {
	hEdit = CreateWindowEx(
		0, _T("EDIT"),   // predefined class 
		NULL,         // no window title 
		WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL | ES_CENTER,
		0, 0, 0, 0,   // set size in WM_SIZE message 
		hWndParent,         // parent window 
		(HMENU)id,   // edit control ID 
		(HINSTANCE)GetWindowLong(hWndParent, GWL_HINSTANCE),
		NULL);        // pointer not needed 
}

void createButton(HWND hWndParent, HWND &hButton, int id, TCHAR* title) {
	hButton = CreateWindowEx(
		0, _T("BUTTON"),   // predefined class 
		title,         // no window title 
		WS_CHILD | WS_VISIBLE | WS_BORDER |
		BS_DEFPUSHBUTTON,
		0, 0, 0, 0,   // set size in WM_SIZE message 
		hWndParent,         // parent window 
		(HMENU)id,   // edit control ID 
		(HINSTANCE)GetWindowLong(hWndParent, GWL_HINSTANCE),
		NULL);
}

