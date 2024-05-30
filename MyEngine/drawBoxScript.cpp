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
#include<string>
#include"STAGE1.h"
#include "ysSceneManager.h"
#include"ysCamera.h"
#include"ysTransform.h"
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
		Vector2 pt;
		pt=app.getmousePosition();
		rect.left = pt.x;
		rect.top = pt.y;
	}
	else if (InputManager::getKeyUp(VK_LBUTTON))
	{
		Vector2 pt;
		pt = app.getmousePosition();
		rect.right = pt.x;
		rect.bottom = pt.y;
		auto scene = dynamic_cast<STAGE1*>(SceneManager::GetaActiveScene());
		auto tr = scene->GetPlayer()->GetComponent<Transform>()->GetPosition() - Vector2(app.getScreen().x/2,app.getScreen().y/2);
		std::string str;
		str = "left: " + std::to_string(tr.x+rect.left) + " ";
		str += " top: " + std::to_string(rect.top) + " ";
		str += " right: " + std::to_string(tr.x+rect.right) + " ";
		str += " bottom: " + std::to_string(rect.bottom) + " ";

		std::ofstream file;
		file.open("..\\Resource\\box1.txt");
		if (file.is_open())
		{
			file << str;
		}
		
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
	
}
