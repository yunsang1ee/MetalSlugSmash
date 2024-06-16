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
#include"ysObject.h"
#include"ysTransform.h"
#include <ysRenderer.h>
#include "ysPlayScene.h"
#include "BlockScript.h"
#include "WallScript.h"
#include "ysEnemyScript.h"
extern Application app;
drawBoxScript::drawBoxScript() :drawType(DrawType::Block)
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
	auto position = app.getmousePosition() + ys::renderer::mainCamera->GetLookPosition() - (app.getScreenf() / 2);
	GetOwner()->GetComponent<Transform>()->SetPosition(position);
	if (InputManager::getKeyDown(VK_LBUTTON))
		lt = position;

	if (InputManager::getKey(VK_LBUTTON))
		rb = position;

	if (InputManager::getKeyDown(VK_CAPITAL))
	{
		switch (drawType)
		{
		case drawBoxScript::DrawType::Block:
			drawType = drawBoxScript::DrawType::Wall;
			break;
		case drawBoxScript::DrawType::Wall:
			drawType = drawBoxScript::DrawType::Block;
			break;
		default:
			break;
		}
	}
	if (InputManager::getKey(VK_CONTROL) && InputManager::getKeyDown((UINT)Key::B))
	{
		drawType = drawBoxScript::DrawType::Enemy;
	}
	switch (drawType)
	{
	case drawBoxScript::DrawType::Block:
	
	{
		if (InputManager::getKeyUp(VK_LBUTTON))
		{
			if (lt.x < rb.x && lt.y < rb.y)
			{
				auto block = object::Instantiate<GameObject>(LayerType::Block, lt);

				auto size = (rb - lt) / 100.0f;
				auto bx = block->AddComponent<BoxCollider2D>();
				bx->setName(L"BackGround");
				bx->SetSize(size);
				block->AddComponent<BlockScript>();

			}
			lt = Vector2::Zero;
			rb = Vector2::Zero;
		}
		if (InputManager::getKeyDown((UINT)Key::S) && InputManager::getKey(VK_CONTROL))
		{
			std::ofstream file{ "..\\Resource\\box2.txt", std::ios::trunc };
			if (file.is_open())
			{
				Vector2 pos;
				Vector2 size;
				auto blocks = SceneManager::GetActiveScene()->GetLayer(enums::LayerType::Block)->GetGameObjects();
				for (auto block : blocks)
				{
					pos = block->GetComponent<Transform>()->GetPosition();
					size = block->GetComponent<BoxCollider2D>()->GetSize();
					file << pos.x << ' ' << pos.y << ' ' << size.x << ' ' << size.y << '\n';
				}
			}
		}
	}
		break;
	case drawBoxScript::DrawType::Wall:
	{
		if (InputManager::getKeyUp(VK_LBUTTON))
		{
			if (lt.x < rb.x && lt.y < rb.y)
			{
				auto block = object::Instantiate<GameObject>(LayerType::Wall, lt);

				auto size = (rb - lt) / 100.0f;
				auto bx = block->AddComponent<BoxCollider2D>();
				bx->setName(L"Wall");
				bx->SetSize(size);
				block->AddComponent<WallScript>();

			}
			lt = Vector2::Zero;
			rb = Vector2::Zero;
		}

		if (InputManager::getKeyDown((UINT)Key::S) && InputManager::getKey(VK_CONTROL))
		{
			std::ofstream file{ "..\\Resource\\Wall2.txt", std::ios::trunc };
			if (file.is_open())
			{
				Vector2 pos;
				Vector2 size;
				auto blocks = SceneManager::GetActiveScene()->GetLayer(enums::LayerType::Wall)->GetGameObjects();
				for (auto block : blocks)
				{
					pos = block->GetComponent<Transform>()->GetPosition();
					size = block->GetComponent<BoxCollider2D>()->GetSize();
					file << pos.x << ' ' << pos.y << ' ' << size.x << ' ' << size.y << '\n';
				}
			}
		}
	}
		break;
	case drawBoxScript::DrawType::Enemy:
	{
		if (InputManager::getKeyUp(VK_LBUTTON))
		{
			
			auto enemy = object::Instantiate<GameObject>(LayerType::Enemy, lt);
			auto es = enemy->AddComponent<EnemyScript>();
			es->IsAdd();

			enemys.push_back(enemy);
			lt = Vector2::Zero;
			rb = Vector2::Zero;
		}
		if (InputManager::getKeyDown((UINT)Key::S) && InputManager::getKey(VK_CONTROL))
		{
			std::ofstream file{ "..\\Resource\\Enemy.txt", std::ios::app };
			if (file.is_open())
			{
				Vector2 pos;
				Vector2 size;
				
				for (auto enemy : enemys)
				{
					pos = enemy->GetComponent<Transform>()->GetPosition();
					file << pos.x << ' ' << pos.y << '\n';
				}
			}
		}
	}
		break;
	case drawBoxScript::DrawType::Item:
		break;
	default:
		break;
	}
	
}

void drawBoxScript::LateUpdate()
{
}

void drawBoxScript::Render(HDC hDC)
{
	if (ys::Collider::isRender())
	{
		Vector2 ltTmp;
		Vector2 rbTmp;
		if (ys::renderer::mainCamera)
		{
			ltTmp = ys::renderer::mainCamera->CalculatPosition(lt);
			rbTmp = ys::renderer::mainCamera->CalculatPosition(rb);
		}

		auto brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		auto oldBrush = SelectObject(hDC, brush);
		auto pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		auto oldPen = SelectObject(hDC, pen);
		Rectangle(hDC
			, ltTmp.x
			, ltTmp.y
			, rbTmp.x
			, rbTmp.y);
		SelectObject(hDC, oldPen);
		DeleteObject(pen);
		SelectObject(hDC, oldBrush);
	}
}

void drawBoxScript::Release()
{
	
}
