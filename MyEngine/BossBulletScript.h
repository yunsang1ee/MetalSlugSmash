#pragma once
#include "ysScript.h"
using namespace ys;
namespace ys
{
	class BossBulletScript : public Script
	{
	public:
		BossBulletScript();
		~BossBulletScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		void boom();

	private:
		float deathTime;
		float time;
		unsigned int damage;
	};
}


