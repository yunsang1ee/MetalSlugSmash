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

		void SetSpeed(const float& speed) { this->speed = speed; }
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
		enum BulletDirection
		{
			Left,Right,Up,Down
		};
	private:
		math::Vector2 prevPosition;
		float time = 0;
		bool goingDown;
		float speed;
		float coolTime;
		int count;
		BulletDirection direction;
	};
}