#include "ysPlayerScript.h"
#include "ysGameObject.h"
#include "ysTimer.h"
#include "ysInputManager.h"
#include <ysTransform.h>

namespace ys
{
	PlayerScript::PlayerScript() : prevPosition({ 0, 0 }), speed(300), coolTime(0)
	{
	}
	PlayerScript::~PlayerScript()
	{
	}
	void PlayerScript::Init()
	{
		
	}
	void PlayerScript::Update()
	{
		if (coolTime >= 0)
			coolTime -= 1 / Timer::getRealFPS();
		else
			coolTime = 0.0f;

		auto tr = GetOwner()->GetComponent<Transform>();
		auto position = tr->GetPosition();
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT) || InputManager::getKey(VK_LBUTTON))
		{
			tr->SetPosition({ position.x - 1 / Timer::getRealFPS() * speed, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT) || InputManager::getKey(VK_RBUTTON))
		{
			tr->SetPosition({ position.x + 1 / Timer::getRealFPS() * speed, position.y });
		}
		if (InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP))
		{
			tr->SetPosition({ position.x, position.y - 1 / Timer::getRealFPS() * speed });
		}
		if (InputManager::getKey((BYTE)ys::Key::S) || InputManager::getKey(VK_DOWN))
		{
			tr->SetPosition({ position.x, position.y + 1 / Timer::getRealFPS() * speed });
		}

		prevPosition = position;

		if (InputManager::getKey((BYTE)ys::Key::U) && !coolTime)
		{
			speed += 10.0f;
			coolTime = 0.1f;
		}
		if (InputManager::getKey((BYTE)ys::Key::I) && !coolTime)
		{
			speed -= 10.0f;
			coolTime = 0.1f;
		}
	}
	void PlayerScript::LateUpdate()
	{
	}
	void PlayerScript::Render(HDC hDC)
	{
	}
}