#include "ysTransform.h"
#include <ysInputManager.h>
#include <ysTimer.h>
#include <ysGameObject.h>
#include <ysSpriteRenderer.h>

namespace ys
{

	Transform::Transform()
		: Component(enums::ComponentType::Transform)
		, scale(Vector2::Zero)
		, rotation(0.0f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Init()
	{
	}

	void Transform::Update()
	{
		if (getName() == L"TRTilte")
		{
			position.x -= 50;
		}
		else if (getName() == L"TRBackBack")
		{
			if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT) || InputManager::getKey(VK_LBUTTON))
			{
				SetPosition({ position.x - 1 / Timer::getRealFPS() * 125, position.y });
			}
			if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT) || InputManager::getKey(VK_RBUTTON))
			{
				SetPosition({ position.x + 1 / Timer::getRealFPS() * 125, position.y });
			}
			if (InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP))
			{
				SetPosition({ position.x, position.y - 1 / Timer::getRealFPS() * 125 });
			}
			if (InputManager::getKey((BYTE)ys::Key::S) || InputManager::getKey(VK_DOWN))
			{
				SetPosition({ position.x, position.y + 1 / Timer::getRealFPS() * 125 });
			}
		}
		else if (getName() == L"TRBack")
		{
			if (InputManager::getKey((BYTE)ys::Key::A) || InputManager::getKey(VK_LEFT) || InputManager::getKey(VK_LBUTTON))
			{
				SetPosition({ position.x - 1 / Timer::getRealFPS() * 250, position.y });
			}
			if (InputManager::getKey((BYTE)ys::Key::D) || InputManager::getKey(VK_RIGHT) || InputManager::getKey(VK_RBUTTON))
			{
				SetPosition({ position.x + 1 / Timer::getRealFPS() * 250, position.y });
			}
			if (InputManager::getKey((BYTE)ys::Key::W) || InputManager::getKey(VK_UP))
			{
				SetPosition({ position.x, position.y - 1 / Timer::getRealFPS() * 250 });
			}
			if (InputManager::getKey((BYTE)ys::Key::S) || InputManager::getKey(VK_DOWN))
			{
				SetPosition({ position.x, position.y + 1 / Timer::getRealFPS() * 250 });
			}
		}
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::Render(HDC hDC)
	{
	}
}
