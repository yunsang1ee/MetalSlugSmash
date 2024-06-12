#pragma once
#include <ysScript.h>

namespace ys
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		~BulletScript();

		virtual void Init() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC hDC) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetDamage(int Damage) { this->Damage = Damage; }
		int getDamage() { return Damage; }
	private:
		float deathTime;
		float time;
		int Damage;
	};
}

