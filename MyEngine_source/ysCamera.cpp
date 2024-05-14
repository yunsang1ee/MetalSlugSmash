#include "ysCamera.h"
#include "ysTransform.h"
#include "YSapplication.h"
#include "ysInputManager.h"
#include "ysTimer.h"

extern ys::Application app;

namespace ys
{
	Camera::Camera() : Component(enums::ComponentType::Camera)
		, distance(Vector2::Zero), resolution({static_cast<float>(app.getScreen().x), static_cast<float>(app.getScreen().y) })
		, target(nullptr)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Init()
	{
	}
	void Camera::Update()
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto position = tr->GetPosition();
		if (InputManager::getKey((BYTE)ys::Key::T))
		{
			ClearTarget();
		}

		if (target)
		{
			auto tr = target->GetComponent<Transform>();
			lookPosition = tr->GetPosition();
		}
		else
			lookPosition = tr->GetPosition();
		distance = lookPosition - (resolution / 2.0f);
	}
	void Camera::LateUpdate()
	{
	}
	void Camera::Render(HDC hDC)
	{
		auto tr = GetOwner()->GetComponent<Transform>();
		auto position = tr->GetPosition();
		TextOut(hDC, position.x, position.y,
			(L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).c_str()
			, (L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).size());
	}
}