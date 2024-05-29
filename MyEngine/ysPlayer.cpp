#include "ysPlayer.h"
#include <ysTransform.h>
#include <ysRenderer.h>

namespace ys
{
	void Player::Init() 
	{
		GameObject::Init();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Player::Render(HDC hDC)
	{
		GameObject::Render(hDC);
		auto tr = GetComponent<Transform>();
		auto positionedByCamera = renderer::mainCamera->CalculatPosition(tr->GetPosition());
		auto position = tr->GetPosition();
		SetBkMode(hDC, TRANSPARENT);
		TextOut(hDC, positionedByCamera.x, positionedByCamera.y,
			(L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).c_str()
			, (L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).size());
		TextOut(hDC, positionedByCamera.x, positionedByCamera.y + 20,
			(L"x: " + std::to_wstring(positionedByCamera.x) + L" y: " + std::to_wstring(positionedByCamera.y)).c_str()
			, (L"x: " + std::to_wstring(positionedByCamera.x) + L" y: " + std::to_wstring(positionedByCamera.y)).size());
	}
}
