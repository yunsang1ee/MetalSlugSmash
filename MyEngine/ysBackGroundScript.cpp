#include "ysBackGroundScript.h"
#include <ysInputManager.h>
#include <ysTimer.h>
#include <ysGameObject.h>
#include <ysTransform.h>
#include <ysSpriteRenderer.h>

namespace ys
{
	BackGroundScript::BackGroundScript() : parallax(1)
	{
	}
	BackGroundScript::~BackGroundScript()
	{
	}
	void BackGroundScript::Init()
	{
	}
	void BackGroundScript::Update()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto sr = GetOwner()->GetComponent<SpriteRenderer>();
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
		{
			auto position = tr->GetPosition();
			
			tr->SetPosition({ position.x + Timer::getDeltaTime() * parallax, position.y });
			
			
			//ī�޶� ��� �Ǿ� �ִ��� �ƿ� �𸣱� ������ ��� �������� ��� �ؾ� ���� �𸣰��� ����� �����̴°���
			//ī�޶� �����̴°���

		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * parallax, position.y });
		}
	}
	void BackGroundScript::LateUpdate()
	{
	}
	void BackGroundScript::Render(HDC hDC)
	{
	}
}