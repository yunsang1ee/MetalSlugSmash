#include "ysapplication.h"
#include "ysSceneManager.h"
#include "ysInputManager.h"
#include "ysTimer.h"


namespace ys
{
	Application::Application() : hWnd(nullptr), hDc(nullptr), hBackDc(nullptr), hBitmap(nullptr), screen{}, frameCheck{} {}

	Application::~Application()
	{
	}

	void Application::Init(HWND hWnd_, RECT screenSize)
	{
		hWnd = hWnd_;
		hDc = GetDC(hWnd_);
		hBackDc = CreateCompatibleDC(hDc);

		setScreen(screenSize);

		InputManager::Init();
		Timer::Init();
	}

	void Application::Run()
	{
		Timer::Update();
		InputManager::BeforeUpdate();
		Update();
		LateUpdate();
		Render();
		InputManager::AfterUpdate();
	}

	void Application::Update()
	{
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		PatBlt(hBackDc, 0, 0, screen.x, screen.y, WHITENESS);

		SceneManager::Render(hBackDc);

		Timer::Render(hBackDc, screen);
		BitBlt(hDc, 0, 0, screen.x, screen.y, hBackDc, 0, 0, SRCCOPY);
	}

	void Application::setScreen(RECT screenSize)
	{
		::AdjustWindowRect(&screenSize, WS_OVERLAPPEDWINDOW, FALSE);
		screen.x = screenSize.right - screenSize.left; screen.y = screenSize.bottom - screenSize.top;
		SetWindowPos(hWnd, nullptr, 0, 0, screen.x, screen.y, 0);

		
		hBitmap = CreateCompatibleBitmap(hDc, screen.x, screen.y);
		auto oldBitmap = SelectObject(hBackDc, hBitmap);
		DeleteObject(oldBitmap);
	}
}