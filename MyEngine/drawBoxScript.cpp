#include "drawBoxScript.h"
#include "ysGameObject.h"
#include "YSapplication.h"
#include <YSapplication.h>
#include <fstream>
#include <iostream>
#include <string>
#include<sstream>
#include <ysInputManager.h>
#include"ysBoxCollider2D.h"
extern Application app;
drawBoxScript::drawBoxScript()
{
}

drawBoxScript::~drawBoxScript()
{
}

void drawBoxScript::Init()
{
}

void drawBoxScript::Update()
{
	if (InputManager::getKeyDown(VK_LBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(app.getHWND(), &pt);
		GetOwner()->GetComponent<>
		rect.left = pt.x;
		rect.top = pt.y;
	}
	else if (InputManager::getKeyUp(VK_LBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(app.getHWND(), &pt);
		rect.right = pt.x;
		rect.bottom = pt.y;
	}
}

void drawBoxScript::LateUpdate()
{
}

void drawBoxScript::Render(HDC hDC)
{
}

void drawBoxScript::Release()
{
	std::wstring str;
	str = rect.left + L" ";
	str += rect.top + L" ";
	str += rect.right + L" ";
	str += rect.bottom + L" ";

	std::wofstream file(L"..\\Resource\\box.txt");
	file << str;
}
