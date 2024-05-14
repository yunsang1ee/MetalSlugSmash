#pragma once
#include "ysScript.h"

namespace ys
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

	private:
		math::Vector2 prevPosition;

		float speed;
		float coolTime;
	};
}

