#include "ysBackGroundScript.h"
#include <ysInputManager.h>
#include <ysTimer.h>
#include <ysGameObject.h>
#include <ysTransform.h>
#include <ysRenderer.h>

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
	}
	void BackGroundScript::Update()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		if ((InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT))
			&& !renderer::mainCamera->isXmax() && !renderer::mainCamera->isXmin())
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x + Timer::getDeltaTime() * parallax, position.y });
			//카메라가 어떻게 되어 있는지 아예 모르기 때문에 배경 움직임을 어떻게 해야 할지 모르겟음 배경이 움직이는건지
			//카메라가 움직이는건지
		}
		if ((InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT))
			&& !renderer::mainCamera->isXmax() && !renderer::mainCamera->isXmin())
		{
			auto position = tr->GetPosition();
			tr->SetPosition({ position.x - Timer::getDeltaTime() * parallax, position.y });
		}
		if (InputManager::getKeyDown(VK_BACK))
		{
			sr->SetTexture
		}
	}
	void BackGroundScript::LateUpdate()
	{
	}
	void BackGroundScript::Render(HDC hDC)
	{
	}
}