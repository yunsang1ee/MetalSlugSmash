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
		, rotation(Vector2::Zero)
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
	}

	void Transform::LateUpdate()
	{
	}

	void Transform::Render(HDC hDC)
	{
	}
}
