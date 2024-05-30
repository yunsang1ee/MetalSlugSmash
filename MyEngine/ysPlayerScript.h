#pragma once
#include "ysScript.h"

namespace ys
{
	class PlayerScript : public Script
	{
		enum class PlayerState
		{
			Idle, Move, Jump, Slide, Attack, Damaged, Sit ,Lookup
		};
		enum class BulletDirection
		{
			Left, Right, Up, Down
		};
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

		void ShootBullet();
	

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		
		void SetLowerBody(GameObject* PlayerLowerBody) { this->PlayerLowerBody = PlayerLowerBody; }
		
	private:
		void idle();
		void move();
		void sit();
		void slide();
		void attack();
		void lookup();
	private:
		math::Vector2 prevPosition;
		float time = 0;
		bool goingDown;

		
		float coolTime;
		int count;
	
		BulletDirection direction;
		GameObject* PlayerLowerBody;
		PlayerState state;
	};
}