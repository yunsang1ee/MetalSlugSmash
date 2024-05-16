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

		void Run();

		void Init(HWND, RECT screenSize);
		void Update();
		void LateUpdate();
		void Render();
		void Destroy();
		void Release();

		void setScreen(RECT screen);
		void setMousePosition(const Vector2& posotion) { mousePosition = posotion; }

		HWND getHWND() { return hWnd; }
		HDC getHDC() { return hDc; }
		POINT getScreen() { return screen; }
		math::Vector2 getmousePosition() { return mousePosition; }

	private:
		HWND hWnd;
		HDC hDc;
		HDC hBackDc;
		HBITMAP hBitmap;
		POINT screen;
		Vector2 mousePosition;

		float frameCheck;
	};
}