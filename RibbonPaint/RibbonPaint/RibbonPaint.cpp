// RibbonPaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "RibbonPaint.h"
#include <vector>
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include "DLL_Shape.h"
using namespace Gdiplus;
using namespace MyDLL;
using namespace std;
#define MAX_LOADSTRING 100

// Global Variables:cai nao
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	CoInitialize(0);
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_RIBBONPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RIBBONPAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	CoUninitialize();
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0; // CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_RIBBONPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_RIBBONPAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

vector<CShape*> shapes;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
int startX;
int startY;
int lastX;
int lastY;
bool isDrawing = false;
enum ModeShape {
	LINE,
	RECTANGLE,
	ELLIPSE
};

ModeShape mode;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		startX = x;
		startY = y;
		isDrawing = true;
	}
	break;
	case WM_MOUSEMOVE: {
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		WCHAR buffer[200];
		wsprintf(buffer, L"%d, %d", x, y);
		SetWindowText(hWnd, buffer);

		if (isDrawing) {
			lastX = x;
			lastY = y;

			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
					   break;
	case WM_LBUTTONUP: 
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);

		
		switch (mode)
		{
		case LINE: {
			CLine* line = new CLine;
			line->Create(startX, startY, lastX, lastY);
			shapes.push_back(line);
			InvalidateRect(hWnd, NULL, TRUE);
			break; 
		}
		case RECTANGLE: {
			if (GetKeyState(VK_LSHIFT)<0)
			{
				CSquare* square = new CSquare;
				square->Create(startX, startY, startX + abs(startX - x), startY + abs(startY - y));
				shapes.push_back(square);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				CRectangle* rectangle = new CRectangle;
				rectangle->Create(startX, startY, lastX, lastY);
				shapes.push_back(rectangle);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		case ELLIPSE: {
			if (GetKeyState(VK_LSHIFT)<0)
			{
				CCircle* circle = new CCircle;
				circle->Create(startX, startY, startX + abs(startX - x), startY + abs(startY - y));
				shapes.push_back(circle);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				CEllipse* ellipse = new CEllipse;
				ellipse->Create(startX, startY, lastX, lastY);
				shapes.push_back(ellipse);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}

		}	
		
		
	}
	isDrawing = false;

	InvalidateRect(hWnd, NULL, TRUE);
	break;

	case WM_CREATE:
	{
		InitializeFramework(hWnd);
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		mode = LINE;
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case ID_DRAW_LINE:
		{
			mode = LINE;
			InvalidateRect(hWnd, NULL, TRUE);
		}
			break;

		case ID_DRAW_RECTANGLE:
		{
			mode = RECTANGLE;
			InvalidateRect(hWnd, NULL, TRUE);
		}
			break;

		case ID_DRAW_ELLIPSE:
		{
			mode = ELLIPSE;
			InvalidateRect(hWnd, NULL, TRUE);
			
		}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		break;
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Graphics *graphics = new Graphics(hdc);
		for (int i = 0; i < shapes.size(); i++) {
			shapes[i]->Draw(graphics);
		}

		if (isDrawing) 
		{
			switch (mode)
			{
			case LINE: {
				CLine* line = new CLine();
				line->Create(startX, startY, lastX, lastY);
				line->Draw(graphics);
				break;
			}
			case RECTANGLE:
			{
				if (GetKeyState(VK_LSHIFT)<0)
				{
					CSquare* square = new CSquare();
					square->Create(startX, startY, lastX, lastY);
					square->Draw(graphics);
					break;
				}
				else
				{
					CRectangle* rectangle = new CRectangle();
					rectangle->Create(startX, startY, lastX, lastY);
					rectangle->Draw(graphics);
					break;
				}
			}
			break;
			case ELLIPSE:
			{
				if (GetKeyState(VK_LSHIFT)<0)

				{
					CCircle* circle = new CCircle();
					circle->Create(startX, startY, lastX, lastY);
					circle->Draw(graphics);
					break;
				}
				else
				{
					CEllipse* ellipse = new CEllipse();
					ellipse->Create(startX, startY, lastX, lastY);
					ellipse->Draw(graphics);
					break;
				}
				break;
			}
			}
		}
		delete graphics;
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		GdiplusShutdown(gdiplusToken);
		DestroyFramework();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

