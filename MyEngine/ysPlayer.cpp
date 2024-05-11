#include "ysPlayer.h"
#include "ysTimer.h"
#include "ysInputManager.h"
#include <ysTransform.h>

namespace ys
{
	void Player::Init() 
	{
		GameObject::Init();
		prevPosition = { 0, 0 };
		speed = 20;
		coolTime = 0;
	}

	void Player::Update()
	{
		GameObject::Update();
		if (coolTime >= 0)
			coolTime -= 1 / Timer::getRealFPS();
		else
			coolTime = 0.0f;

		auto tr = GetComponent<Transform>();
		auto position = tr->GetPosition();
		if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT) || InputManager::getKey(VK_LBUTTON))
		{
			tr->SetPosition({position.x - 1 / Timer::getRealFPS() * speed, position.y});
		}
		if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT) || InputManager::getKey(VK_RBUTTON))
		{
			tr->SetPosition({position.x + 1 / Timer::getRealFPS() * speed, position.y});
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

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Player::Render(HDC hDC)
	{
		GameObject::Render(hDC);
		auto tr = GetComponent<Transform>();
		auto position = tr->GetPosition();
		TextOut(hDC, position.x, position.y,
			(L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).c_str()
			, (L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).size());
	}
}
