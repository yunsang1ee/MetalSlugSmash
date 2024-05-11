#pragma once
#include "ysGameObject.h"

namespace ys
{
	class Player : public GameObject
	{
	public:
		void Init() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hDC) override;

	private:
		Vector2 prevPosition;

		float speed ;
		float coolTime;
	};
}
