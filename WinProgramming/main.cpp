#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#include "framework.h"

#include "..\\MyEngine_source\\YSapplication.h"
#include "..\\MyEngine_source\\ysInputManager.h"
#include "..\\MyEngine\\ysLoadResources.h"
#include "..\\MyEngine\\LoadScene.h"
#pragma comment(lib, "..\\x64\\Debug\\MyEngine.lib")


ys::Application app;

HINSTANCE g_hInst;
ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"METAL SLUG SMASH";

LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX NewWndClass(UINT, WNDPROC, HINSTANCE, HICON,
	HCURSOR, HBRUSH, LPCWSTR, LPCWSTR, HICON);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(506);
	HWND hWnd;
	MSG msg;
	g_hInst = hInstance;

	RECT windowRect{ 0, 0, 4 * 300, 3 * 300 };

	WNDCLASSEX WndClass;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WinProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	::RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW ,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL);

		
	::ShowWindow(hWnd, nShowCmd);
	::UpdateWindow(hWnd);

	Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);

	ys::LoadResources();
	ys::LoadScenes();

	app.Init(hWnd, windowRect);

	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {//event
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				break;
		}
		//game logic update
		app.Run();
	}

	Gdiplus::GdiplusShutdown(gpToken);
	app.Release();
	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	static int x{}, y{};

	std::wstring line;

	switch (Msg) {//InputManager는 singleton으로 해보고 게임 로직 자체는 Component패턴으로 가보자
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
		RECT windowRect;
		GetClientRect(hWnd, &windowRect);
		lpMMI->ptMinTrackSize.x = windowRect.right - windowRect.left;
		lpMMI->ptMinTrackSize.y = windowRect.bottom - windowRect.top;
		break;
	}
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		app.setScreen(rect);
		break;
	}
	case WM_MOUSEMOVE:
	{
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		app.setMousePosition(Vector2(x, y));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		ys::InputManager::setKeyState(VK_LBUTTON, FALSE, FALSE);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		ys::InputManager::setKeyState(VK_RBUTTON, FALSE, FALSE);
		break;
	}
	case WM_LBUTTONUP:
	{
		ys::InputManager::setKeyState(VK_LBUTTON, KF_REPEAT, KF_UP);
		break;
	}
	case WM_RBUTTONUP:
	{
		ys::InputManager::setKeyState(VK_RBUTTON, KF_REPEAT, KF_UP);
		break;
	}
	case WM_KEYDOWN:
	{//이후 KF_ALTDOWN으로 Alt키 조합까지 구현가능
		auto keyflags = HIWORD(lParam);

		ys::InputManager::setKeyState(wParam,
			(keyflags & KF_REPEAT) == KF_REPEAT,
			(keyflags & KF_UP) == KF_UP);
		break;
	}
	case WM_KEYUP:
	{//이후 KF_ALTDOWN으로 Alt키 조합까지 구현가능
		auto keyflags = HIWORD(lParam);

		ys::InputManager::setKeyState(wParam,
			(keyflags & KF_REPEAT) == KF_REPEAT,
			(keyflags & KF_UP) == KF_UP);
		break;
	}
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	default:
		break;
	}

	return (::DefWindowProc(hWnd, Msg, wParam, lParam));
}