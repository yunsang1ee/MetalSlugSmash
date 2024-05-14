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
		auto position = renderer::mainCamera->CalculatPosition(tr->GetPosition());
		TextOut(hDC, position.x, position.y,
			(L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).c_str()
			, (L"x: " + std::to_wstring(position.x) + L" y: " + std::to_wstring(position.y)).size());
	}
}
