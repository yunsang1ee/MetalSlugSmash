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


		void SetSpeed(const float& speed) { this->speed = speed; }

	private:
		void idle();
		void move();

	private:
		math::Vector2 prevPosition;
		PlayerState state;
		float speed;
		float coolTime;
		int count;
	};
}