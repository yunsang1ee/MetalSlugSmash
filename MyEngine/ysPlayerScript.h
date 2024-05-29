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

		void ShootBullet();
		void SetSpeed(const float& speed) { this->speed = speed; }

	private:
		float speed;
		float coolTime;
		int count;

	};
}