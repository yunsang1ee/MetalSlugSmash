#include "ysapplication.h"
#include "ysSceneManager.h"
#include "ysInputManager.h"
#include "ysTimer.h"
#include <ysResources.h>
#include <ysCollisionManager.h>


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

		CollisionManager::Init();
		SceneManager::Init();
	}

	void Application::Run()
	{
		InputManager::BeforeUpdate();
		Timer::Update();
		Update();
		LateUpdate();
		Render();
		InputManager::AfterUpdate();
	}

	void Application::Update()
	{
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		PatBlt(hBackDc, 0, 0, screen.x, screen.y, WHITENESS);

		CollisionManager::Render(hBackDc);
		SceneManager::Render(hBackDc);

		Timer::Render(hBackDc, screen);
		BitBlt(hDc, 0, 0, screen.x, screen.y, hBackDc, 0, 0, SRCCOPY);
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::Release()
	{
		SceneManager::Release();
		Resources::Release();
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