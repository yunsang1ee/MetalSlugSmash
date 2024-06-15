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
	auto position = app.getmousePosition() + ys::renderer::mainCamera->GetLookPosition() - (app.getScreenf() / 2);
	GetOwner()->GetComponent<Transform>()->SetPosition(position);
	if (InputManager::getKeyDown(VK_CAPITAL))
	{
		wallDraw = !wallDraw;
		
	}

	if (!wallDraw)
	{
		if (InputManager::getKeyDown(VK_LBUTTON))
			lt = position;

		if (InputManager::getKey(VK_LBUTTON))
			rb = position;

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
			std::ofstream file{ "..\\Resource\\box1.txt", std::ios::trunc };
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
	
	
	if (wallDraw)
	{
		if (InputManager::getKeyDown(VK_LBUTTON))
			lt = position;

		if (InputManager::getKey(VK_LBUTTON))
			rb = position;

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
			std::ofstream file{ "..\\Resource\\Wall.txt", std::ios::trunc };
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
