#pragma once
#include "CommonInclude.h"
#include "ysGameObject.h"

namespace ys
{
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND, RECT screenSize);
		void Run();
		void Update();
		void LateUpdate();
		void Render();

		void setScreen(RECT screen);

		HDC getHDC() { return hDc; }

	private:
		HWND hWnd;
		HDC hDc;
		HDC hBackDc;
		HBITMAP hBitmap;
		POINT screen;

		float frameCheck;
	};
}