#include "ysBackGroundScript.h"
#include <ysInputManager.h>
#include <ysTimer.h>
#include <ysGameObject.h>
#include <ysTransform.h>

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
		auto position = tr->GetPosition();
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT) || InputManager::getKey(VK_LBUTTON))
		{
			tr->SetPosition({ position.x + 1 / Timer::getRealFPS() * parallax, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT) || InputManager::getKey(VK_RBUTTON))
		{
			tr->SetPosition({ position.x - 1 / Timer::getRealFPS() * parallax, position.y });
		}
	}
	void BackGroundScript::LateUpdate()
	{
	}
	void BackGroundScript::Render(HDC hDC)
	{
	}
}