#pragma once
#include "ysScript.h"
namespace ys
{
	class EnemyScript : public Script
	{
		enum class EnemyType 
		{
			Normal,//좌우 왔다갔다.
			Strong,//플레이어 쪽으로 다가옴
			Boss//플레이어 쪽으로 다가오고 공격함
		};
		enum class EnemyState
		{
			Idle,
			Attack,
			Death
		};
	public:
		EnemyScript();
		~EnemyScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetHp(int hp) { this->hp = hp; }
		int GetHp() { return hp; }
		void NexTAnimation();
		void IsAdd();
	private:
		void destroy();
		void move();
	private:
		int hp;
		float timer;
		bool moveRight;
		bool death;
		math::Vector2 direction;
		EnemyType enemyType;
		EnemyState enemyState;
	};
}

