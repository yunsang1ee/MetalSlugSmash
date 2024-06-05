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
		static int count = 0;
		pt = app.getmousePosition();
		rect.right = pt.x;
		rect.bottom = pt.y;
		auto scene = dynamic_cast<STAGE1*>(SceneManager::GetActiveScene());
		auto tr = scene->GetPlayer()->GetComponent<Transform>()->GetPosition() - Vector2(app.getScreen().x/2,app.getScreen().y/2);
		//카메라는 맵의 좌표를 알려줄수 없음
		// //auto tr = scene->GetLayer(LayerType::Camera)->GetGameObjects()[0]->GetComponent<Transform>()->GetPosition();
		std::string str;
		str = std::to_string(count++) + "-> ";
		str += "left: " + std::to_string(tr.x+rect.left) + " ";
		str += " top: " + std::to_string(rect.top) + " ";
		str += " right: " + std::to_string(tr.x+rect.right) + " ";
		str += " bottom: " + std::to_string(rect.bottom) + " ";
		str += "\n";

		std::ofstream file;
		file.open("..\\Resource\\box1.txt", std::ios::app);
		if (file.is_open())
		{
			file << str;
		}
		file.close();
		
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
