#include "stdafx.h"
#include "DLL_Shape.h"

namespace MyDLL {
	//CShape
	CShape::CShape()
	{
	}
	CShape::~CShape()
	{
	}


	//CLine
	void CLine::Draw(Graphics* graphics)
	{
		Pen* pen = new Pen(Color(255, 0, 0, 0), 2);
		graphics->DrawLine(pen, x1, y1, x2, y2);
	}
	void CLine::Create(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
	CLine::CLine() {}
	CLine::~CLine() {}

	//CRectangle
	void CRectangle::Draw(Graphics* graphics)
	{
		int topLeft_X, topLeft_Y, bottomRight_X, bottomRight_Y;
		int width, height;
		Pen*pen = new Pen(Color(255, 0, 0, 0), 2);
		// Get topLeft and bottomRight points of Ellipse
		if (x1 <= x2)
		{
			topLeft_X = x1;
			bottomRight_X = x2;
		}
		else
		{
			topLeft_X = x2;
			bottomRight_X = x1;
		}

		if (y1 <= y2)
		{
			topLeft_Y = y1;
			bottomRight_Y = y2;
		}
		else
		{
			topLeft_Y = y2;
			bottomRight_Y = y1;
		}

		// Get widths and heights of Ellipse
		width = bottomRight_X - topLeft_X;
		height = bottomRight_Y - topLeft_Y;

		// DrawEllipse expects top left x, top left y, width and height of shape
		graphics->DrawRectangle(pen, topLeft_X, topLeft_Y, width, height);
	}
	void CRectangle::Create(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
	CRectangle::CRectangle() {}
	CRectangle::~CRectangle() {}

	//CSquare
	void CSquare::Draw(Graphics* graphics)
	{
		int vuong = min(abs(x2 - x1), abs(y2 - y1));
		Pen*pen = new Pen(Color(255, 0, 0, 0), 2);
		if (x2 <= x1)
		{

			int temp = x2;
			x2 = x1;
			x1 = temp;
			x2 = x1 + vuong;

		}
		else
		{
			x2 = x1 + vuong;
		}

		if (y2 <= y1)
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			y2 = y1 + vuong;
		}
		else
		{
			y2 = y1 + vuong;
		}
		graphics->DrawRectangle(pen, x1, y1, vuong, vuong);
	}
	void CSquare::Create(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
	CSquare::CSquare() {}
	CSquare::~CSquare() {}

	//CEllipse
	void CEllipse::Draw(Graphics *graphics)
	{
		int topLeft_X, topLeft_Y, bottomRight_X, bottomRight_Y;
		int width, height;
		Pen*pen = new Pen(Color(255, 0, 0, 0), 2);
		// Get topLeft and bottomRight points of Ellipse
		if (x1 <= x2)
		{
			topLeft_X = x1;
			bottomRight_X = x2;
		}
		else
		{
			topLeft_X = x2;
			bottomRight_X = x1;
		}

		if (y1 <= y2)
		{
			topLeft_Y = y1;
			bottomRight_Y = y2;
		}
		else
		{
			topLeft_Y = y2;
			bottomRight_Y = y1;
		}

		// Get widths and heights of Ellipse
		width = bottomRight_X - topLeft_X;
		height = bottomRight_Y - topLeft_Y;

		// DrawEllipse expects top left x, top left y, width and height of shape
		graphics->DrawEllipse(pen, topLeft_X, topLeft_Y, width, height);
	}
	void CEllipse::Create(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
	CEllipse::CEllipse() {}
	CEllipse::~CEllipse() {}

	//CCircle
	void CCircle::Draw(Graphics* graphics)
	{
		int radius = min(abs(x2 - x1), abs(y2 - y1));
		Pen*pen = new Pen(Color(255, 0, 0, 0), 2);
		if (x2 <= x1)
		{

			int temp = x2;
			x2 = x1;
			x1 = temp;
			x2 = x1 + radius;

		}
		else
		{
			x2 = x1 + radius;
		}

		if (y2 <= y1)
		{
			int temp = y2;
			y2 = y1;
			y1 = temp;
			y2 = y1 + radius;
		}
		else
		{
			y2 = y1 + radius;
		}
		graphics->DrawEllipse(pen, x1, y1, radius, radius);
	}
	void CCircle::Create(int a, int b, int c, int d)
	{
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
	}
	CCircle::CCircle() {}
	CCircle::~CCircle() {}
}