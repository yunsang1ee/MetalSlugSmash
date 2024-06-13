#pragma once
#include "ysScript.h"

namespace ys
{
	class PlayerScript : public Script
	{
		enum class PlayerState
		{
			Idle, IdleJump, Move, Grenade, Sit
			, LookDown, LookDownAttack, JumpAttack, MoveJump, IdleAttack
			, LookUp, LookUpAttack
		};
		
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Init();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hDC);

		void ShootBullet();
		void ShootEnd();

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetLowerBody(GameObject* playerLowerBody) { this->playerLowerBody = playerLowerBody; }
		
	private:
		void idle();
		void idle_Jump();
		void move();
		void grenade();
		void sit();

		void lookDown();
		void lookDown_Attack();

		void jump_Attack();
		void move_Jump();
		void idle_Attack();
		
		void lookUp();
		void lookUp_Attack();

	private:
		float attackDirection;
		math::Vector2 bulletOffset;
		int count;

		class Transform* ownerTransform;
		class Animator* ownerAnimator;

		GameObject* playerLowerBody;
		PlayerState state;
	};
}