#pragma once
#include "ysGameObject.h"

namespace ys
{
	class Player : public GameObject
	{
	public:
		Player() = default;

		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hDC) override;
	};
}
