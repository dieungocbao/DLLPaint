#pragma once
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
#ifdef SHAPEDLL_EXPORTS
#define SHAPEDLL_API __declspec(dllexport) 
#else
#define SHAPEDLL_API __declspec(dllimport) 
#endif
namespace MyDLL {
	class CShape
	{
	protected:
		int x1, y1, x2, y2;
	public:
		virtual SHAPEDLL_API void Draw(Graphics* graphics) = 0;
		virtual SHAPEDLL_API void Create(int a, int b, int c, int d) = 0;
		SHAPEDLL_API CShape();
		SHAPEDLL_API ~CShape();
	};

	class CLine : public CShape
	{
	private:
	public:
		void SHAPEDLL_API Draw(Graphics* graphics);
		void SHAPEDLL_API Create(int a, int b, int c, int d);
		SHAPEDLL_API CLine();
		SHAPEDLL_API ~CLine();
	};

	class CRectangle : public CShape
	{
	private:
	public:
		void SHAPEDLL_API Draw(Graphics* graphics);
		void SHAPEDLL_API Create(int a, int b, int c, int d);
		SHAPEDLL_API CRectangle();
		SHAPEDLL_API ~CRectangle();
	};

	class CSquare : public CShape
	{
	private:
	public:
		void SHAPEDLL_API Draw(Graphics* graphics);
		void SHAPEDLL_API Create(int a, int b, int c, int d);
		SHAPEDLL_API CSquare();
		SHAPEDLL_API ~CSquare();
	};

	class CEllipse : public CShape
	{
	private:
	public:
		void SHAPEDLL_API Draw(Graphics* graphics);
		void SHAPEDLL_API Create(int a, int b, int c, int d);
		SHAPEDLL_API CEllipse();
		SHAPEDLL_API ~CEllipse();
	};

	class CCircle : public CShape
	{
	private:
	public:
		void SHAPEDLL_API Draw(Graphics* graphics);
		void SHAPEDLL_API Create(int a, int b, int c, int d);
		SHAPEDLL_API CCircle();
		SHAPEDLL_API ~CCircle();
	};
}