#pragma once
#include "ysScript.h"

namespace ys
{
	class PlayerScript : public Script
	{
		enum class PlayerState
		{
			Idle, Move
		};

	public:
		PlayerScript();
		~PlayerScript();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

		void ShootBullet();
		void SetSpeed(const float& speed) { this->speed = speed; }
		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		
		void SetTopBody(bool isTopBody=false) { this->isTopBody = isTopBody; }
		enum BulletDirection
		{
			Left,Right,Up,Down
		};
	private:
		void idle();
		void move();

	private:
		PlayerState state;
		float speed;
		float coolTime;
		int count;
		bool isTopBody;
		BulletDirection direction;
	};
}