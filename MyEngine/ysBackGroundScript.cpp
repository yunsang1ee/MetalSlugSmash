#include "ysBackGroundScript.h"
#include <ysInputManager.h>
#include <ysTimer.h>
#include <ysGameObject.h>
#include <ysTransform.h>
#include <ysRenderer.h>
#include<ysBoxCollider2D.h>
namespace ys
{
	BackGroundScript::BackGroundScript() : parallax(300)
	{
	}
	BackGroundScript::~BackGroundScript()
	{
	}
	void BackGroundScript::Init()
	{
		GetOwner()->GetComponent<BoxCollider2D>()->setName(L"BackGround");
	}
	void BackGroundScript::Update()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		if ((InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
			&& !renderer::mainCamera->isXmax() && !renderer::mainCamera->isXmin())
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * parallax, position.y });
		}
		if ((InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
			&& !renderer::mainCamera->isXmax() && !renderer::mainCamera->isXmin())
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